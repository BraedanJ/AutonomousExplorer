/*
 * rover.c
 *
 *  Created on: Apr 4, 2013
 *      Author: Michael Jun
 */





#include <stdio.h>
#include "includes.h"
#include "terasic_lib/terasic_includes.h"
#include "terasic_lib/adc_spi_read.h"
#include "terasic_lib/I2C.h"

#include "explorer.h"

#include "rover.h"


//send the motor command
void roverCommand(int direction, float speed) {
	if (direction == FORWARD || direction == REVERSE) {
		drive(direction, speed);
	} else if (direction == LEFT || direction == RIGHT) {
		turn(direction, speed);
	}
	getDistance();

}

//takes the average distance of all encoders
double getDistance() {
	double encoder_FL, encoder_BL, encoder_FR, encoder_BR;
	getAllEncoderDistances(&encoder_FL, &encoder_BL, &encoder_FR, &encoder_BR);
	double average = ( encoder_FL+ encoder_BL + encoder_FR + encoder_BR) / 4;
	return average;

}
//sets with the encoders up
void roverInit() {
	getEncoderDistance(ENCODER_BACK_LEFT_BASE);
	getEncoderDistance(ENCODER_BACK_RIGHT_BASE);
	getEncoderDistance(ENCODER_FRONT_LEFT_BASE);
	getEncoderDistance(ENCODER_FRONT_RIGHT_BASE);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//get all encoder distances
void getAllEncoderDistances(double *encoder_FL, double *encoder_BL,
		double *encoder_FR, double *encoder_BR) {
	*encoder_BL = getEncoderDistance(ENCODER_BACK_LEFT_BASE);
	*encoder_BR = getEncoderDistance(ENCODER_BACK_RIGHT_BASE);
	*encoder_FL = getEncoderDistance(ENCODER_FRONT_LEFT_BASE);
	*encoder_FR = getEncoderDistance(ENCODER_FRONT_RIGHT_BASE);
}
//read encoders
//encoder are set up to be read from net change based on last read
//
double getEncoderDistance(int encoderBase) {
	static int encoder_FL = 0;
	static int encoder_BL = 0;
	static int encoder_FR = 0;
	static int encoder_BR = 0;

	int nPulses = (int) IORD(encoderBase, 0);
	int temp = nPulses;
	switch (encoderBase) {
	case ENCODER_BACK_LEFT_BASE:
		//   printf ("BACK LEFT: %d %d %d\n",nPulses,encoder_BL,temp);
		nPulses = nPulses - encoder_BL;
		encoder_BL = temp;
		break;
	case ENCODER_BACK_RIGHT_BASE:
		nPulses = nPulses - encoder_BR;
		encoder_BR = temp;
		break;
	case ENCODER_FRONT_LEFT_BASE:
		nPulses = nPulses - encoder_FL;
		encoder_FL = temp;
		break;
	case ENCODER_FRONT_RIGHT_BASE:
		nPulses = nPulses - encoder_FR;
		encoder_FR = temp;
		break;
	default:
		break;
	}

	return nPulses * PI * WHEEL_DIAMETER / PULSES_PER_ROTATION;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//set PWM with direction pins
void setPWM(int PWMBase, float percentage, int direction) {
	

    if (PWMBase == PWM_LEFT_BASE) {
		IOWR_ALTERA_AVALON_PIO_DATA(DIR_LEFT_BASE, direction);
	}
	if (PWMBase == PWM_RIGHT_BASE) {
		IOWR_ALTERA_AVALON_PIO_DATA(DIR_RIGHT_BASE, direction);
	}
	
	
    percentage=percentage/100;
	IOWR(PWMBase, 0, percentage * PWM_TOTAL_CYCLES);
}
//drives forward with speed adjusmenet of 80.5
void drive(int direction, float speed) {
int adjusment=80.5
	if (direction == FORWARD || direction == REVERSE) {
        setPWM(PWM_RIGHT_BASE, speed, direction);
		setPWM(PWM_LEFT_BASE, speed* adjusment, direction);
		
	} else {
		printf("invalid direction for drive command \n");
	}

}
//turns 90 degree based on encoders
void turn90(int direction,float speed)
{
    double distance=getDistance();

	if(direction==LEFT)
	{
		printf("left\n");
	setPWM(PWM_LEFT_BASE, speed - 20, 1);
	 setPWM(PWM_RIGHT_BASE, speed,0);
	}
	else
	{
		printf("right\n");
		setPWM(PWM_LEFT_BASE, speed - 20, 0);
			setPWM(PWM_RIGHT_BASE, speed, 1);
	}
	while (1) {
	         distance+=getDistance();
				if (distance > QUATERTURN ) {

					break;
				}
	             OSTimeDlyHMSM(0, 0,0,100);

			}
			stop();
			getDistance();
}
void turn(int direction, float speed) {


	if(direction==LEFT)
	{

	setPWM(PWM_LEFT_BASE, speed, 1);
	 setPWM(PWM_RIGHT_BASE, speed,0);
	}
	else
	{

		setPWM(PWM_LEFT_BASE, speed, 0);
			setPWM(PWM_RIGHT_BASE, speed, 1);
	}

}
void stop() {

	setPWM(PWM_LEFT_BASE, 0, 1);
	setPWM(PWM_RIGHT_BASE, 0, 1);
}
/*
 *  int encoder_FL = 0;
    int encoder_BL = 0;
    int encoder_FR = 0;
    int encoder_BR = 0;
        getEncoderDistance(ENCODER_BACK_LEFT_BASE);
      getEncoderDistance(ENCODER_BACK_RIGHT_BASE);
      getEncoderDistance(ENCODER_FRONT_LEFT_BASE);
      getEncoderDistance(ENCODER_FRONT_RIGHT_BASE);
       double distance=getDistance();
    if(direction==LEFT)
    {
    setPWM(PWM_LEFT_BASE, speed - 20, 1);
     setPWM(PWM_RIGHT_BASE, speed,0);
    }
    else
    {
        setPWM(PWM_LEFT_BASE, speed - 20, 0);
            setPWM(PWM_RIGHT_BASE, speed, 1);
    }
    if (degreeChange == 90) {
        while (1) {
         encoder_BL+= getEncoderDistance(ENCODER_BACK_LEFT_BASE);
        encoder_BR+= getEncoderDistance(ENCODER_BACK_RIGHT_BASE);
         encoder_FL+=getEncoderDistance(ENCODER_FRONT_LEFT_BASE);
        encoder_FR+=getEncoderDistance(ENCODER_FRONT_RIGHT_BASE);
            if (encoder_FL > QUATERTURN && encoder_BL > QUATERTURN
                    && encoder_FR > QUATERTURN && encoder_BR > QUATERTURN) {
 
                break;
            }
             OSTimeDlyHMSM(0, 0,0,100);
            
        }
        stop();
    }*/
