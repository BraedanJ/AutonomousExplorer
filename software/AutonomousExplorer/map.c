/*
 * map.cpp
 *
 *  Created on: Mar 23, 2013
 *      Author: Michael Jun
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "map.h"
#include "explorer.h"
#include "rover.h"

#define TOO_CLOSE 10



int processData(double frontL, double frontR, double left, double right,double angle)
{
	static int command=FORWARD;
	   static double turnAngle=0;
if(command==FORWARD)
{
	if(frontL<MIN_DISTANCE||frontR<MIN_DISTANCE)
	{
		        if(left>MIN_DISTANCE*1.5&&left>right)
		        {
		            turnAngle=angle;
		                command=LEFT;

		                return LEFT;
		        }
		          else if(right>MIN_DISTANCE&&left<right)
		        {
		              turnAngle=angle;
		                   command=RIGHT;

		                   return RIGHT;
		        }
		        else
		        {
		        	//would implment backtracking here if was working

		    //    OSTimeDlyHMSM(0, 0, 1, 0);
		        }
		  }
		    else
		    {

		    }

}
//rover checks for change of 90 degrees
else if(command==LEFT)
   {
       if((angle-turnAngle)>=90)
       {

      command=FORWARD;
       }
       else
       {

 // 	 *led=0xE0;
       return LEFT;
       }
   }
   else if(command==RIGHT)
   {
       if(turnAngle-angle>=90)
       {


       command=FORWARD;

       }
       else
       {
     	//  *led=0x07;
       }
       return RIGHT;
    }
return FORWARD;
}

//changes rover direction based on if rover too close
int processDataNC(double frontL, double frontR, double left, double right)
{

	    if(frontL<MIN_DISTANCE||frontR<MIN_DISTANCE)
	    {
	        if(left>MIN_DISTANCE*1.5&&left>right)
	        {
	          turn90(LEFT,100);
	          return 90;
	        }
	          else if(right>MIN_DISTANCE&&left<right)
	        {
	         turn90(RIGHT,100);
	         return -90;
	        }
	        else
	        {
	        printf("stop\n");
	           turn90(RIGHT,100);
	            turn90(RIGHT,100);
	            return -180;
	    //    OSTimeDlyHMSM(0, 0, 1, 0);
	        }
	    }
	    else
	    {
	           drive(FORWARD,100);
	           return 0;
	    }


	         OSTimeDlyHMSM(0, 0, 0, 50);


return 0;
}

//coverts the scalar data into vector
pt convert(double scalar, double angle,pt position) {
pt vector;
	vector.x = cos((angle ) * PI / 180) * scalar + position.x;

	vector.y = sin((angle ) * PI / 180) * scalar + position.y;

	return vector;
}

//to be impletned later
int checkExistingIntersection(int *opening, int *side) {
	int a = 0;
	int b = 0;
/*
	for (a = 0; a < openingCount; a++) {
		for (b = 0; b < 3; b++) {
			if (((fCoord[count].x - fCoord[count - 5].x)*
						(intersection[a].sides[b].point1.y- intersection[a].sides[b].point2.y)
					      - (fCoord[count].y - fCoord[count - 5].y)*
						   (intersection[a].sides[b].point1.x- intersection[a].sides[b].point2.x))
					!= 0)
			{
				opening=a;
				side=b;
				return 1;
			}
		}*/
//	}

	return 0;

}
