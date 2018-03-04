/***************************************************************************
 *   Copyright (C) 2006 by Joan Anglada                                  *
 *   janglada(@)gmail.com                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef GA_H
#define GA_H


//number of cities-chromosomelength
#define CHLEGTH 225
//number of individuals
#define NIND 2*CHLEGTH
#include <stdlib.h>

/**
@author joan,,,
*/


using namespace std;

/**
 *GA CLASS
 *Implementa l'algoritme gen�tic
 */

class GA
{
public:

        /**
        *Constructor
        *Crea una poblacio a l'altzar. 
        *Crida setCities().
        */
        GA();
        /**
        *Destructor
        *No fa res.
        */
        ~GA();
        /**
         * 
         * 
         * */
         void computecityDists();
        /**
        *Metode no pren cap par�metre.
        *Fa un pas en l'evoluci�
        *
        */
        void evolve();
        /**
        *Metode que llegeix des de l'arxiu "cities.dat"
        *les coordenades de les ciutats
        *@see 
        */
        void setCities();
        /**
        *Metode que pren un argument i retorna un float.
        *@param indx argument enter corresponent a la ciutat desitjada
        *@return La coordenada X de la ciutat indx-essima
        */
        float getXcity(int indx)
        {
                return tour[indx][0];
        }
        /**
         *Metode que pren un argument i retorna un float.
         *@param indx argument enter corresponent a la ciutat desitjada
         *@return La coordenada Y de la ciutat indx-essima
         */
        float getYcity(int indx)
        {
                return tour[indx][1];
        }
        /**
         *Metode que pren un argument i retorna un int.
         *@param indx argument enter. Correspon a la ciutat desitjada
         *@return Ciutat en la posici� indx-essima del cromosoma que fa el tour m�s curt
         */
        int getCity(int indx)
        {
                return population[minIndex][indx];
        }
        /**
         *Metode que pren un argument i retorna un float.
         *@return Longitud del tour m�s curt
         */
        float getLength()
        {
                return lengths[minIndex];
        }
        /**
           *Metode que retorna un int.
           *@return El nombre de ciutats
         */
        int getNcities()
        {
                return CHLEGTH;
        }

		void printBestSolution();	

protected:


        /**
         *Metode que pren un argument. Intercanvia les posicions de dues 
         *ciutats a l'atzar en el cromosoma indicat.
         *@param indx Argument enter. Correspon al l'index del cromosoma desitjat.
         *
         */
        void citySwap(int indx);
        /**
         *Metode que pren 3 arguments enters. Intercanvia les posicions de dues ciutats 
         *a l'atzar en el cromosoma indicat.
         *@param indx Argument enter. Correspon al l'index del cromosoma desitjat.
         *@param a Enter corresponent a l'index de la ciutat a intercanviar.
         *@param b Enter corresponent a l'index de l'altra ciutat a intercanviar.
         */
        void citySwap(int a,int b,int indx);
        /**
        *Metode que pren 2 arguments. Intercanvia les posicions de dues ciutats 
        *a l'atzar en el cromosoma indicat.
        *@param indx Argument enter. Correspon al l'index del cromosoma desitjat.
        *@param a Enter corresponent a l'index de la ciutat a intercanviar.
        *@param b Enter corresponent a l'index de l'altra ciutat a intercanviar.
        */
        void revOrder(int indx,bool isit);
        /**
         * Metode que inverteix l'ordre d'un tram de cromosoma
         * @param indx Index del cromosoma a invertir.
         * @param isit Si �s true el tram que invertiex el cromsoma �s igual o menor que 3
         *Si isit es false, llavors el tram a invertir potser tan llarg com el nombre de ciutats
        */
        void displace(int indx);
        /**
         * Metode que desordena tots els cromsomes de tots els individus.
         */
        void shuffle();
        /**
         * Metode que copia el millor cromosoma a la posici� indx
         * @param indx Index de l'individu.
         */
        void copyChromosm(int indx);
        /**
         * Metode que calcula la distancia entre dues ciutats
         * @param a Index d'una de les ciutats
         * @param b Index de l'altra ciutat.
         * @return Dist�ncia entre les ciutats a i b  \f$\sqrt{(x_a-x_b)^2+(y_a-y_b)^2}\f$
         */
        float distCities(int a, int b );

        /**
         * Metode que retorna un float
         * @return Nombre a l'atzar entre 0 i 1 uniformement distribuit
         */
        float randR()
        {
                return ( ((double)rand())/((double) RAND_MAX+(double)1) );
        }
        /**
         * Metode que pren un enter i retorna una enter
         * @param m Valor maixim de l'enter a retornar
         * @return Nombre enter a l'atzar entre 1 i m uniformement distribuit.
         */
        int randInt(int m)
        {
                return (int)(( ((double)rand())/((double) RAND_MAX+(double)1) )*m);
        }
        /**
         * Metode que pren un enter.
         * @param indx Index de l'individu el cromosoma del qual sera canviat per un cromosoma a l'atzar.
         */
        void rnewgene(int indx);
        /**
        *Matriu que guarda les coordenades de les ciutats
        *
        */
        float tour[CHLEGTH][2];
        /**
        *Vector que guarda les longituds del tour de cada cdromosoma
        *
        */
                
        float lengths[NIND];
        float probs[NIND];
        /**
        *Matriu que guarda els cromsomes
        *Cada fila �s un cromosoma (individu)  diferent
        */
        int population[NIND][CHLEGTH];
        /**
        *Enter que guarda la posici� (index) del millor cromosoma
        *
        */
        int minIndex;
        
        /**
        *Enter que guarda la posici� (index) del pitjor cromosoma. Serveix per a normalitzar les probabilitats
        *@see evolve()
         */
        int maxIndex;

       float cityDitsts[CHLEGTH][CHLEGTH];



};

#endif
