#include <xc.h>
#include <stdio.h>
//Timer 3 ya esta ocupado asi que el Timer 2 para la bombilla o ventilador
//Se ha decicido Timer2 para bombilla e interrupciones para ventilador
#define PERIODO 50000
#define max(a, b) ((a) > (b) ? (a) : (b))

int alto=0;
void initBombilla(){
    //Pines
    ANSELC &=~(1<<4);
    TRISC &=~(1<<4);
    LATC &= ~(1<<4);
    
    //Remapeo
    SYSKEY=0xAA996655;
    SYSKEY=0x556699AA;
    RPC4R = 5;
    SYSKEY=0xFE0;
    
    //Configuracion OC1
    OC3CON=0; //Primero apagado
    OC3R=2500;  // A DECIDIR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    OC3RS=2500;
    OC3CON =0x0006; //off, PWM sin faltas
    
    T2CON = 0;
    TMR2 = 0;
    PR2 = PERIODO-1; //50 us 
    T2CON = 0x0010; //Que empiece apagado
    
    
}

// AHORA LOGICA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//Una relacion lineal quizas no sea la mejor (la bombilla retiene el calor)
//Podemos probar con un control PI

float Kp = 15.0; //kp original 15
float Ki = 0.36; //ki 0.36
float error_integral = 0.0;
float dt = 1; // cada segundo

// LLAMAR CUANDO HAYA UNA MUESTRA
int controlar_brillo(float temperatura_deseada, float temperatura_actual) {
    float error = temperatura_deseada - temperatura_actual;
    
    // Integración del error
    error_integral += error * dt;

    // Cálculo de salida PI
    float salida = Kp * error + Ki * error_integral;

    // Saturacion de  fuera de [0, 100]
    if (salida > 100.0) {
        salida = 100.0;
    }
    if (salida < 0.0){
        salida = 0.0;
    }

    // minimo del 50%
    int brillo_pwm = (salida >= 50.0) ? (int)salida : 0;
    //if (error>=0.75 && brillo_pwm==0){
    //    brillo_pwm=max(brillo_pwm,70);
    //}
    // Aquí devolveríamos el valor de brillo que usaría el PWM (por ejemplo OC1RS)
    return brillo_pwm;
}


void setBrillo(int porcentaje){
    alto=porcentaje*PERIODO/100;
    OC3RS=alto;
}
void startBombilla(){
    OC3CON |= 0x8000;
    TMR2=0; //Por si acaso
    T2CON |=0x8000;
}
void stopBombilla(){
    OC3CON &= ~0x8000;
    T2CON  &= ~0x8000;
}
int getBrillo(){
    int sol;
    asm("di");
    sol=alto*100/PERIODO;
    asm("ei");
    return sol;
}
