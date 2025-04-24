#include <xc.h>
#include <stdio.h>
#include <math.h>
#include "UART.h"
#include "Pic32Ini.h"
#include "TftDriver/TftDriver.h"
//Configuracion del sensor de temperatura
//Manejar conversor AD en automatico con Timer3

float media=0; //Inicializamos a 0 por si acaso
int hay_media=0;
float Vcc=3.3; //Alimentacion pa el sensor 

void initSensor(){
    //El sensor térmico a AN1-> RA1
    TRISA |=2; //Entrada sensor
    AD1CON1=0;//Apagar conversor
    AD1CON1bits.SSRC = 2;//Timer3
    AD1CON1bits.ASAM = 1;//Auto Sampling
    
    AD1CON2= 3<<2;//Solo hay un canal y 4 medidas (SMPI=3 +1)
    AD1CON3= 0x200; //(TSAMP y TADC) este valor me afecta mucho cuando T=1s
    
    AD1CHS=0x00010000; // AN1 a 0V
    
    IFS0bits.AD1IF = 0; // Borro el flag
    IEC0bits.AD1IE = 1; // Habilito
    IPC5bits.AD1IP = 2; // Prioridad 2
    IPC5bits.AD1IS = 0; // Subprioridad 0
    AD1CON1bits.ON = 0;  //Apagado que no empiece todavia
    
    T3CON = 0;
    TMR3 = 0;
    PR3 = 19531; //Muestrea cada 250ms
    T3CON= 0x0060; //Apagado y div 5
}
void startADC(){
    T3CON |=0x8000;
    AD1CON1bits.ON=1; //Encender AD
}

float conversionVaT(float Vmedida){
    static int R_fija=4700; // Resistencia auxiliar para medir
    static int R25=4700; //Resistencia del sensor a 25ºc
    static int B=3950; //Coeficiente Beta de la datasheet
    
    //Primero despejamos la R del sensor en la medida
    float R_sensor= R_fija*(Vmedida/(Vcc-Vmedida));
    //Ahora la formula pa temperatura en Kelvin
    float T_kelvin= B / (log(R_sensor / R25) + (B / 298.15)); //298.15 es 25 en K
    float T_celsius= T_kelvin-273.15;
    
    return T_celsius;
    
}
__attribute__((vector(23), interrupt(IPL2SOFT), nomips16))
void InterrupcionADC(void) {
    IFS0bits.AD1IF = 0; // Se borra el flag
    //Hacer media de los 4 
    media=(ADC1BUF0+ADC1BUF1+ADC1BUF2+ADC1BUF3)/4; //o >>2 es lo mismo
    hay_media=1;
    //Ahora lo que se quiera hacer con la media
    
}
int existeMedia(){
    int sol;
    asm("di");
    sol=hay_media;
    hay_media=0;
    asm("ei");
    return sol;
}

float getTemperatura(){
    float sol;
    asm("di");
    sol=media;
    hay_media=0;
    asm("ei");
    sol=Vcc*sol/1023;
    sol=conversionVaT(sol);
    return sol;
}
