#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "opt1.h"

using namespace std;

double opt1::setOptimizer(double (*foo)(double* , double* ), 
			double* _x_buf, double* _y_buf, int _x_dim, int _y_dim )
{
	fun = foo;
	x = _x_buf;
	y = _y_buf;
	xd = _x_dim;
	yd = _y_dim;
	
	intitalize();
	
	for(int _iterations=0; _iterations<D; _iterations++)
	{
		update(_iterations);
	}
	
	Display_g_best();

	cout<<endl<<"======Fitness======"<<endl<<Fun_fitness(_g_best, y)<<endl;
}

void opt1::intitalize()
{
	//输入x的取值范围
	double *_x_constrain_max = new double [xd];
	double *_x_constrain_min = new double [xd];
	
	cout<<"Intitalizing constrains: "<<endl;
	for (int i=0; i<xd; i++)
	{
		cout<<endl<<"x dimension: "<<i+1<<endl<<"_POS_MAX: ";
		cin>>_x_constrain_max[i];
		cout<<"_POS_MIN: ";
		cin>>_x_constrain_min[i];
	}
	 
	srand((int)time(0));
	
	//intitalize elements 
	for(int i=0; i<N; i++)
	{	
		element[i].pos = new double [xd];
		element[i].spd = new double [xd];
		element[i].pBest = new double [xd];
		element[i]._POS_MAX = new double [xd];
		element[i]._POS_MIN = new double [xd];
		
		/* start intitalizing constrains */
		for(int j=0; j<xd; j++)
		{
			element[i]._POS_MAX[j] = _x_constrain_max[j];
			element[i]._POS_MIN[j] = _x_constrain_min[j];
		} 
		
		element[i]._SPD_MAX = V_MAX;		
		/* constrains intitalized */
		
		for(int j=0; j<xd; j++)
		{
			_pos_SetRandom(element[i].pos, xd, element[i]._POS_MAX, element[i]._POS_MIN);
		}
		
		_spd_SetRandom(element[i].spd, xd, V_MAX);
		
		for(int j=0; j<xd; j++)
		{
			element[i].pBest[j] = element[i].pos[j];
		}
		element[i]._p_bestValue = Fun_fitness(element[i].pBest, y);
	}

	_g_best = new double [xd];
	//cout<<"here"<<endl;
	Generate_g_best();
	//_g_bestValue = Fun_fitness(_g_best, y);
	/*
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<xd; j++)
		{
			cout<<element[i].pos[j]<<"  "<<element[i].spd[j]<<"  "<<element[i].pBest[j]<<endl;
		}
		cout<<"element "<<i<<endl;
	}
	
	for(int j=0; j<xd; j++)
	{
		cout<<_g_best[j]<<endl;
	}
	_g_bestValue = Fun_fitness(element[0].pos, y);
	cout<<_g_bestValue<<endl;*/
}

void opt1::update(int iterations)
{
	double w;
	w = _w_Generate(iterations);
	
	for (int i = 0; i < xd; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
			double v = w*element[j].spd[i] + c1*randval(0, 1)*(element[j].pBest[i] - element[j].pos[i]) + c2*randval(0, 1)*(_g_best[i] - element[j].pos[i]);
			
			//do the constrain
			if (v > V_MAX)  
			{element[j].spd[i] = V_MAX;}
			else if (v < V_MIN)  
			{element[j].spd[i] = V_MIN;}
			else 
			{element[j].spd[i] = v;}
	
			double x = element[j].pos[i] + element[j].spd[i];
			
			//do the constrain
			if (x > element[j]._POS_MAX[i])
			{element[j].pos[i] = element[j]._POS_MAX[i];}
			else if (x < element[j]._POS_MIN[i])
			{element[j].pos[i] = element[j]._POS_MIN[i];}
			else 
			{element[j].pos[i] = x;}
		}	
	}
	Generate_g_best();
	Generate_p_best();
}

void opt1::_spd_SetRandom(double* buf, int dim, double constrain)
{
	int _int_constrain = 1000*constrain;
	for(int i=0; i<dim; i++)
	{
		buf[i] = 0.001*(2.0*(rand()% _int_constrain)-_int_constrain);
	}
}

void opt1::_pos_SetRandom(double* buf, int dim, const double *c_max, const double *c_min)
{
	/*************************************
	将c_max和c_min的值加倍，同时转化为整型 
	这样之后才能设置随机数   
	**************************************/
	int *_int_c_max;
	int *_int_c_min;
	
	_int_c_max = new int [dim];
	_int_c_min = new int [dim];
	
	for(int i=0; i<dim; i++)
	{
		_int_c_max[i] = c_max[i]*1000;
		_int_c_min[i] = c_min[i]*1000;
	}
	
	for(int i=0; i<dim; i++)
	{
		buf[i] = 0.001*(rand()% (_int_c_max[i]-_int_c_min[i]+1)+_int_c_min[i]);
	}
}

double opt1::Fun_fitness(double* x, double* y)
{
	return (*fun)(x, y);
}

void opt1::Generate_g_best()
{
	_g_bestValue = Fun_fitness(element[0].pos, y);
	//cout<<_g_bestValue<<endl;
	int _posof_gbest = 0; 
	
	for(int i=1; i<N; i++)
	{
		double _fun_fitness = Fun_fitness(element[i].pos, y);
		
		if(_g_bestValue>_fun_fitness)
		{
			_g_bestValue = _fun_fitness;
			_posof_gbest = i;
		}

		//cout<<_posof_gbest<<endl;
	}
	//update _g_best
	for(int i=0; i<xd; i++)
	{
		_g_best[i] = element[_posof_gbest].pos[i];	
	}
}

void opt1::Generate_p_best()
{
	for(int i=0; i<N; i++)
	{
		double _fun_fitness = Fun_fitness(element[i].pos, y);
		if(element[i]._p_bestValue>_fun_fitness)
		{
			element[i]._p_bestValue = _fun_fitness;
			//update element[i].pBest
			for(int j=0; j<xd; j++)
			{
				element[i].pBest[j] = element[i].pos[j];
			}
		}
	}
}

double opt1::_w_Generate(int iterations)
{
	return ((W_int-W_end)*(D-iterations)/D + W_end);
}

double opt1::randval(double max, double min)
{
	int _int_max = max*1000;
	int _int_min = min*1000;
	
	return (0.001*(rand()% (_int_max-_int_min+1)+_int_min));
}

void opt1::Display_g_best()
{
	cout<<endl<<"======Optimal solution======"<<endl;
	for(int i=0; i<xd; i++)
	{
		cout<<_g_best[i]<<endl;
	}
}
