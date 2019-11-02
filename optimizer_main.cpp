#include <iostream>
#include <math.h>
#include "optimizer.h"
#include "opt1.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
double test_f(double *x, double *y)
{

	int xd=6;
	int yd=8*3;

	double sensor_position[8][3] =
	{
	    { -0.10,     0,  0 },
	    { -0.05,  -0.05,  0 },
	    {     0,  -0.1,  0 },
	    {  0.05, -0.05,  0 },
	    {  0.10,     0,  0 },
	    {  0.05,  0.05,  0 },
	    {     0,  0.10,  0 },
	    { -0.05,  0.05,  0 },
	};

	double K=0.09788*3.14159*0.005*0.005*0.01*1090*10000;
	double res=0;
	double a,b,c,m,n,p,R,xs,ys,zs;

	a=x[0];b=x[1];c=x[2];
    m=x[3];n=x[4];p=x[5];

	for (int i=0;i<8;i++)
	{

		xs=sensor_position[i][0];
		ys=sensor_position[i][1];
		zs=sensor_position[i][2];

		double bx,by,bz;
		bx=y[i*3+0];
		by=y[i*3+1];
		bz=y[i*3+2];

        R=sqrt((xs-a)*(xs-a)+(ys-b)*(ys-b)+(zs-c)*(zs-c));

        bx-=K*((3*(m*(xs-a)+n*(ys-b)+p*(zs-c))*(xs-a))/(R*R*R*R*R)-m/(R*R*R));
        by-=K*((3*(m*(xs-a)+n*(ys-b)+p*(zs-c))*(ys-b))/(R*R*R*R*R)-n/(R*R*R));
        bz-=K*((3*(m*(xs-a)+n*(ys-b)+p*(zs-c))*(zs-c))/(R*R*R*R*R)-p/(R*R*R));

		res+=bx*bx+by*by+bz*bz;
	}

	return res;
}

int main(int argc, char** argv) {
    double x[6]={0.05,-0.05,0.12,0,0,1};
    double y[24]={0};
    optimizer* optimizer;
    opt1 opt1;
    optimizer = &opt1;
	
    optimizer->setOptimizer(test_f, x, y, 6, 24);
    
	return 0;
}
