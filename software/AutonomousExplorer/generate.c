#include "generate.c"



void GenerateTestData(double *front,double *left, double *right, int *angles,int *test)
{

int counter=0;
int angle=0;
	printf("%d %d\n",counter,angle);

//go forward for 100
	int a=0;
	for(a=0;a<=100;a++)
	{
		 angles[a+counter]=angle;
		  front[a+counter]=150-a;
		  right[counter+a]=25;
		  left[counter+a]=25;
		  test[counter+a]=FORWARD;
	}
	int sideLength=125;
	int backLength=125;
			for(a=0;a<=25;a++)
				{
			    angles[counter+a]=angle;
			    front[counter+a]=50-a;
			    right[counter+a]=25;
			    left[counter+a]=sideLength;
			    test[counter+a]=FORWARD;
				}
			counter=counter+27;
			int j=0;
				for (j=0; j<=90;j++)
				{
					 angles[counter+j]=angle+j;
					 	//front sensor
						if(j<=78)
						{
							 front[counter+j]=25/cos(j*3.14/180);
						}
						else
						{
							 front[counter+j]=sideLength/cos((90-j)*3.14/180);
						}
						//right sensor
						if(j<45)
						{
						    right[counter+j]=25/cos(j*3.14/180);
						}
						else
						{
							right[counter+j]=25/cos((90-j)*3.14/180);
						}
						//Left sensor
						if(j<12)
						{
							 left[counter+j]=sideLength/cos(j*3.14/180);
						}
						else if(j<45)
						{
							 left[counter+j]=25/cos((90-j)*3.14/180);
						}
						else if(j<78)
						{
							 left[counter+j]=25/sin((90-j)*3.14/180);
						}
						else
						{
							 left[counter+j]=backLength/cos((90-j)*3.14/180);
						}
						test[counter+a]=LEFT;
				}
		angle=angle+90;
		counter=counter+91;
		for(a=0;a<=25;a++)
		{
		angles[counter+a]=angle;
		front[counter+a]=125-a;
	    right[counter+a]=25;
		left[counter+a]=125;
		test[counter+a]=FORWARD;
		}
	counter=counter+a;
	for(a=0;a<=50;a++)
	{
		 angles[a+counter]=angle;
		  front[a+counter]=100-a;
		  right[counter+a]=25;
		  left[counter+a]=25;
		  test[counter+a]=FORWARD;
	}
}
