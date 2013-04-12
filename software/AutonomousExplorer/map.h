/*
 * map.h
 *
 *  Created on: Mar 23, 2013
 *      Author: Michael Jun
 */

#ifndef MAP_H_
#define MAP_H_


#define PI 3.14159265

//STRUCTURE DEFINITIONS
typedef struct{
	double x;
	double y;

}pt;

// to be later implmetnted for backstracking
typedef struct{
	pt point1;
	pt point2;
	int value;
}sd;
typedef struct{
	sd sides[4];
	int total;
//to be changed to linked list system later
}opening;



#define MIN_DISTANCE 12
//hard wire pointer adress for storage of adress of where the data points will be stroed,
#define DATA_START (volatile unsigned int *)(0x02231548	)
#define COUNT_BASE (volatile unsigned int *)( 0x02241548	)
#define POSITION_BASE (volatile unsigned int *)( 0x02331548)
#define LEFT_COORD_BASE (volatile unsigned int *)( 0x02431548)
#define RIGHT_COORD_BASE (volatile unsigned int *)( 0x02531548)


int processData(double front1, double front2, double left, double right,double angle);
int processDataNC(double front1, double front2, double left, double right);
pt convert(double scalar, double angle,pt position);
int checkExistingIntersection(int *opening, int *side);


#endif /* MAP_H_ */
