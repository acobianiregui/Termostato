/* 
 * File:   sensor.h
 * Author: 34648
 *
 * Created on 23 de marzo de 2025, 14:43
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

void initSensor();
void InterrupcionADC(void);
void startADC();
float conversionVaT(float Vmedida);
float getTemperatura();
int existeMedia();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */

