/*
 * sensors.h
 *
 *  Created on: Apr 4, 2013
 *      Author: Michael Jun
 */

#ifndef SENSORS_H_
#define SENSORS_H_



#define INCHES_PER_VOLT     0.006445313
#define COMPASS_ADDRESS     0x42

void getRangeData(double *frontLeft, double *frontRight, double *left, double *right);
float getSensor(int nextSensor);
float getHeading();
void sensorsInit();





#endif /* SENSORS_H_ */
