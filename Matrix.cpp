#include "Matrix.h"
#include <cmath>

using namespace std; 
Matrix_4x4::Matrix_4x4(){
	for (int i=0; i<Nd; i++)
	{
		for (int j=0; j<Nd; j++)
		{
			if (i == j)
				matrix_4x4[i][j] = 1;
			else
				matrix_4x4[i][j] = 0;
		}
	}
}

Matrix_4x4::Matrix_4x4(const double (*buf)[Nd]){
	for (int i=0; i<Nd; i++)
	{
		for (int j=0; j<Nd; j++)
		{
			matrix_4x4[i][j] = buf[i][j];
		}
	}
}

Matrix_4x4::Matrix_4x4(const Matrix_4x4 &copy){
	for (int i=0; i<Nd; i++)
	{
		for (int j=0; j<Nd; j++)
		{
			matrix_4x4[i][j] = copy.matrix_4x4[i][j];
		}
	}
}

void const Matrix_4x4::display(){
	for (int i=0; i<Nd; i++)
	{
		for (int j=0; j<Nd; j++)
		{
			cout<<matrix_4x4[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

Matrix_4x4 operator+(const Matrix_4x4 &M1, const Matrix_4x4 &M2){
	double buf[Nd][Nd] = {0};
	Matrix_4x4 output(buf);
	for (int i=0; i<Nd; i++){
		for (int j=0; j<Nd; j++)
		{
			output.matrix_4x4[i][j] = M1.matrix_4x4[i][j] + M2.matrix_4x4[i][j];
		}
	}
	return output;
}

Matrix_4x4 operator*(const Matrix_4x4 &M1, const Matrix_4x4 &M2){
	double buf[Nd][Nd] = {0};
	Matrix_4x4 output(buf);
	for (int i=0; i<Nd; i++){
		for (int j=0; j<Nd; j++)
		{
			for (int m=0; m<Nd; m++){
				output.matrix_4x4[i][j] += M1.matrix_4x4[i][m] * M2.matrix_4x4[m][j];
			}
		}
	}
	return output;
}

Matrix_4x4 operator-(const Matrix_4x4 &M1, const Matrix_4x4 &M2){
	double buf[Nd][Nd] = {0};
	Matrix_4x4 output;
	for (int i=0; i<Nd; i++){
		for (int j=0; j<Nd; j++)
		{
			output.matrix_4x4[i][j] = M1.matrix_4x4[i][j] - M2.matrix_4x4[i][j];
		}
	}
	return output;
}

const Matrix_4x4& Matrix_4x4::operator=(const Matrix_4x4 &other){
	if (matrix_4x4 == other.matrix_4x4)
		{return *this;}
	else
	{
		for (int i=0; i<Nd; i++){
			for (int j=0; j<Nd; j++)
			{
				matrix_4x4[i][j] = other.matrix_4x4[i][j];
			}
		}
		return *this;	
	}
}

const Matrix_4x4& Matrix_4x4::operator=(const double (*buf)[Nd]){
	for (int i=0; i<Nd; i++)
	{
		for (int j=0; j<Nd; j++)
		{
			matrix_4x4[i][j] = buf[i][j];
		}
	}
	return *this;
}

const Matrix_4x4 Matrix_4x4::operator^(const int n){
	int abs_n = abs(n);
	Matrix_4x4 output(*this);
	Matrix_4x4 mutiplier(output);
	for (int i=0; i<abs_n-1; i++)
	{
	output = output*mutiplier;
	}
	
	if (n>0) { return output; }
	else if (n<0) 
	{ 
		output.inversion();
		return output;
	}
	else { return *this; } 
} 

double Matrix_4x4::operator()(int i, int j){
	if (!((i<=4) && (j<=4))) { 
		cout<<"Out of range..."<<endl;
		return 0;
	}
	return matrix_4x4[i][j];
}

istream& operator>>(istream& in_put, Matrix_4x4 &M){
	for (int i=0; i<Nd; i++)
	{
		for (int j=0; j<Nd; j++)
		{
			in_put>>M.matrix_4x4[i][j];
		}
	}
	return in_put;
}

ostream& operator<<(ostream& out_put, const Matrix_4x4 &M){
	for (int i=0; i<Nd; i++)
	{
		for (int j=0; j<Nd; j++)
		{
			cout<<M.matrix_4x4[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

void Matrix_4x4::swap_rol(double rol_a[],double rol_b[])  
{      
    double temp;  
    for(int i=0 ; i<Nd ; i++)  
    {  
        temp = rol_a[i];  
        rol_a[i] = rol_b[i];  
        rol_b[i] = temp;    
    }    
}  
  
double const Matrix_4x4::det() 
{       
	int counter = 0;                   //记录行交换的次数
    double det=1;  
    double _det_matrix_4x4[Nd][Nd];
    
    //拷贝matrix_4x4的值，防止其被直接改变 
    for (int i=0; i<Nd; i++)
    {
    	for (int j=0; j<Nd; j++)
    	{ _det_matrix_4x4[i][j] = matrix_4x4[i][j]; }
	}
 
    for(int ii=0 ; ii<Nd; ii++)  
    {     
        if((_det_matrix_4x4[ii][ii] < 10e-5) && (_det_matrix_4x4[ii][ii] > -10e-5))
		{
			for(int j=ii; j<Nd; j++)  
        	{    
            	if(!((_det_matrix_4x4[ii][ii] < 10e-5) && (_det_matrix_4x4[ii][ii] > -10e-5)) )
				{
					swap_rol(_det_matrix_4x4[ii], _det_matrix_4x4[j]);      //交换两行以保证对角线上元素非0 
					counter ++;
				}
        	}
        	if (counter == 0)        //若对角线下方元素均为 0，则行列式值为 0 
        		return 0;
		}	
		
		//通过行变换将对角线下方元素消为0 
		//运用第三类行变换，将第ii行乘res加到第k行，将(k, ii)处元素消为0 
        for(int k=ii+1; k<Nd; k++)  
		{    
          double res = -1 * _det_matrix_4x4[k][ii] / _det_matrix_4x4[ii][ii];  

          for(int u=0; u<Nd; u++)  
          {   
              _det_matrix_4x4[k][u] = _det_matrix_4x4[k][u] + _det_matrix_4x4[ii][u] * res; 
          }  
		}  
	}
	 
	for(int ii=0; ii<Nd; ii++)                  //求对角线上元素的积
    	{ det = det * _det_matrix_4x4[ii][ii]; }
 
	//行变换偶数次符号不变
	if(counter%2 == 1)  { det= -det; }
	return det;  
}

void Matrix_4x4::inversion(){  
    double matrix_E [Nd][Nd]; 
	
	//构造单位矩阵 
	for (int eraw=0; eraw<Nd; eraw++)
	{
		for (int ecol=0; ecol<Nd; ecol++)
		{
			if (eraw == ecol)	{ matrix_E[eraw][ecol] =1; }
			else
				matrix_E[eraw][ecol] = 0;
		}
	} 
	
	for(int ii=0 ; ii<Nd; ii++)  
    {     
        if((matrix_4x4[ii][ii] < 10e-5) && (matrix_4x4[ii][ii] > -10e-5))
		{
			int counter = 0; 
			
			for(int j=ii; j<Nd; j++)  
        	{    
            	if(!((matrix_4x4[ii][ii] < 10e-5) && (matrix_4x4[ii][ii] > -10e-5)) )
				{
					swap_rol(matrix_4x4[ii], matrix_4x4[j]);      //交换两行以保证对角线上元素非0 
					swap_rol(matrix_E[ii], matrix_E[j]);
					counter ++;
				}
        	}
        	if (counter == 0)        //该列元素均为0，不可求逆 
        	{
			 	cout<<"Invalid for inversion..."<<endl;
        		return;
        	} 
		}	
		
		//将ii转化为1
		double devider = matrix_4x4[ii][ii];
		for (int col=0; col<Nd; col++)
		{
			matrix_4x4[ii][col] = matrix_4x4[ii][col]/devider;
			matrix_E[ii][col] = matrix_E[ii][col]/devider;
		}
		
        for(int k=0; k<Nd; k++)  
		{
			if (k == ii) { k++; }	  
			double adder = - matrix_4x4[k][ii];
        	for(int u=0; u<Nd; u++)  
        	{   
           		matrix_4x4[k][u] = matrix_4x4[k][u] + adder*matrix_4x4[ii][u]; 
           		matrix_E[k][u] = matrix_E[k][u] + adder*matrix_E[ii][u];
        	}  
		}
	}
	
	//swap the two matrix
	//此时输出的matrix_4x4为原矩阵的逆
	for (int i=0; i<Nd; i++)
	{
		double swap;
		for (int j=0; j<Nd; j++)
		{
			swap = matrix_4x4[i][j];
			matrix_4x4[i][j] = matrix_E[i][j];
			matrix_E[i][j] = swap;
		}
	}
}

void Matrix_4x4::turn(){
	double swap;
	for (int i=0; i<Nd; i++)
	{
		for (int j=i+1; j<Nd; j++)
		{
			//交换非对角线上元素 
			swap = matrix_4x4[i][j];
			matrix_4x4[i][j] = matrix_4x4[j][i];
			matrix_4x4[j][i] = swap;
		}
	} 
}
