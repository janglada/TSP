#ifndef ANT_H_
#define ANT_H_
#include <vector>  // vector class library
#include <list>	   // list class library
using namespace std;


class Ant
{
public:
	Ant(int n);
	~Ant();
	
private:
    int N_Cities;
	int* tabuC; //ciutats visitades
	vector<int> availableC;
	double tourLength; 	
	//static cTour tour;
};

#endif /*ANT_H_*/
