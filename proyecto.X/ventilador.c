#include <stdio.h>
#include <xc.h>
int cuenta=0;
int vel=0;

float error_anterior = 0.0;
float dt2 = 1.0; 
float Kp2 = 80.0;            
float Kd2 = 0.1;   


//El ventilador sera por PWM de interrupciones
void initVentilador(){
    //Decidir pines
    TRISB &= ~(1<<14);
    ANSELB &= ~(1<<14);
    LATB &= ~(1<<14);
    //Timer 4
    T4CON=0;
    TMR4=0;
    PR4=999; //50 us
    T4CON=0x0000;
    //Interrupciones
    IFS0bits.T4IF=0; // Apagamos el flag por si acaso
    IEC0bits.T4IE=1; //Enable
    IPC4bits.T4IP=1; //Prioridad 1
    IPC4bits.T4IS=0; //Subprioridad 0   
   
}

int controlar_velocidad(float temperatura_deseada, float temperatura_actual){
    float error = temperatura_actual - temperatura_deseada;
    
    float derivada = (error - error_anterior)/dt2;
    
    error_anterior = error;
    
    float salida = Kp2 * error + Kd2 * derivada;
    
    if(salida > 100.0){
        salida = 100.0;
    }
    if(salida < 0.0){
        salida = 0.0;
    }
    int v = (salida >= 50.0) ? (int)salida : 0;
    if (error>=1 &&v==0){
        v+=50;
    }
    return v;
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
    LATB &= ~(1<<14);
}
int getVelocidad(){
    int sol;
    asm("di");
    sol=vel;
    asm("ei");
    return sol;
}

__attribute__((vector(16), interrupt(IPL1SOFT), nomips16))
void InterrupcionTimer4(void){
    IFS0bits.T4IF=0; //Apagamos flag
    if (cuenta>100){
        cuenta=0;
    }
    cuenta++;
    if (cuenta<vel){
        LATB |= (1 << 14);
        
    }else{
        LATB &= ~(1 << 14);
    }
}
