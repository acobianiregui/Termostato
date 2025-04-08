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


void initDisplay();
void init1();
int main(){
    //Inicicializaciones
    init1();
    initSensor();
    startADC();
    InicializarUART(9600);
    //initBombilla();
    //startBombilla();
    //setBrillo(2500*9);
    initDisplay();
    
    //Habilitar interrupciones
    INTCON |= (1<<12);
    asm("ei");
    int act; int ant=(PORTB>>5)&1;
    char temp [TAMANO_COLA]={0};
    while(33){
       act=(PORTB>>5)&1;
       if ((act!=ant)&&(act==0)){
           float temperatura=getTemperatura();
           sprintf(temp,"%.2f",temperatura);
           putsUART(temp);
           putsUART(" Celsius \n\r");
           setBrillo(2500*20);
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
}