#ifndef MAP_H_
#define MAP_H_

#include "tour.h"

class Map : public cTour
{
public:
	Map();
	virtual ~Map();
private:
	double** trail;
	
};

#endif /*MAP_H_*/
