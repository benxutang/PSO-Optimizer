#ifndef _MATRIX_4x4_
#define _MATRIX_4x4_

#include <iostream>
#define Nd 4
using namespace std;
class Matrix_4x4
{
private:
	double matrix_4x4[Nd][Nd];
	
	//private funtions
	void swap_rol(double rol_a[],double rol_b[]);
	
public:
	
	//constructor
	Matrix_4x4();
	
	Matrix_4x4(const double (*buf)[Nd]);
	
	Matrix_4x4(const Matrix_4x4 &copy);

	//destructor
	~Matrix_4x4(){};
	
public:
	
	//operator
	friend Matrix_4x4 operator+(const Matrix_4x4 &M1, const Matrix_4x4 &M2);
	
	friend Matrix_4x4 operator-(const Matrix_4x4 &M1, const Matrix_4x4 &M2);
	
	friend Matrix_4x4 operator*(const Matrix_4x4 &M1, const Matrix_4x4 &M2);
	
	friend ostream& operator<<(ostream& out_put, const Matrix_4x4 &M); 
	
	friend istream& operator>>(istream& out_put, Matrix_4x4 &M);
	
	const Matrix_4x4& operator=(const Matrix_4x4 &other);
	
	const Matrix_4x4& operator=(const double (*buf)[Nd]);
	
	const Matrix_4x4 operator^(const int n);
	
	double operator()(int i, int j);
	
	//public funtions
	//计算行列式
	double const det();
	
	//矩阵求逆 
	void inversion();
	
	//矩阵输出 
	void const display();
	
	//矩阵转置 
	void turn();
	
};

#endif //_MATRIX_4x4_
