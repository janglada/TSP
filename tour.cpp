#include "tour.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;


cTour::cTour()
{


	
	
	
}

cTour::~cTour()
{
/*
for(int i=0;i<2;i++)
{
  delete[] cityCoord[i];
  delete[] cityDists[i];

}

delete[] cityCoord;	
delete[] cityDists;
*/
}

void cTour::init(int N)
{
N_Cities=N;	
//INCIALITZO TAULA DE DISTANCIES
cityDists=new double*[N_Cities];
for(int i=0;i<N_Cities;i++) cityDists[i]=new double[N_Cities];
	
for(int i=0;i<N_Cities;i++){
 for(int j=0;j<N_Cities;j++)	cityDists[i][j]=0.0;
	
}
//INICIALITZO TAULA COORDENADES DE LES CIUTATS
cityCoord=new double*[N_Cities];
for(int i=0;i<N_Cities;i++) cityCoord[i]=new double[2];
	
for(int i=0;i<N_Cities;i++){
 for(int j=0;j<2;j++)	cityCoord[i][j]=0.0;
	
}	
	
}
 
void cTour::readCities()
{
        int row=0;
        int col=0;

        ifstream inFile ("cities.dat");

        if (!inFile) {
                cout << "Unable to open file datafile.txt";
                exit(1);   // call system to stop
        }

        while ( !inFile.eof()) { // keep reading until end-of-file


                inFile >> cityCoord[row][col]; // sets EOF flag if no value found
                col++;
                if(col==2) {
                        col=0;
                        row++;
                }
        }
        cout<<row<<endl;
        inFile.close();	
	
	
}

void cTour::ComputeCityDistances()
{
for(int i=0;i<N_Cities;i++)
{
for(int j=i+1;j<N_Cities;j++)	
{
        double x1=cityCoord[i][0];
        double y1=cityCoord[i][1];

        double x2=cityCoord[j][0];
        double y2=cityCoord[j][1];

         cityDists[i][j]= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) );//sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
         cityDists[j][i]=cityDists[i][j];
}
}	
	
	
}

double cTour::getTourDist(int *sol1)
{
	
double longitud=0;
for(int i=0;i<N_Cities-1;i++){
longitud=longitud+cityDists[sol1[i]][sol1[i+1]];	
}	
longitud=longitud+cityDists[sol1[N_Cities-1]][0];	
return longitud;	
}


