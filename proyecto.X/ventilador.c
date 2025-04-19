#include <stdio.h>
#include <xc.h>
int cuenta=0;
int vel=0;

float error_anterior = 0.0;
float dt = 1.0; 
float Kp = 12.0;            
float Kd = 2.0;   


//El ventilador sera por PWM de interrupciones
void initVentilador(){
    //Decidir pines
    TRISA &= ~(1<<7);
    ANSELC &= ~(1<<7);
    LATC &= ~(1<<7);
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

int controlar_velocidad(float temperatura_deseada, float temperatura_actual){
    float error = temperatura_actual - temperatura_deseada;
    
    float derivada = (error - error_anterior)/dt;
    
    error_anterior = error;
    
    float salida = Kp * error + Kd * derivada;
    
    if(salida > 100.0){
        salida = 100.0;
    }
    if(salida < 0.0){
        salida = 0.0;
    }
    
    return (int)salida;
}

void setVelocidad(int velocidad){
    asm("di");
    vel=velocidad;
    asm("ei");
}

void Ventilador_Start(void) {
    T4CON |= (1<<15);
}

void Ventilador_Stop(void) {
    T4CON &= ~(1<<15);
    LATC &= ~();
}

__attribute__((vector(16), interrupt(IPL1SOFT), nomips16))
void InterrupcionTimer4(void) {
    IFS0bits.T4IF=0; //Apagamos flag
    if (cuenta>100){
        cuenta=0;
    }
    cuenta++;
    if (cuenta<vel){
        LATA |= (1 << 7);
        
    }else{
        LATC &= ~(1 << 7);
        
    }
}