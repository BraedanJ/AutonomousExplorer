//============================================================================
// Name        : map.cpp

// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>


#include <stdio.h>

#include <cmath>
#define FORWARD 0
#define LEFT 1
#define RIGHT 2
#define PI 3.14159265
#define TOO_CLOSE 25
using namespace std;

FILE * input;

int GenerateTestData(double *front,double *left, double *right, int *angles, int *test);
void GenerateForward(double *front,double *left, double *right, int *angles, int *test,int length);
void GenerateLeft(double *front,double *left, double *right, int *angles, int *test,int sLength, int bLength);
void GenerateRight(double *front,double *left, double *right, int *angles, int *test,int sLength, int bLength);

double f[1000];
double l[1000];
double r[1000];
int    angles[1000];
int test[1000];

void pData();
int angle;
int bug;
int counter;
int bug1;

#define PI 3.14159

int main()
{
cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
bug=0;
counter=0;
angle=0;
input=fopen("input.txt","w");

bug1=GenerateTestData(f,l,r,angles,test);
int a;
for(a=0;a<bug1;a++)
{
	fprintf(input,"%d %lf %lf %lf %d \n",angles[a],f[a],l[a],r[a], a);
}
fclose(input);
cout << "!!!Hello World!!!" << bug1<< endl; // prints !!!Hello World!!!
pData();
	return 0;
}




void pData()
{
	double x=0;
	double y=0;
	int command=0;
	double leftCoord[1000][2];
	double rightCoord[1000][2];
	double frontCoord[1000][2];
	FILE *fp;
	fp=fopen("output.txt","w");

int dangle=0;
for (int a=1;a<bug1;a++)
{
if (command==0)
{
	if(f[a]>25)
	{
	}
	else
	{

		 dangle=angles[a];
		 printf("Angle: %d  ",dangle);
		if(l[a]>=26&&l[a]>=r[a])
		{
			printf("left turn at data point %d\n",a);
			command=1;
		}
		else if (r[a]>=26&&r[a]>=l[a] )
		{
			printf("right turn at data point %d\n",a);
			command=2;

		}
	}

}
else if(command==1)
{
if(abs(dangle-angles[a])>=90)
{
command=0;
printf("Left: done angle change %d %d \n",a,angles[a]);
}
}
else if(command==2)
{
if(abs(dangle-angles[a])>=90)
{
command=0;
printf("Right:done angle change %d %d  \n",a,angles[a]);
}
}


	      	leftCoord[a][0]=cos((angles[a]+180)*PI/180)*l[a]+x;
			leftCoord[a][1]=sin((angles[a]+180)*PI/180)*l[a]+y;
			rightCoord[a][0]=cos((angles[a])*PI/180)*r[a]+x;
			rightCoord[a][1]=sin((angles[a])*PI/180)*r[a]+y;
			if(command==0)
				{
				x=cos((angles[a]+90)*PI/180)*(f[a-1]-f[a])+x;
				y=sin((angles[a]+90)*PI/180)*(f[a-1]-f[a])+y;

				}
			fprintf(fp,"%lf\t%lf\t\t %lf\t%lf \t\t %lf\t%lf \t\t%d\n",x,y,leftCoord[a][0],leftCoord[a][1],rightCoord[a][0],rightCoord[a][1],a);

}
fclose(fp);
}

int nR=0;
int nL=0;
int nB=0;

#define OPEN 50
#define CLOSE 0
int GenerateTestData(double *front, double *left, double *right, int *angles,int *test) {


int length=150;
	GenerateForward(front,left,right,angles,test,100);

	nR=CLOSE;
	nL=OPEN;
	nB=OPEN;
	GenerateLeft(front,left,right,angles,test,length,length);
	GenerateForward(front,left,right,angles,test,length-75);
	nR=OPEN;
	nL=CLOSE;
	nB=OPEN;
	GenerateLeft(front,left,right,angles,test,length,length);
	printf("%d %d 3rd\n", bug, angle);
	GenerateForward(front,left,right,angles,test,length-75);
	nB=CLOSE;
	GenerateRight(front,left,right,angles,test,length,length);
	GenerateForward(front,left,right,angles,test,length-75);
	nB=OPEN;
	GenerateRight(front,left,right,angles,test,length,length);
	printf("%d %d 3rd\n", bug, angle);
	return bug;
}
void GenerateForward(double *front,double *left, double *right, int *angles, int *test,int length)
{

	int a = 0;
	bug=counter;
	for (a = 0; a <= length; a++) {
		angles[ bug+a] = angle;
		front[ bug+a] = length+50 - a;
		right[bug + a] = 25;
		left[bug + a] = 25;
		test[bug + a] = FORWARD;
	}
	counter+=length;
	bug=counter;
}

void GenerateLeft(double *front,double *left, double *right, int *angles, int *test,int sLength, int bLength)
{
	int j = 0;

	/*
	if(opening==1)
	{
	fangle=acos((25.00/(slength+25)))*180/PI;
	sangle=acos((25.00/slength))*180/PI;
	bangle==acos((25.00/blength))*180/PI;
	}
	else if(opening==2)
	{
		fangle=acos((25.00/(slength)))*180/PI;
		sangle=acos(25.00/(slength+25))*180/PI;
		bangle==acos((25.00/blength))*180/PI;
	}
	*/
	double fangle=acos((25.00/(sLength-nR)))*180/PI;
	double sangle=acos(25.00/(sLength-nL))*180/PI;
	double bangle=acos(25.00/(bLength-nB))*180/PI;

	printf("%d %d ff\n", bug, angle);
	bug=counter;
	for (j = 0; j <= 25; j++) {

		angles[bug + j] = angle;
		front[bug + j] = 50 - j;
		right[bug + j] = 25;
		left[bug + j] = sLength;
		test[bug + j] = FORWARD;
	}

	printf("%d %d asd\n", bug, angle);
	counter+=25;
	bug=counter;

	for (j = 0; j <= 90; j++) {
		angles[bug + j] = angle + j;
//front sensor
		if (j <= fangle) {
			front[bug + j] = 25 / cos(j * PI / 180);
		} else {
			front[bug + j] = sLength / cos((90 - j) * PI / 180);
		}
//right sensor
		if (j < 45) {
			right[bug + j] = 25 / cos(j * PI/ 180);
		} else {
			right[bug + j] = 25 / cos((90 - j) * PI / 180);
		}
//Left sensor
		if (j < (90-sangle)) {
			left[bug + j] = sLength / cos(j * 3.14 / 180);
		} else if (j < 45) {
			left[bug + j] = 25 / cos((90 - j) * 3.14 / 180);
		} else if (j <bangle) {
			left[bug + j] = 25 / sin((90 - j) * 3.14 / 180);
		} else {
			left[bug + j] = bLength / cos((90 - j) * 3.14 / 180);
		}
		test[bug + j] = LEFT;
	}
	counter+=91;
	bug=counter;
	angle+=90;
	printf("%d %d ff?\n", bug, angle);
	for (j = 0; j <= 25; j++) {
		angles[bug + j] = angle;
		front[bug + j] = sLength - j;
		right[bug +j] = 25;
		left[bug + j] = bLength;
		test[bug + j] = FORWARD;
	}
	counter+=25;
	bug=counter;

	printf("%d %d ?\n", bug, angle);
}
void GenerateRight(double *front,double *left, double *right, int *angles, int *test,int sLength, int bLength)
{

	int j = 0;

	/*
	if(opening==1)
	{
	fangle=acos((25.00/(slength+25)))*180/PI;
	sangle=acos((25.00/slength))*180/PI;
	bangle==acos((25.00/blength))*180/PI;
	}
	else if(opening==2)
	{
		fangle=acos((25.00/(slength)))*180/PI;
		sangle=acos(25.00/(slength+25))*180/PI;
		bangle==acos((25.00/blength))*180/PI;
	}
	*/
	double fangle=acos((25.00/(sLength-nL)))*180/PI;
	double sangle=acos(25.00/(sLength-nR))*180/PI;
	double bangle=acos(25.00/(bLength-nB))*180/PI;
	printf("%lf\n ",sangle);

	bug=counter;
	for (j = 0; j <= 25; j++) {

		angles[bug + j] = angle;
		front[bug + j] = 50 - j;
		left[bug + j] = 25;
		right[bug + j] = sLength;
		test[bug + j] = FORWARD;
	}

	printf("%d %d asd\n", bug, angle);
	counter+=25;
	bug=counter;

	for (j = 0; j <= 90; j++) {
		angles[bug + j] = angle - j;
//front sensor
		if (j <= fangle) {
			front[bug + j] = 25 / cos(j * PI / 180);
		} else {
			front[bug + j] = sLength / cos((90 - j) * PI / 180);
		}
//left sensor
		if (j < 45) {
			left[bug + j] = 25 / cos(j * PI/ 180);
		} else {
			left[bug + j] = 25 / cos((90 - j) * PI / 180);
		}
//right sensor

		if (j < (90-sangle)) {
			right[bug + j] =  sLength / cos(j * 3.14 / 180);
		} else if (j < 45) {
			right[bug + j] = 25 / cos((90 - j) * 3.14 / 180);
		} else if (j <bangle) {
			right[bug + j] = 25 / sin((90 - j) * 3.14 / 180);
		} else {
			right[bug + j] = bLength / cos((90 - j) * 3.14 / 180);
		}
		test[bug + j] = RIGHT;
	}
	counter+=91;
	bug=counter;
	angle+=-90;
	printf("%d %d ff?\n", bug, angle);
	for (j = 0; j <= 25; j++) {
		angles[bug + j] = angle;
		front[bug + j] = sLength - j;
		left[bug +j] = 25;
		right[bug + j] = bLength;
		test[bug + j] = FORWARD;
	}
	counter+=25;
	bug=counter;

	printf("%d %d ?\n", bug, angle);
}



