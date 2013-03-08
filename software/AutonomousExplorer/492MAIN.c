/*************************************************************************
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.      *
* All rights reserved. All use of this software and documentation is     *
* subject to the License Agreement located at the end of this file below.*
**************************************************************************
* Description:                                                           *
* The following is a simple hello world program running MicroC/OS-II.The * 
* purpose of the design is to be a very simple application that just     *
* demonstrates MicroC/OS-II running on NIOS II.The design doesn't account*
* for issues such as checking system call return codes. etc.             *
*                                                                        *
* Requirements:                                                          *
*   -Supported Example Hardware Platforms                                *
*     Standard                                                           *
*     Full Featured                                                      *
*     Low Cost                                                           *
*   -Supported Development Boards                                        *
*     Nios II Development Board, Stratix II Edition                      *
*     Nios Development Board, Stratix Professional Edition               *
*     Nios Development Board, Stratix Edition                            *
*     Nios Development Board, Cyclone Edition                            *
*   -System Library Settings                                             *
*     RTOS Type - MicroC/OS-II                                           *
*     Periodic System Timer                                              *
*   -Know Issues                                                         *
*     If this design is run on the ISS, terminal output will take several*
*     minutes per iteration.                                             *
**************************************************************************/


#include <stdio.h>
#include "system.h"
#include "includes.h"
#include "generate.h"
#include "altera_avalon_pio_regs.h"

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
#define   FORWARD 0
#define   LEFT 1
#define   RIGHT 2
#define PI 3.14159265
#define TOO_CLOSE 25

OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2


#define TEST 1
void * MyQueue[ 100 ];

OS_EVENT *QueueEvent;
OS_EVENT *NewData;
void * RawData[ 100 ];

void mapData(double front,double left, double right,int angle, int command);


/* Prints "Hello World" and sleeps for three seconds */
void task1(void* pdata)
{
 int testData=TEST;

 INT8U  err=OS_NO_ERR;
 char sValue[256];
double data[4];
  char *LEDS=GREED_LEDS_BASE;
  if(testData==1)
  {
      else if(testData==1)
          {
          int a=0;
           int counter=0;
          double front[1000];
          double left[1000];
          double right[1000];
          int angles[1000];
          int test[1000];
         counter= GenerateTestData(front,left,right,angles,test,a);
          for(a=0;a<=counter;a++)
          {
          *LEDS =0xf0;
          OSTimeDlyHMSM(0, 0, 0, 500);
           *LEDS =0x0f;
         OSTimeDlyHMSM(0, 0, 0, 500);
       sprintf(sValue,"%lf %lf %lf %d %d",front[a],left[a],right[a],angles[a],test[a]);
          }
          }
  }
  
  while (1)
  { 
          *LEDS =0xff;
          OSTimeDlyHMSM(0, 0, 0, 500);
      
          int a=0;
          for (a=0;a<5;a++)
          {
       //     data[a]=ADC_Read(a+1)
            
          }
       
       // sprintf(sValue,"%lf %lf %lf %d",data[0],data[1],data[2],data[3]);
        err=OSQPost(NewData, (void *) sValue);
          *LEDS =0x00;
          OSTimeDlyHMSM(0, 0, 0, 500);

  }

}

//lcd task
void task2(void* pdata)
{
    void* data;
    int testData=TEST;
    int compass=0;
    double front=0;
    double left=0;
    double right=0;
    int test=0;
    int turnAngle=0;
    int command=FORWARD;

    INT8U  err=OS_NO_ERR;
    while(1)
    {

    data=OSQPend(NewData, 0,&err);

    if (testData==1)
    {
     sscanf((char*) data, "%lf %lf %lf %d %d ", &front,&left,&right,&compass,&test);
    printf(" %lf %lf %lf %d %d: \n",front,left,right,compass,test);
    }
    else
    {
    
    sscanf((char*) data, "%lf %lf %lf %d", &front,&left,&right,&compass);
    printf(" %lf %lf %lf %d:: \n",front,left,right,compass);
    }

      if(command==FORWARD)
      {
        if(front<=TOO_CLOSE)
        {
          if(left>right&&left>TOO_CLOSE)
          {
            turnAngle=compass;
            command=LEFT;
          }
          else if(right>left&&right>TOO_CLOSE)
           {
            turnAngle=compass;
            command=RIGHT;
           }
          }
       else if (left<TOO_CLOSE)
       {
            //to be later implmented
       }
       else if( right<TOO_CLOSE)
       {
         //to be later implmented
       }
       else
       {
        //drive forward
       }

     }
      else if(command==LEFT)
      {
          if(abs(turnAngle-compass)>=90)
          {
          command=0;
          }
          else
          {
                  //insert left command
          }
      }
      else if(command==RIGHT)
      {
          if(abs(turnAngle-compass)>=90)
          {
          command=0;

          }
          else
          {
                  //insert right command
          }
   

      }
    if(testData==1)
    {
        if(test!=command)
        {
            printf("ERROR!!!! command= %d test comand= %d \n",command,test);
        }
    }
 //mapData(front,left,  right, angle,  command)
}
}






void mapData(double front,double left, double right,int angle, int command)
{

double CarPosition[10000][2];
double LeftSensor[10000][2];
double RightSensor[10000][2];

static int a=0;



if(command==FORWARD)
{
CarPosition[a][0]= cos((Angle+90)*PI/180)*DistanceTraveled+CarPosition[a][0];
CarPosition[a][1]=sin((Angle+90)*PI/180)*DistanceTraveled+CarPosition[a][1];
}
LeftSensor[a][0]=cos((Angle+180)*PI/180)*left+CarPosition[a][0];
LeftSensor[a][1]=sin((Angle+180)*PI/180)*left+CarPosition[a][1];
RightSensor[a][0]=cos((angles)*PI/180)*right+CarPosition[a][0];
RightSensor[a][1]=sin((angle)*PI/180)*rightar+CarPosition[a][1];
a++;

}




/* The main function creates two task and starts multi-tasking */
int main(void)
{



QueueEvent= OSQCreate( &MyQueue[0], 100 );

NewData= OSQCreate( &RawData[0], 100 );


  OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
              
               
  OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
 

  OSStart();
  return 0;
}



/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2004 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
******************************************************************************/

