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

#include "ga.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

//number of cities-chromosomelength
#define CHLENGTH 225
//number of individuals
#define NIND 2*CHLEGTH



using namespace std;

GA::GA()
{
        srand ( time(NULL) );

        for (int i=0;i<NIND;i++) {
                population[i][0]=0;
                population[i][CHLENGTH-1]=CHLENGTH-1;
                for(int j=1;j<(CHLENGTH-1);j++) {
                        population[i][j]=j;
                        probs[i]=0;
                }

        }
        shuffle();
        setCities();
        computecityDists();
}

GA::~GA()
{}



void GA::shuffle()
{

        for(int j=0;j<NIND;j++) {
                //--- Shuffle elements by randomly exchanging each with one other.
                for (int i=1; i<CHLENGTH; i++) {
                        int r = randInt(CHLENGTH-1);
                        //   cout<<r<<"   "<<endl;// generate a random position 0<position<CHLENGTH-1
                        int temp = population[j][i];
                        population[j][i] = population[j][r];
                        population[j][r] = temp;
                }

        }
}

void GA::setCities()
{
        int row=0;
        int col=0;

        ifstream inFile ("cities.dat");

        if (!inFile) {
                cout << "Unable to open file datafile.txt";
                exit(1);   // call system to stop
        }

        while ( !inFile.eof()) { // keep reading until end-of-file


                inFile >> tour[row][col]; // sets EOF flag if no value found
                col++;
                if(col==2) {
                        col=0;
                        row++;
                }
        }
        inFile.close();
}

void GA::evolve()
{

        float length;
        lengths[0]=0.0;
        float maxVal=0.0;


        for(int i=0;i<NIND;i++)               //per a cada cromosoma
        {
                length=0;
                for(int j=1;j<CHLENGTH;j++)
                {
                        length=length+distCities(population[i][j-1],population[i][j]);

                }
                length=length+distCities(population[i][CHLENGTH-1],population[i][0]);

                lengths[i]=length;                  //calcula longitud de la volta
        }
        
        maxVal=lengths[0];
        minIndex=0;
        
        for(int i=0;i<NIND;i++) {
                if (lengths[i]>maxVal) {
                        maxVal=lengths[i];
                        maxIndex=i;
                }//maxVal=travel mes llarg, serveix per "normalitzar" prbabilitat
                if (lengths[i]<lengths[minIndex]) {
                        minIndex=i;
                }     //posicio del travel mes curt
        }


        for(int i=0;i<NIND;i++) {  //per a cada cromosoma

                probs[i]=(float)(1-(lengths[i]/maxVal));  //puntua cada volta, com mes proper a 1 millor

                if(i!=minIndex) //si i!= viatge mes curt
                {
                        float coin1=randR();   //llençaa una moneda
	//FILOSOFIA: MALA PUNTUACIO= CANVIS GROSSOS
	//			 BONA PUNTUACIO= PETITS CANVIS			
                        if(probs[i]>0.75)//CANVIS PETITS//MOLTS "PARAMETRES TUNEJABLES" 0.75,0.33,0.666
                        {								//SERIA INTERESSANT FER UN ALGORITME GENETIC SOBRE
														//AQUESTS PARAMETRES......millor un altre dia...
                                if(coin1<0.3333) {
                                        displace(i);
                                } else {
                                        if(coin1<0.6666) {
                                                citySwap(i);
                                        }
                                        else {
                                                revOrder(i,true);
                                        }
                                }
                        }
                        else //CANVIS GROSSOS
                        {
                                copyChromosm(i);
                                if(probs[i]>randR()) {

                                        if(coin1<0.3333) {
                                                displace(i);
                                        } else {
                                                if(coin1<0.6666) {
                                                        citySwap(i);
                                                }
                                                else {
                                                        revOrder(i,true);
                                                }
                                        }
                                } else {//ENCARA MES GROSSOS
                                        // copyChromosm(i);
                                        coin1=randR();
                                        if(coin1<0.3333) {
                                                revOrder(i,false);
                                        } else {
                                                if(coin1<0.6666) {
                                                        citySwap(i);
                                                        citySwap(i);
                                                        citySwap(i);
                                                } else {
                                                        if(coin1<0.95) {
                                                                displace(i);
                                                                citySwap(i);
                                                                displace(i);
                                                        } else
                                                                rnewgene(i);
                                                }
                                        }
                                }

                        }
                }
               /* else{ //INTRODUIM UN "LLOP": es menja la millor solucio
                	if(randR()<0.001) rnewgene(minIndex);
                }*/

        }
}

float GA::distCities(int a,int b)
{

      /*  float x1=tour[a][0];
        float y1=tour[a][1];

        float x2=tour[b][0];
        float y2=tour[b][1];

        return ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
        */
        return cityDitsts[a][b];
}

void GA::citySwap(int indx)
{

        int a=randInt(CHLENGTH);
        int b=randInt(CHLENGTH);

        int temp = population[indx][a];
        population[indx][a] = population[indx][b];
        population[indx][b] = temp;
}

void GA::revOrder(int indx,bool isit)
{
        int width=0;
        if(isit==true)
                width=randInt(10);
        else
                width=randInt(CHLENGTH);
        int startPoint=randInt(CHLENGTH-1-width);
        int aux[CHLENGTH];

        for(int k=0;k<CHLENGTH;k++)
                aux[k]=population[indx][k];
        reverse(aux+startPoint,aux+startPoint+width);
        for(int k=0;k<CHLENGTH;k++)
                population[indx][k]=aux[k];
}

void GA::displace(int indx)
{

        int c1=randInt(CHLENGTH);
        int c2=randInt(CHLENGTH);
        if(c2<c1) {
                int aux=c1;
                c1=c2;
                c2=aux;
        }
        citySwap(c1,c2,indx);
        for(int k=c2;k>c1;k--)
                citySwap(k,k-1,indx);
}

void GA::citySwap(int a,int b,int indx)
{

        int temp = population[indx][a];
        population[indx][a] = population[indx][b];
        population[indx][b] = temp;
}

void GA::copyChromosm(int indx)
{

        for(int i=0;i<CHLENGTH;i++) {
                population[indx][i]=population[minIndex][i];
        }
}

void GA::rnewgene(int indx)
{

        for (int i=0; i<CHLENGTH; i++) {
                int r = randInt(CHLENGTH);
                int temp = population[indx][i];
                population[indx][i] = population[indx][r];
                population[indx][r] = temp;
        }

}

void GA::computecityDists()
{
	
for(int i=0;i<CHLENGTH;i++)
{
for(int j=i+1;j<CHLENGTH;j++)	
{
       float x1=tour[i][0];
        float y1=tour[i][1];

        float x2=tour[j][0];
        float y2=tour[j][1];

         cityDitsts[i][j]= sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) ) ;//sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
         cityDitsts[j][i]=cityDitsts[i][j];
}
}	
}

void GA::printBestSolution()
{
	
for(int i=0;i<	CHLEGTH;i++)
cout<<population[minIndex][i]<<"   ";
cout<<endl;
cout<<"Longitud : "<<lengths[minIndex]<<endl;
}
