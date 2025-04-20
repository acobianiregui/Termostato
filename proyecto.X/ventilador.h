/* 
 * File:   ventilador.h
 * Author: Usuario
 *
 * Created on 19 de abril de 2025, 10:08
 */

#ifndef VENTILADOR_H
#define	VENTILADOR_H

#ifdef	__cplusplus
extern "C" {
#endif

void initVentilador();
int controlar_velocidad(float temperatura_deseada, float temperatura_actual);
void setVelocidad(int velocidad);
void Ventilador_Start(void);
void Ventilador_Stop(void);
void InterrupcionTimer4(void);

#ifdef	__cplusplus
}
#endif

#endif	/* VENTILADOR_H */