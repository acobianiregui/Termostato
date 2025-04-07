/* 
 * File:   UART.h
 * Author: 34648
 *
 * Created on 20 de febrero de 2025, 23:28
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif
#define TAMANO_COLA 100
typedef struct {
    int cabeza; // Marca el índice de la cabeza
    int cola;
    char datos[TAMANO_COLA];
} cola_circ;
static cola_circ cola_tx, cola_rx;
void InicializarUART(int baudios);
char getcUART(void);
void putsUART(char* ps);
void InterupcionUART();

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

