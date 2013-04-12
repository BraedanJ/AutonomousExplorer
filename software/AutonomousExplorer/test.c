#include <stdio.h>

#include "includes.h"
#include "terasic_lib/terasic_includes.h"
#include "terasic_lib/adc_spi_read.h"
#include "terasic_lib/I2C.h"
#include "system.h"


#include "rover.h"
#include "explorer.h"
#include "sensors.h"
#include "test.h"
#include "map.h"


#include "math.h"
#include "altera_avalon_pio_regs.h"

void test(int type)
{
	double frontLeft, frontRight,left, right;
	double encoderFL,encoderFR, encoderBL,encoderBR;
	roverInit();
	sensorsInit();


//printf the ADC data
 if(type==RANGEFINDERS)
{
   getRangeData( &frontLeft, &frontRight,&left,& right);
   printf("front left=%lf front right=%lf left=%lf right=%lf %d \n", frontLeft, frontRight,left, right);

}//compass heading
 else if(type==COMPASS)
 {

	float data=getHeading();
	printf("compass=%f\n",data);
 }
 //invidual cnecoder read
else if(type==ENCODER)
{
	   encoderBL= getEncoderDistance(ENCODER_BACK_LEFT_BASE);
	   encoderBR= getEncoderDistance(ENCODER_BACK_RIGHT_BASE);
	   encoderFL=getEncoderDistance(ENCODER_FRONT_LEFT_BASE);
	 	 encoderFR=getEncoderDistance(ENCODER_FRONT_RIGHT_BASE);
	    printf("Encoder BL: %lf \n",encoderBL);
	    printf("Encoder BR: %lf \n",encoderBR);
	    printf("Encoder FL: %lf \n",encoderFL);
	    printf("Encoder FR: %lf \n",encoderFR);

}

 //test through all possible rover drive commands
else if (type==ROVER_COMMANDS)
{
    printf("Drive Functions \n");
    /////
    printf("FORWARD\n");
	 drive(FORWARD,100);
	OSTimeDlyHMSM(0, 0, 2, 0);
	printf("STOP\n");
    stop();
	OSTimeDlyHMSM(0, 0, 2, 000);
    ///////////
    printf("LEFT... \n");
    OSTimeDlyHMSM(0, 0, 2, 000);
	turn(LEFT,100);
	OSTimeDlyHMSM(0, 0, 2, 000);
	printf("STOP\n");
	stop();
	OSTimeDlyHMSM(0, 0, 2, 000);
	///////////
	printf("RIGHT...");
	turn(RIGHT,100);
	OSTimeDlyHMSM(0, 0, 2, 000);
	printf("STOP\n");
	stop();
  OSTimeDlyHMSM(0, 0, 2, 000);
  ////////////
    printf("REVERSE...");
   drive(REVERSE,100);
   OSTimeDlyHMSM(0, 0, 2, 000);
    printf("STOP\n");
    stop();
    OSTimeDlyHMSM(0, 0, 2, 000);
}
else if(type==DRIVE) //dodges obsticale no mapping
{
printf("DUMMY DRIVE\n");
   int *power = (int*)GO_BASE;
while(1)
{
    
       if(*power==1)
      {
 getRangeData( &frontLeft, &frontRight,&left,& right);
	printf("front left=%lf front right=%lf left=%lf right=%lf %d \n", frontLeft, frontRight,left, right);
    if(frontRight<MIN_DISTANCE||frontLeft<MIN_DISTANCE)
    {
        if(left>10&&left>right)
        {
         turn90(LEFT,60);

        }
          else if(right>10&&left<right)
        {
        turn90(RIGHT,60);
        }
        else
        {
            
        printf("stop\n");
        OSTimeDlyHMSM(0, 0, 0, 500);
        turn90(RIGHT,60);
        turn90(RIGHT,60);
       OSTimeDlyHMSM(0, 0, 1, 0);
        }
    }
    else
    {
           drive(FORWARD,100);
    }
      }
      else
      {
        stop();
      }
   OSTimeDlyHMSM(0, 0, 0, 300);
    
}

}
}






void calibrate(int type)
{
if(type==TURN)
{
	int direction=LEFT;
	int speed=100;
       roverInit();
       sensorsInit();
	int encoder_FL = 0;
	int encoder_BL = 0;
	int encoder_FR = 0;
	int encoder_BR = 0;
int adjusment=25; //turning distance calacibraiton value
       double distance=getDistance();
      double backLeft,backRight,frontRight,frontLeft;
	if(direction==LEFT)
	{
	setPWM(PWM_LEFT_BASE, speed , 1);
	 setPWM(PWM_RIGHT_BASE, speed,0);
	}
	else
	{
		setPWM(PWM_LEFT_BASE, speed , 0);
		setPWM(PWM_RIGHT_BASE, speed, 1);
	}
	 getRangeData(&frontLeft, &backLeft,&backRight, &frontRight);
	    printf("BEFORE:fl=%lf fr=%lf bl=%lf br=%lf \n",frontLeft, frontRight, backLeft, backRight);
		while (1) {
         distance+=getDistance();
			if (distance > adjusment) {

				break;
			}
			getAllEncoderDistances(&encoder_FL,&encoder_BL,&encoder_FR,&encoder_BR);
           OSTimeDlyHMSM(0, 0,0,100);

		}
	getRangeData(&frontLeft, &backLeft,&backRight, &frontRight);
	printf("AFTER:fl=%lf fr=%lf bl=%lf br=%lf \n",frontLeft, frontRight, backLeft, backRight);
	printf("FRONT:R= %lf L=%lf BACK:R= %lf L= %lf\t avg= %lf",encoder_FR,encoder_FL,encoder_BR,encoder_BL,distance);
	printf("left side sum: %d, right side sum: %d\n\n",(encoder_FL+encoder_BL)/2,(encoder_FR+encoder_BR)/2);
	stop();
	}

if(type==FORWARD) //test how strong each side has to be for straight forward driving
{
	int a=0;
	for(a=0;a<20;a+=5)
	{
	setPWM(PWM_LEFT_BASE, 85-a, 1);
	setPWM(PWM_RIGHT_BASE, 100, 1);
	 OSTimeDlyHMSM(0, 0, 5, 50);
}
}


}



void buttonTest() //making sure hte top buttons work
{

   int *power = (int*)GO_BASE;
   int button;
   *buttonChange = 0;
 while (1)
 {
   
       button = *buttonChange;
          printf("switch =%d, button=%d\n",*power,button);


           if (button == 1) {
        	   *buttonChange = 0;
        	      if (*power == 1)
        	           {
        	    	  return;
        	           }
           }

               OSTimeDlyHMSM(0, 0, 1, 100);

     }






}
