#include <xc.h>
#include <stdio.h>
//Timer 3 ya esta ocupado asi que el Timer 2 para la bombilla o ventilador
//Se ha decicido Timer2 para bombilla e interrupciones para ventilador
void initBombilla(){
    //Pines
    //En registro B15
    //OC1 usa RB15
    ANSELC &=(1<<5);
    TRISC &=(1<<5);
    
    //Remapeo
    SYSKEY=0xAA996655;
    SYSKEY=0x556699AA;
    RPC5R = 5;
    SYSKEY=0xFE0;
    
    //Configuracion OC1
    OC1CON=0; //Primero apagado
    OC1R=2500;  // A DECIDIR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    OC1RS=2500;
    OC1CON =0x0006; //off, PWM sin faltas
    
    T2CON = 0;
    TMR2 = 0;
    PR2 = 49999; //50 us 
    T2CON = 0x0010; //Que empiece apagado
    
    
}
void startBombilla(){
    OC1CON |= 0x8000;
    TMR2=0; //Por si acaso
    T2CON |=0x8000;
}

void setBrillo(int brillo){
    OC1RS=brillo;
}
void stopBombilla(){
    OC1CON &= ~0x8000;
    T2CON  &= ~0x8000;
}