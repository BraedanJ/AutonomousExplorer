#ifndef GENERATE_H_
#define Generate_H_


int GenerateTestData(double *front,double *left, double *right, int *angles, int *test,int counter);
void GenerateForward(double *front,double *left, double *right, int *angles, int *test,int length);
void GenerateLeft(double *front,double *left, double *right, int *angles, int *test,int sLength, int bLength);
void GenerateRight(double *front,double *left, double *right, int *angles, int *test,int sLength, int bLength)
#define FORWARD 0
#define LEFT 1
#define RIGHT 2
#define PI 3.14159265
#define TOO_CLOSE 26

#endif /*TESTDATA_H_*/
