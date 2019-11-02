#ifndef _OPT_1_H_
#define _OPT_1_H_

#include "optimizer.h" 

#define N 20
#define D 1500
#define T 100
#define W_int 0.9
#define W_end 0.4
#define c1 0.5
#define c2 0.5
#define V_MAX 0.5
#define V_MIN -0.5

//单个粒子
struct Element{
	double *pos;
	double *spd;
	double *_POS_MAX;
	double *_POS_MIN;
	double _SPD_MAX = V_MAX;
	double *pBest;
	double _p_bestValue;
}; 

class opt1: public optimizer
{
public:

	double setOptimizer(double (*foo)(double*, double*), 
			double* _x_buf, double* _y_buf, int _x_dim, int _y_dim );	
			
private:
	
	//粒子群 
	Element element[N];
	//全局最优解向量 
	double *_g_best;
	//全局最优解向量对应函数值 
	double _g_bestValue;

	//初始化
	void intitalize();
	
	void update(int iterations);
	
	void _spd_SetRandom(double* buf, int dim, double constrain);
	
	void _pos_SetRandom(double* buf, int dim, const double *c_max, const double *c_min);

	double Fun_fitness(double* x, double* y);
	
	void Generate_g_best();
	
	void Vector_copyvalue(double* output, double* input, int dim);
	
	double _w_Generate(int iterations);
	
	void Generate_p_best();
	
	double randval(double max, double min);
};

#endif //_OPT_1_H_
