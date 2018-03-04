#include "Map.h"

Map::Map()
{
	for(int i=0;i<N_Cities;i++) trail[i]=new double[N_Cities];
	
	for(int i=0;i<N_Cities;i++){
 	for(int j=0;j<N_Cities;j++)	trail[i][j]=0.0;
	
	}
}

Map::~Map()
{
}
