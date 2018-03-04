#include "nn.h"
#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;

nn::nn()
{
	srand ( time(NULL) );
}

nn::~nn()
{
}

void nn::init(double temp,int n)
{
N_n=n;
N2_n=n*n;
tour.init(N_n);
tour.readCities();
tour.ComputeCityDistances();

T=temp;
/*
A=100;
D=1000;
B=1000;
C=2000;
*/
A=1;
B=1;
C=1;
D=1;
sol=new int[N_n];
neurons=new double*[N_n];
for(int i=0;i<N_n;i++) {neurons[i]=new double[N_n];	sol[i]=i;}
//inicialitzem a l'atzar les neurones
cout<<"ok1"<<endl;
for(int i=0;i<N_n;i++){
	for(int j=0;j<N_n;j++){
	if(i==j) neurons[i][j]=1;
	else neurons[i][j]=0;//randInt(2);//tanh((randR()-0.5)*2/T);
	}		
}	

matrix2vector_sol();
cout<<"ok2"<<endl;
length=tour.getTourDist(sol);
cout<<"ok3"<<endl;
}

void nn::step()
{
	
	for(int steps=0;steps<2;steps++)
	{
int x=randInt(N_n);
int i=randInt(N_n);

double e1=0;
double e2=0;
double e3=0;
double e4=0;	

double output=0;
	
	
//CALCUL e1 I e3**********************
int ant_i=i-1;
if(i==0) ant_i=N_n-1;

int post_i=i+1;
if(i==N_n) post_i=0;

for(int y=0;y<N_n;y++)
{
if(y!=x)
{
e1=e1+tour.getCityDist(x,y)*(neurons[y][post_i]+neurons[y][ant_i]);	
e3=e3+neurons[y][i];
}	
else {
	/*do nothing*/} 	
}		


//CALCUL e2**********************************

for(int j=0;j<N_n;j++)
{
if(j!=i)
{
	e2=e2+neurons[x][j];
}
else{ /*nothing*/}	
}
/*
//CALCUL e3	
for(int y=0;y<N_n;y++)
{
if(y!=x)
{
e3=e3+neurons[y][i];	
}	
else {
//do nothing
 } 	
}		
	*/

//CALCUL e4
for(int k=0;k<N_n;k++)
{
	for(int k1=0;k1<N_n;k1++)
	{
	e4=e4+neurons[k][k1];	
	}
	
}

output=0.5*(1+tanh( (-1./T)*(D*e1 + A*e2 + B*e3 + C*(e4-N_n)) ) );
neurons[x][i]=output;
}
matrix2vector_sol();

}

void nn::matrix2vector_sol()
{
	
	for(int i=0;i<N_n;i++)
	{
		//int indexMax=0;
		double Max=neurons[0][i];
		sol[i]=0;
		for(int j=0;j<N_n;j++){
			if(neurons[j][i]>Max) {
			    Max=neurons[j][i];	
				sol[i]=j;
			}
		}
	}
	length=tour.getTourDist(sol);			
	
}

void nn::printMaxtrix()
{
for(int i=0;i<N_n;i++)
{
for(int j=0;j<N_n;j++)
{
cout<<neurons[i][j]<<"   ";	
}	
cout<<endl;	
}
cout<<endl;
cout<<endl;
}

void nn::printVectorSol()
{
	for(int j=0;j<N_n;j++)
{
cout<<sol[j]<<"   ";	
}	
cout<<endl;
cout<<endl;
}

void nn::increaseParameters()
{/*
A=A+0.1;
B=B+0.1;
C=C+0.1;
D=D+0.1;
	*/
T=T*0.9999;
A=A+randR()*0.07;
B=B+randR()*0.07;
C=C+randR()*0.07;
D=D+randR()*0.07;	
	
}
