#ifndef TOUR_H_
#define TOUR_H_
using namespace std;


class cTour
{
public:
	cTour();
	void init(int N);
	 ~cTour();
	void readCities();
	void ComputeCityDistances();
	double getCityDist(int a, int b) {return cityDists[a][b];}
	double getTourDist(int* sol1); //la longitud de la solucio ha de ser Ncities!!! 
	
	double getXcity(int i) {return cityCoord[i][0];}
	double getYcity(int i) {return cityCoord[i][1];}
	
	//void printMatrix();
	
	
protected:

	int N_Cities;
	double** cityDists;
	double** cityCoord;	
	
	
	
	
};

#endif /*TOUR_H_*/
