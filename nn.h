#ifndef NN_H_
#define NN_H_
#include "tour.h"
#include <stdlib.h>
using namespace std;
class nn
{
public:
	nn();
	~nn();
	void init(double temp, int n);
	
	void step();
	
	
	double getXCity(int i) {return tour.getXcity(sol[i]);}
	double getYCity(int i) {return tour.getYcity(sol[i]);}
	
	double getCity(int i) {return sol[i];}
	
	double getLength() {return length;}
	
	void increaseParameters();
	
	void printMaxtrix();
	
	void printVectorSol();
	
		int getNcities()
        {
                return N_n;
        }
private:
    //matriu quadrada,  
	double** neurons;
	//solucions en forma de vector
	int *sol;
	
	//nombre neurones
	int N_n;
	//neurones^2
	int N2_n;
	
	cTour tour;
	
	double A;
	
	double B;
	
	double C;
	
	double D;
	
	double T;
	
	int randInt(int m){return (int)(( ((double)rand())/((double) RAND_MAX+(double)1) )*m);}
		
	double randR()
        {
                return ( ((double)rand())/((double) RAND_MAX+(double)1) );
        }
	
	//converteix la solucio matriu en un vector per a poder dibuixar la solucio
    void matrix2vector_sol();
    
    //longitud solucio
    double length;
    

};

#endif /*NN_H_*/
