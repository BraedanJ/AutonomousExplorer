/*
 * rover.h
 *
 *  Created on: Apr 4, 2013
 *      Author: Michael Jun
 */

#ifndef ROVER_H_
#define ROVER_H_


#define PWM_TOTAL_CYCLES    312500
#define WHEEL_DIAMETER      6.2
#define PULSES_PER_ROTATION 166.666666667

#define QUATERTURN 25.3
#define EIGHTHTurn 13.5



void roverInit();
void roverCommand(int direction,float speed);
void setPWM(int PWMBase, float percentage, int direction) ;
void drive(int direction, float speed);
void stop();



double getEncoderDistance(int encoderBase);

void getAllEncoderDistances(double *encoder_FL,double *encoder_BL, double *encoder_FR, double *encoder_BR);
void turn90(int direction, float speed);
void turn(int direction, float speed);
double getDistance();



#endif /* ROVER_H_ */
