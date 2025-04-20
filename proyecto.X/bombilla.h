/* 
 * File:   bombilla.h
 * Author: 34648
 *
 * Created on 7 de abril de 2025, 19:06
 */

#ifndef BOMBILLA_H
#define	BOMBILLA_H

#ifdef	__cplusplus
extern "C" {
#endif

void initBombilla();
void startBombilla();
void setBrillo(int porcentaje);
int controlar_brillo(float temperatura_deseada, float temperatura_actual);
void stopBombilla();
int getBrillo();

#ifdef	__cplusplus
}
#endif

#endif	/* BOMBILLA_H */

