#include <stdio.h>
#include "includes.h"
#include "terasic_lib/terasic_includes.h"
#include "terasic_lib/adc_spi_read.h"
#include "terasic_lib/I2C.h"
#include "system.h"
#include "math.h"
#include "altera_avalon_pio_regs.h"

#include "explorer.h"
/*
 #include "test.h"
 #include "generate.h"
 */
#include "test.h"
#include "sensors.h"
#include "rover.h"
#include "map.h"



OS_EVENT *NewData;
void * RawData[100];


/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK task1_stk[TASK_STACKSIZE];
OS_STK task2_stk[TASK_STACKSIZE];


/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2


/* Prints "Hello World" and sleeps for three seconds */
void task1(void* pdata) {
	int testmode=11;
	INT8U err = OS_NO_ERR;
	char data[256];
	int *power = (int*) GO_BASE;
	double frontL, frontR, right, left;

	double distance;
	int button;
	*buttonChange = 0;
	roverInit();
    int *button1=(int *)DATA_OUTPUT_BASE;
//set up calls
	roverInit();
	sensorsInit();
	while (1) {
		
		//checks the swtich and whether to run a test progrma or not
		if (*power == 1) {
			if (testmode == 1) {
				printf("Testmode\n");

//RANGEFINDERS 0  COMPASS 1  ROVER 2  ROVER1 3  DRIVE 4
test(COMPASS);

				OSTimeDlyHMSM(0, 0, 2, 000);
			} else { //gets all sensor data and post htem

				printf("...");
			getRangeData(&frontL, &frontR, &right, &left);
				distance=getDistance();


			//	sprintf(data, "%lf %lf %lf %lf %lf %f", frontL, frontR, right, left,
									//distance,compass);
				sprintf(data, "%lf %lf %lf %lf %lf", frontL, frontR, right, left,
						distance);

				err = OSQPost(NewData, (void *) data);
				OSTimeDlyHMSM(0, 0, 0, 300);
			}

		} else {
           
          // int testButton = IORD(DATA_OUTPUT_BASE, 0x3);
           
			  stop();
			button = *buttonChange;
			printf("%d \n",button);
   
			if (button == 1) {
                //IOWR(DATA_OUTPUT_BASE, 0x3, 0x1);
				*buttonChange = 0;
		          printData();

		    //   OSTimeDlyHMSM(0, 0, 1, 100);
			}
		     OSTimeDlyHMSM(0, 0, 1, 100);
		}

	}
}

/* Prints "Hello World" and sleeps for three seconds */
void task2(void* pdata) {

	INT8U err = OS_NO_ERR;
	void * data;
	double frontL, frontR, right, left,distance;
//int command=-1;
	static double angle = 0;
	pt * position;

	pt * leftCoord;

	pt * rightCoord;

	int *count;
	count=COUNT_BASE;
	pt currentPosition;
	int *power=(int*) GO_BASE;  //set up start delay so data does not reset on start up
	while(*power!=1)
	{

		  OSTimeDlyHMSM(0, 0, 1, 0);
	}
	*count=0;
	currentPosition.x=0;
	currentPosition.y=0;
	position=calloc(1000,sizeof(pt));
	leftCoord=calloc(1000,sizeof(pt));
	rightCoord=calloc(1000,sizeof(pt));
	*POSITION_BASE=position;
	*RIGHT_COORD_BASE=rightCoord;
	*LEFT_COORD_BASE=leftCoord;
	int command;
//sets teh user set locations in sdram in memeory with new poitners of 1000 data points

	while (1) {
		data = OSQPend(NewData, 0, &err);
		sscanf((char*) data, "%lf %lf %lf %lf %lf", &frontL, &frontR, &right, &left,
				&distance);


	angle+=processDataNC(frontL, frontR, left,right);  //set up in no compas(NC) returns assumed angle change and commsn rover in function
	//command=processDatA(frontL,frontR,left,right,compass); //this function uses the compass and returns with the drive command for hte motors
		position[*count]=convert(distance, angle + 90, currentPosition); //updates positon
		currentPosition.x=position[*count].x;
		currentPosition.y=position[*count].y;
		rightCoord[*count]=convert(right, angle, currentPosition);
		leftCoord[*count]=convert(left, angle + 180,currentPosition);

		*count=*count+1;
		  OSTimeDlyHMSM(0, 0, 0, 50);
	}
}
/*
void interrupt_isr_name( void * context, alt_u32 id) {
    char *LEDS=(char *) LED_BASE;

    *LEDS =~*LEDS;
    stop();
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(GO_BASE, 0xF);
    	IOWR_ALTERA_AVALON_PIO_EDGE_CAP( GO_BASE, 0);
}

/* The main function creates two task and starts multi-tasking */
int main(void) {

//used for passing data between the 2 task
	NewData = OSQCreate(&RawData[0], 100);



	OSTaskCreateExt(task1, NULL, (void *) &task1_stk[TASK_STACKSIZE - 1],
			TASK1_PRIORITY, TASK1_PRIORITY, task1_stk, TASK_STACKSIZE, NULL, 0);

	OSTaskCreateExt(task2, NULL, (void *) &task2_stk[TASK_STACKSIZE - 1],
			TASK2_PRIORITY, TASK2_PRIORITY, task2_stk, TASK_STACKSIZE, NULL, 0);

	OSStart();


	return 0;
}



/*Prints the data out from SDRAM
 * must be in debug mode
 *
 *
 */
void printData()
{
	int* button;
	button= COUNT_BASE;
	pt * position;
	position=*POSITION_BASE;
	pt * leftCoord;
	leftCoord=*LEFT_COORD_BASE;
	pt * rightCoord;
	rightCoord=*RIGHT_COORD_BASE;
	FILE* fp;
	fp=fopen("/mnt/host/data.txt","w");
	if(fp!=NULL)
	{
	printf("DATA OUTPUT %d\n",button[0]);
	int a=0;
	for(a=0;a<button[0];a++)
	{

	fprintf(fp,"Position\t%lf\t%lf\t\t",position[a].x,position[a].y);
	fprintf(fp,"Left Coord\t%lf\t%lf\t\t",leftCoord[a].x,leftCoord[a].y);
	fprintf(fp,"Right Coord\t%lf\t%lf\t\t",rightCoord[a].x,rightCoord[a].y);
	fprintf(fp,"number\t%d\n",a);
	}
	free(position);
	free(leftCoord);
	free(rightCoord);
	fclose(fp);
	}
}
