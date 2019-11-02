#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

class optimizer
{
public:
	
	optimizer(){};
	
	virtual double setOptimizer(double (*foo)(double* , double* ), 
			double* _x_buf, double* _y_buf, int _x_dim, int _y_dim ) = 0;	
	
	~optimizer(){};
	
protected:
	double *x;
	double *y;
	int xd;
	int yd;
	double (*fun)(double* _x_buf, double* _y_buf);
};

#endif //_OPTIMIZER_H_
