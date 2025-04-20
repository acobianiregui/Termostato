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
void initDisplay();
void init1();
int convertir_a_entero(const char* str, int* resultado);
void interpretar_instruccion(const char* instruccion);
char* recibir_cadena();
//Variables globales del main
char mensaje_temp[32]={0};
int modo_auto=0;
int t_deseada=28;
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
    int act; int ant=(PORTB>>5)&1;
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
       act=(PORTB>>5)&1;
       //Actualización automatica en el display 
       if(existeMedia()){
           t=getTemperatura();
           asm("di");
           setColor(VGA_BLACK);
           fillRect(0,40,158,60);
           setColor(VGA_WHITE);
           sprintf(mensaje_temp, "Hay %.2f grados",t );
           print(mensaje_temp, LEFT, 40,0);
           asm("ei");
           //Probar el PI
           if (modo_auto){
               calor=controlar_brillo(t_deseada,t);
               frio=controlar_velocidad(t_deseada,t);
               sprintf(temp,"%d",calor);
               //putsUART(temp);
               setBrillo(calor);
               setVelocidad(frio);
           }
       }
       if ((act!=ant)&&(act==0)){
           t_deseada=24;
           sprintf(temp,"%.2f",t);
           putsUART(temp);
           putsUART(" Celsius \n\r");
           //setBrillo(200);
       } 
       ant=act;
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
void initDisplay(){
    Ventilador_Stop(); //El timer 4 no puede estar corriendo justo a la vez
    extern uint8_t SmallFont[];
    extern unsigned short logo[];
    inicializarTFT(LANDSCAPE);
    setFont(SmallFont);
    clrScr(); // Borra la pantalla
    // Dibuja un rectángulo rojo en la parte superior de la pantalla.
    setColor(VGA_RED);
    fillRect(0, 0, 159, 13);
    // Dibuja un rectángulo gris en la parte inferior de la pantalla.
    setColorRGB(64, 64, 64);
    fillRect(0, 114, 159, 127);
    // Selecciona color blanco y fondo transparente para el texto
    setColor(VGA_WHITE);
    setBackColor(VGA_TRANSPARENT);
    // Imprime una cadena centrada en la línea 1 de la pantalla con ángulo 0
    print("Termostato ACI & PMP", CENTER, 1,0);
    drawBitmap(CENTER-15,CENTER+50,50,64,logo,1);
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
            modo_auto = 0;
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
        t_deseada=valor_auto; //Se ajusta a la nueva temperatura pedida
        modo_auto = 1; //Se activa el modo automatico
        putsUART("\r\n");
        return;
    }

    // Comando "MANUAL V <numero>" o "MANUAL B <numero>"
    if (modo == NULL || tipo == NULL || valor_str == NULL) {
        putsUART("ERROR: no se reconoce la instruccion\r\n");
        return;
    }

    modo_auto = 0; // Por si no se hubiera desactivado antes

    int valor;
    if (!convertir_a_entero(valor_str, &valor)) {
        putsUART("ERROR: no numeros en conversion\r\n");
        return;
    }

    if (strcmp(modo, "MANUAL") == 0) {
        if (strcmp(tipo, "V") == 0) {
            setVelocidad(valor);
            putsUART("\r\n");
        } else if (strcmp(tipo, "B") == 0) {
            setBrillo(valor);
            putsUART("\r\n");
        } else {
            putsUART("ERROR: modo manual erroneo\r\n");
        }
    } else {
        putsUART("ERROR: instruccion desconocida\r\n");
    }
}

