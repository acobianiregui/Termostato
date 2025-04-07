#include <stdio.h>
#include <xc.h>
int cuenta=0;
int vel=0;
//El ventilador sera por PWM de interrupciones
void initVentilador(){
    //Decidir pines
    
    //Timer 4
    T4CON=0;
    TMR4=0;
    PR4=249; //50 us
    T4CON=0x0000;
    //Interrupciones
    IFS0bits.T4IF=0; // Apagamos el flag por si acaso
    IEC0bits.T4IE=1; //Enable
    IPC4bits.T4IP=1; //Prioridad 1
    IPC4bits.T4IS=0; //Subprioridad 0   
}
void setVelocidad(int velocidad){
    asm("di");
    vel=velocidad;
    asm("ei");
}
__attribute__((vector(16), interrupt(IPL1SOFT), nomips16))
void InterrupcionTimer4(void) {
    IFS0bits.T4IF=0; //Apagamos flag
    if (cuenta>100){
        cuenta=0;
    }
    cuenta++;
    if (cuenta<vel){
        //Alto nivel
        
    }else{
        //Bajo nivel
        
    }
}
