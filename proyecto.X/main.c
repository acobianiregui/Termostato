#include <stdio.h>
#include <stdlib.h>
#include <sys/attribs.h>
#include <stdint.h>
#include <xc.h>
#include <string.h>
#include "Pic32Ini.h"
#include "UART.h"
#include "sensor.h"
#include "TftDriver/TftDriver.h"
#include "bombilla.h"
#include "ventilador.h"

void initDisplay();
void init1();
char mensaje_temp[32]={0};

int main(){
    //Inicicializaciones
    init1();
    initSensor();
    startADC();
    InicializarUART(9600);
    initBombilla();
    startBombilla();
    //stopBombilla();
    initDisplay();
    //Habilitar interrupciones
    INTCON |= (1<<12);
    asm("ei");
    int act; int ant=(PORTB>>5)&1;
    char temp [TAMANO_COLA]={0};
    float t=0;
    int j=0;
    while(33){       
       act=(PORTB>>5)&1;
       //Actualizaci�n automatica en el display 
       if(existeMedia()){
           t=getTemperatura();
           setColor(VGA_BLACK);
           fillRect(0,40,158,60);
           setColor(VGA_WHITE);
           sprintf(mensaje_temp, "Hay %.2f grados",t );
           print(mensaje_temp, LEFT, 40,0);
           //Probar el PI
           j=controlar_brillo(31,t);
           //setBrillo(j);
           sprintf(temp,"%d",j);
           //putsUART(temp);
           setBrillo(j);
       }
       if ((act!=ant)&&(act==0)){
           
           sprintf(temp,"%.2f",t);
           putsUART(temp);
           putsUART(" Celsius \n\r");
           setBrillo(200);
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

void initDisplay(){
 
    extern uint8_t SmallFont[];
    extern unsigned short logo[];
    inicializarTFT(LANDSCAPE);
    setFont(SmallFont);
    clrScr(); // Borra la pantalla
    // Dibuja un rect�ngulo rojo en la parte superior de la pantalla.
    setColor(VGA_RED);
    fillRect(0, 0, 159, 13);
    // Dibuja un rect�ngulo gris en la parte inferior de la pantalla.
    setColorRGB(64, 64, 64);
    fillRect(0, 114, 159, 127);
    // Selecciona color blanco y fondo transparente para el texto
    setColor(VGA_WHITE);
    setBackColor(VGA_TRANSPARENT);
    // Imprime una cadena centrada en la l�nea 1 de la pantalla con �ngulo 0
    print("Termostato ACI & PMP", CENTER, 1,0);
    drawBitmap(CENTER-15,CENTER+50,50,64,logo,1);
}
