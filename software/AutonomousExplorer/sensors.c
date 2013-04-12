/*
 * sensor.c
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
#include "sensors.h"


//returns all adc data
void getRangeData(double *frontLeft, double *frontRight, double *left, double *right)
{
IOWR_ALTERA_AVALON_PIO_DATA( CHAIN_INIT_BASE,1);
OSTimeDlyHMSM(0, 0, 0, 50);
IOWR_ALTERA_AVALON_PIO_DATA( CHAIN_INIT_BASE,0);

  *frontLeft=(double)getSensor(3);
      OSTimeDlyHMSM(0, 0, 0,1);
  *left=getSensor(1);
      OSTimeDlyHMSM(0, 0, 0,1);
  *frontRight=getSensor(2);
      OSTimeDlyHMSM(0, 0, 0,1);
  *right=getSensor(4);
      OSTimeDlyHMSM(0, 0, 0,1);
}

//adc individual read/conversion
float getSensor(int nextSensor) {
    alt_u16 data16 = ADC_Read(nextSensor);
    return (float) data16 * 3.3 / 4095.0 / INCHES_PER_VOLT;
}

//returns comapss heading
float getHeading() {
    alt_u8 buf[2];
    I2C_MultipleRead(COMPASS_SCL_BASE, COMPASS_SDA_BASE, COMPASS_ADDRESS, 0x00, buf, sizeof(buf));
    return (float) (((int) buf[0] << 8) + ((int) buf[1])) / 10;
}

void sensorsInit()
{
    //ultrasonic sensor set
	//chain set up and change off first adc read from stall sensor to rangefidner
   IOWR_ALTERA_AVALON_PIO_DATA( CHAIN_INIT_BASE,1);
     OSTimeDlyHMSM(0, 0, 0, 50);
     IOWR_ALTERA_AVALON_PIO_DATA( CHAIN_INIT_BASE,0);
   ADC_Read(4);

  

}

