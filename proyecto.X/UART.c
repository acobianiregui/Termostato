#include <xc.h>
#include "Pic32Ini.h"
//Modulo UART

//Definimos un struct para facilitar las colas
#define TAMANO_COLA 100
typedef struct{
    int cabeza; //Marca el indice de la cabeza
    int cola;
    char datos[TAMANO_COLA];
} cola_circ;

//////////////////////////////////////////
static cola_circ cola_tx, cola_rx;


void InicializarUART(int baudios){
    //Definimos puertos
    //U1RX a RB2 y U1TX a RA0
    ANSELB &=~((1<<2));
    ANSELA &=~1;
    TRISB |=(1<<2);
    TRISA &=~1;
    LATA |=1;
    // Se desbloquean los registros
    SYSKEY=0xAA996655; 
    SYSKEY=0x556699AA;
    U1RXR = 4; //Consultar tabla tema 4
    RPA0R = 1;
    SYSKEY=0x1CA11CA1;
    
    //Calculo de la UXBRG (Tasa de comunicacion)
    if (baudios>38400){
        U1MODEbits.BRGH = 1;
        U1BRG=((5*1000*1000)/(4*baudios));
    }else{
        U1MODEbits.BRGH = 0;
        U1BRG=((5*1000*1000)/(16*baudios));
    }
    
    IFS1bits.U1RXIF=0; //Se borra el flag por si acaso
    IEC1bits.U1RXIE=1; //Habilito interrupciones
    IFS1bits.U1TXIF=0; //Tambien por si acaso
    IPC8bits.U1IP=3; //Prioridad 3
    IPC8bits.U1IS = 1; //Subprioridad 1 (por ejemplo)
    
    U1STAbits.URXISEL=0; //Interrupcion cuando haya un char
    U1STAbits.UTXISEL=2; //Interrumpe cuando FIFO esta vacio
    U1STAbits.URXEN=1; //Habilita el recepttor
    U1STAbits.UTXEN=1; //El transmisor
    
    //Modo multivec en main
    
    
    U1MODE |=0x8000; //Enciende UART
    
}

//Rutina de interrupcion
__attribute__((vector(32),interrupt(IPL3SOFT),nomips16))
void InterupcionUART(){
    //Puede interrumpir el transmisor o el receptor
    
    //Posibilidad 1: transmisor
    if(IFS1bits.U1TXIF==1){
        if(cola_tx.cabeza != cola_tx.cola){//Hay cosas que mandar
            U1TXREG= cola_tx.datos[cola_tx.cola];
            cola_tx.cola++;
            if(cola_tx.cola==TAMANO_COLA){
                cola_tx.cola=0;
            } 
        }else{
            //No hay nada que activar
            IEC1bits.U1TXIE = 0;
        }
        //Ha acabo el transmisor
        IFS1bits.U1TXIF=0; //Apagamos flag
    }
    //Posibilidad 2: receptor
    if(IFS1bits.U1RXIF==1){
        if((cola_rx.cabeza +1 ==cola_rx.cola)||
                (cola_rx.cabeza +1 ==TAMANO_COLA && cola_rx.cola==0)){
            //Cola llena 
        }else{
            cola_rx.datos[cola_rx.cabeza]=U1RXREG; //Lee dato
            cola_rx.cabeza ++;
            if (cola_rx.cabeza==TAMANO_COLA){
                cola_rx.cabeza=0;
            }
        }
        //Hemos acabado con el receptor
        IFS1bits.U1RXIF = 0; 
    }
}

//Ahora funciones get y put

char getcUART(void){
    char c;
    if(cola_rx.cabeza != cola_rx.cola){ //Datos nuevos
        c= cola_rx.datos[cola_rx.cola];
        cola_rx.cola++; //Adelantamos la cola
        if (cola_rx.cola==TAMANO_COLA){
            cola_rx.cola=0; //Reseteamos indice
        }
    }else{ //No hay nada nuevo
        c='\0';
    }
    return c;
}

void putsUART(char* ps ){
    while((*ps!='\0')&&(ps!= NULL )){ //Cuando se lea /0 se acaba la secuencia a escribir
        if((cola_tx.cabeza +1 ==cola_tx.cola)||
                (cola_tx.cabeza +1 ==TAMANO_COLA && cola_tx.cola==0)){
            break ;//Cola llena, abortar
        }else{
            cola_tx.datos[cola_tx.cabeza]= *ps;//Escribe el elemento al que apunta
            ps++; //Apunta al siguiente
            cola_tx.cabeza++;
            if(cola_tx.cabeza==TAMANO_COLA){
                cola_tx.cabeza=0;
            }
        }
    }
    IEC1bits.U1TXIE = 1;//Se habilita interrupcion para enviar

}