#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include <stdint.h>
#include <xc.h>
#include <string.h>
#include <ctype.h>
#include "Pic32Ini.h"
#include "UART.h"
#include "sensor.h"
#include "TftDriver/TftDriver.h"
#include "bombilla.h"
#include "ventilador.h"
//Funciones del main
void init1();//Inicalizacion de pines básicos
void initDisplay(); //Inicializa el fondo del display
int convertir_a_entero(const char* str, int* resultado); //Conversiones para los comandos
void interpretar_instruccion(const char* instruccion); //Interpreta las instrucciones del usuario
char* recibir_cadena();//Devuelve la cadena que ha envia el usuario
void cambiaVentDisplay(int n); //Actualiza el porcentaje de velocidad en el display
void cambiaBombiDisplay(int n); //Actualiza el porcentaje de brillo en el display
//Variables globales del main
char mensaje_temp[32]={0};
int modo_auto=0;
int t_deseada=0;
int main(){
    //Inicicializaciones
    init1();
    initSensor();
    startADC();
    InicializarUART(9600);
    initBombilla();
    startBombilla();
    initVentilador();
    Ventilador_Start();
    //stopBombilla();
    initDisplay();
    //Habilitar interrupciones
    INTCON |= (1<<12);
    asm("ei");
    char temp [TAMANO_COLA]={0};
    float t=0;
    int calor=0;
    int frio=0;
    while(33){   
       // Miramos si hay instrucciones
        char* instruccion = recibir_cadena();
        if (instruccion != NULL) {
            interpretar_instruccion(instruccion);
        }
       //Actualización automatica en el display 
       if(existeMedia()){
           t=getTemperatura();
           //Cambiar temperatura actual en el display
           asm("di");
           setColor(VGA_BLACK);
           fillRect(110,20,158,30);
           setColor(VGA_WHITE);
           sprintf(mensaje_temp, "%.2f",t);
           print(mensaje_temp, RIGHT, 20,0);
           asm("ei");
           //Probar el PI
           if (modo_auto){
               calor=controlar_brillo(t_deseada,t);
               frio=controlar_velocidad(t_deseada,t);
               cambiaVentDisplay(frio);
               cambiaBombiDisplay(calor);
               //sprintf(temp,"%d",calor);
               //putsUART(temp);
               setBrillo(calor);
               setVelocidad(frio);
           }
       }
       
    }
}

void init1(){
    ANSELB &= ~(1 << 5);   
    ANSELC &= ~0x000F;              

    LATA = 0;   
    LATB = 0; 
    LATC = 0x000F;                 

    TRISA = 0;
    TRISB = (1 <<5);                      
    TRISC = 0;  
}
/*Funcion que inicializae el fondo de display
 * OJO con el timer 4 y con las imagenes
 */
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
void initDisplay(){
    Ventilador_Stop(); //El timer 4 no puede estar corriendo justo a la vez
    extern unsigned short fan[];
    extern unsigned short bulb[];
    inicializarTFT(LANDSCAPE);
    setFont(SmallFont);
    clrScr(); // Borra la pantalla
    // Rectangulo de arriba
    setColor(VGA_RED);
    fillRect(0, 0, 159, 13);
    // Texto inicial
    setColor(VGA_WHITE);
    setBackColor(VGA_TRANSPARENT);
    print("Termostato ACI & PMP", CENTER, 1,0);
    print("Temp actual:", LEFT, 20,0);
    print("T esperada : ",LEFT,40,0);
    print("MODO AUTO:",CENTER,65,0);
    print("0 %",12,107,0);
    print("0 %",135,107,0);
    setFont(BigFont);
    print("OFF",55,90,0);
    setFont(SmallFont);
    //Lineas amarillas
    setColorRGB(255,255,0);
    drawLine(0,35,200,35);
    drawLine(0,55,200,55);
    // Imagenes (drawBitMap)
    // OJO!!!!!!
    //La he modificado para que que pueda pintar  bien fondos trasnparentes
    drawBitmap(CENTER-15,CENTER+50,34,33,fan,1);
    drawBitmap2(RIGHT+110,CENTER+50,34,34,bulb,1);
    Ventilador_Start();
}

char* recibir_cadena() {
    static char cadena[TAMANO_COLA];
    static int pos = 0;
    char mensaje[2] = {'\0', '\0'};// Para el eco
    char c = getcUART();                

    if (c != '\0') { // Se ha recibido algo
        mensaje[0] = c;
        putsUART(mensaje); //Eco

        if (c != '\r') { //No ha terminado
            if (pos < TAMANO_COLA) {
                cadena[pos++] = c;
            } else {
                //Si se pasa, reinicio
                pos = 0;
            }
        } else { //Termina la cadena
            cadena[pos] = '\0'; //Fin
            pos = 0;            //Reiniciamos para siguiente vez
            return cadena;      //Devolvemos la cadena 
        }
    }

    return NULL; //Aun no se ha terminado la cadena
}


/*
Quiero hacer una funcion que compruebe si la conversion es correcta
y que devuelva el valor si se podia convertir asi que hay que usar punteros
*/
int convertir_a_entero(const char* str, int* resultado) { 
    char* endptr;
    long val = strtol(str, &endptr, 10);

    // Se verifca que la cadena sea correcta
    if (*endptr != '\0') {
        return 0; // Hay valores no numéricos
    }

    *resultado = (int) val;
    return 1; // Todo ha ido bien
}
/*
 Funcion para interpretar las instrucciones que se le puede dar al termostato
 * AUTO <numero> Activa el modo automatico a la temperatura especificada
 * MANUAL B <numero> Activa manualmente 
 */
void interpretar_instruccion(const char* instruccion) {
    if (strlen(instruccion) > 20) {
        putsUART("Longitud maxima excedida \r\n");
        return;
    }
    // Copiamos cadena
    char buffer[21];  // +1 por el '\0'
    strncpy(buffer, instruccion, 20);
    buffer[20] = '\0'; // Aseguramos '\0'

    // Identificamos secciones usando espacio como separador
    char* modo = strtok(buffer, " ");
    char* tipo = strtok(NULL, " ");
    char* valor_str = strtok(NULL, " ");

    // Instrucción "AUTO <numero>" o "AUTO OFF"
    if (modo != NULL && strcmp(modo, "AUTO") == 0) {
        if (tipo == NULL) {
            putsUART("ERROR: AUTO requiere parámetro \r\n");
            return;
        }

        // Caso: "AUTO OFF"
        if (strcmp(tipo, "OFF") == 0 && valor_str == NULL) {
            if(modo_auto){ //Estaba en auto
                //Pintamos en display OFF
                asm("di");
                setColor(VGA_BLACK);
                fillRect(50,87,100,110);
                setColor(VGA_WHITE);
                setFont(BigFont);
                print("OFF",55,90,0);
                setFont(SmallFont);
                asm("ei");   
                setBrillo(0);
                cambiaVentDisplay(0);
                setVelocidad(0);
                cambiaBombiDisplay(0);
            }
            modo_auto = 0;
            //Quito la temperatura deseada (en modo manual no hay)
            asm("di");
            setColor(VGA_BLACK);
            fillRect(110,40,158,50);
            setColor(VGA_WHITE);
            asm("ei");
            putsUART("\r\n");
            return;
        }

        // Caso: "AUTO <numero>"
        if (valor_str != NULL) {
            putsUART("ERROR: AUTO tiene demasiados argumentos\r\n");
            return;
        }

        int valor_auto;
        if (!convertir_a_entero(tipo, &valor_auto)) {
            putsUART("ERROR: no numeros en la conversion\r\n");
            return;
        }
        if(!modo_auto){ //Estaba en off
            //Cambiamos a ON en el display
            asm("di");
            setColor(VGA_BLACK);
            fillRect(50,87,100,110);
            setColor(VGA_WHITE);
            setFont(BigFont);
            print("ON",55,90,0);
            setFont(SmallFont);
            asm("ei");
        }
        t_deseada=valor_auto; //Se ajusta a la nueva temperatura pedida
        modo_auto = 1; //Se activa el modo automatico
        asm("di");
        setColor(VGA_BLACK);
        fillRect(110,40,158,50);
        setColor(VGA_WHITE);
        sprintf(mensaje_temp, "%d",t_deseada);
        print(mensaje_temp, RIGHT, 40,0);
        asm("ei");
        putsUART("\r\n");
        return;
    }

    // Comando "MANUAL V <numero>" o "MANUAL B <numero>"
    if (modo == NULL || tipo == NULL || valor_str == NULL) {
        putsUART("ERROR: no se reconoce la instruccion\r\n");
        return;
    }
    if(modo_auto){ //Estaba en on, pintamos 
        asm("di");
        setColor(VGA_BLACK);
        fillRect(50,87,100,110);
        setColor(VGA_WHITE);
        setFont(BigFont);
        print("OFF",55,90,0);
        setFont(SmallFont);
        asm("ei");   
    }
    modo_auto = 0; // Por si no se hubiera desactivado antes
    asm("di");
    setColor(VGA_BLACK);
    fillRect(110,40,158,50);
    setColor(VGA_WHITE);
    asm("ei");
    int valor;
    if (!convertir_a_entero(valor_str, &valor)) {
        putsUART("ERROR: no numeros en conversion\r\n");
        return;
    }

    if (strcmp(modo, "MANUAL") == 0) {
        if (strcmp(tipo, "V") == 0) {
            if (valor>100){
                valor=100;
            }
            if (valor<50){
                valor=0;
            }
            setVelocidad(valor);
            cambiaVentDisplay(valor);
            putsUART("\r\n");
        } else if (strcmp(tipo, "B") == 0) {
            setBrillo(valor);
            putsUART("\r\n");
            cambiaBombiDisplay(valor);
        } else {
            putsUART("ERROR: modo manual erroneo\r\n");
        }
    } else {
        putsUART("ERROR: instruccion desconocida\r\n");
    }
}

void cambiaVentDisplay(int n){
    asm("di");
    setColor(VGA_BLACK);
    fillRect(LEFT,107,26,117);
    setColor(VGA_WHITE);
    sprintf(mensaje_temp,"%d",n);
    print(mensaje_temp,5,107,0);
    asm("ei");
}
void cambiaBombiDisplay(int n){
    asm("di");
    setColor(VGA_BLACK);
    fillRect(127,107,150,117);
    setColor(VGA_WHITE);
    sprintf(mensaje_temp,"%d",n);
    print(mensaje_temp,127,107,0);
    asm("ei");
}