#ifndef SA_H_
#define SA_H_
#include "tour.h"
#include <math.h>

#include <stdlib.h>

using namespace std;


class Sa
{
public:
	Sa();
	 ~Sa();
	 
	 void inicialitza(int nc,double t0);

	void shuffle();
	
	void trymove();
	
	
	//"a la 1 li copio la 2"
	void copySol(int* solucio1,int* solucio2) {for (int i=0;i<N_Cities;i++) solucio1[i]=solucio2[i];}
	
	int getNcities()
        {
                return N_Cities;
        }
	
	double getLength() {return sol_length;}
	void go();
	double getXCity(int i) {return tour.getXcity(sol[i]);}//sol_best[i]
	double getYCity(int i) {return tour.getYcity(sol[i]);}
	
	double getCity(int i) {return sol[i];}
	
	void setTemp(double temp) {T=temp;} 
	
	double getTemp() {return T;}
	
	void printSol();
	
	void changeT(int k) {T=Ti/log(1+1000*k);/*T=Ti/(1+0.1*k)*/;}
	
	void solApprox();
	
	void printBestSolution();
private:

	
	 
	int randInt(int m)
    {
     return (int)(( ((double)rand())/((double) RAND_MAX+(double)1) )*m);
    }
	
	
	double randR()
        {
                return ( ((double)rand())/((double) RAND_MAX+(double)1) );
        }
	
	void twoOpt(int* s, int a, int b);
	
	double twoOpt_cost(int i,int j);
	
	void citySwap(int indx1,int indx2, int* s);
	void reverse(int* array, int start, int end);
	
	double displace_cost(int i,int j);
	
	void displace(int i,int j);
	
	//void revOrder2(int indx);
	void revOrder(int* s,int start, int end);
	
	double citySwap_cost(int a, int b);
	
	void move(int t,int c1, int c2, int c3, int a,int b );
	
	double revOrder_cost(int i, int j);
	int N_Cities;
//	double** tour;
	int* sol; //solucio
	int* sol_best;
	double T;//temperatura
	double Ti;
	double sol_length;//longitud de la solucio
	double sol_best_length;
	cTour tour;
	
};



#endif /*SA_H_*/
