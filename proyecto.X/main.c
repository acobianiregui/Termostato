#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <string.h>
#include "Pic32Ini.h"
#include "UART.h"
#include "sensor.h"
#include "TftDriver/TftDriver.h"
#include "bombilla.h"

int main(){
    //Inicicializaciones
    initSensor();
    startADC();
    InicializarUART(9600);
    initBombilla();
    startBombilla();
    setBrillo(2500*9);
    
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