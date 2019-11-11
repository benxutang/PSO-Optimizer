#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

/**
 * 	优化器optimizer接口说明：
 * 	用于计算多元方程组的近似解
 *
 * 	Inputs:
 * 		函数名
 * 		ｘ数组及其维度
 * 		ｙ数组及其维度
 *              ｘ的取值范围
 *
 * 	Output
 * 		优化后结果：ｘ数组值
 *              输出结果与目标值的误差
 *
 * 	@opt1.cpp Line 39 to 52 :
 *      ｘ的取值范围在此处赋值
 *
 *      @opt1.h Line 6 to 14 :
 *      在此处调整参数的值，对不同的应用场景，可以获得更好的优化效果
 *      N: 粒子个数　增大可以增加精度，但是会延长运行时间
 *      D: 迭代次数　增大可以增加精度，但是会延长运行时间
 */

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
