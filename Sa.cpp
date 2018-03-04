#include "Sa.h"
#include <math.h>
#include <iostream>
#include <time.h>



using namespace std;


Sa::Sa()
{
	 srand ( time(NULL) );
	//srand ( 70 );
}

Sa::~Sa()
{
	
delete[] sol;
delete[] sol_best;
tour.~cTour();
	
}

void Sa::inicialitza(int nc,double t0)
{
//INICIALITZO MATRIU DISTANCIES I VECTOR SOLUCIONS	
N_Cities=nc;
sol=new int[N_Cities];	
sol_best=new int[N_Cities];
// CONFIGURACIO INICIAL A L'ATZAR
shuffle();
//INICIALITZO TEMP
T=t0;
Ti=t0;
sol_length=0;
//INICIALITZO LA "DATA STRUCTURE" de les ciutats
tour.init(N_Cities);
tour.readCities();
tour.ComputeCityDistances();
shuffle();
copySol(sol_best,sol);
sol_length=tour.getTourDist(sol);	
sol_best_length=sol_length;

}

void Sa::shuffle()
{
for(int i=0;i<N_Cities;i++){ sol[i]=i;}	

for(int j=0;j<N_Cities;j++) {
          
        int r = randInt(N_Cities-1);
        int temp = sol[j];
        sol[j] = sol[r];
        sol[r] = temp;
                }
}

void Sa::go()
{
	int steps=0;
	steps=2;
	int eq_steps=0;
	while(eq_steps<50000)
	{
		eq_steps++;
	//try move
	
	int c1=0;
	int c2=0;
	int c3=0;
	int a=0;
	int b=0;
	int z;
	double Delta;
	//double x=
	//int t=((randR()-0.5)<0)?2:3;//randInt(4);
	int t=2+randInt(4);
	//int t=0+randInt(5);
	//cout<<t<<endl;
	
	switch(t)
	{
	case 0:	
	//Swap OPT PETIT
		a=randInt(N_Cities-2);
		b=a+2;//randInt(N_Cities);
		//if (a==b) {a=2+(int) (b/2);}
        Delta=citySwap_cost(a,b);
        
        break;
	case 1:
	//TWO_OPT GRAN
		a=randInt(N_Cities-8);	  		    
	    b=(a+1);
        Delta=citySwap_cost(a,b);
        
        break;
    case 2:  
    //DISPLACE
         z=randInt(20)+1;
    	 a=randInt(N_Cities-z-1);
	     b=a+randInt(z)+1;//randInt(3)+2;  
	     Delta=displace_cost(a,b);
	    // cout<<"2"<<endl;  
	     break;
	case 3:
	//REVERSE PETIT
	     z=randInt(N_Cities-10)+1;
	     a=randInt(N_Cities-z);
	     b=a+randInt(z)+1;//randInt(N_Cities-3)+1;  
	     Delta=revOrder_cost(a,b);
	     //cout<<"3"<<endl;
	     break;
	case 4:
	//REVERSE GRAN
	     z=randInt(40)+1;
	     a=randInt(N_Cities-z);
	     b=a+randInt(z)+1;//randInt(N_Cities-3)+1;  
	     Delta=revOrder_cost(a,b);
	     //cout<<"4"<<endl;
	     break;
	 case 5:
	    a=randInt((int)(N_Cities/2)-1)+1;
	    b=2*a;
	   // cout<<a<<"  "<<b<<endl;
	    //if(a==b) b=N_Cities-2;
	    Delta=revOrder_cost(a,b);
	    break;
	 
	 
	 case 6:
	 //twoopt
	    a=randInt(N_Cities);
	    if(a==(N_Cities-1)) c2=0;
	    else c2=c1+1;
	    b=(a+2);
	    Delta=twoOpt_cost(a,b);
	    break;
	}
	
	  
	 
	
	if(Delta<0) 
	{
	move(t,c1,c2, c3,a,b );
	sol_length=tour.getTourDist(sol);
	
		
	if(sol_length<sol_best_length) 
	    {
		copySol(sol_best,sol);
		sol_best_length=sol_length ;
		}
		
	//millor solucio trobada fins el moment	

	} 
	else
	{
		
	double r=randR();
	if (r<exp(-Delta/T) )  
		{
	    move(t,c1,c2, c3,a,b );
		sol_length=tour.getTourDist(sol);
		}	
	}            	
	}
}

void Sa::citySwap(int indx1,int indx2,int * s)
{
int temp = s[indx1];
s[indx1] = s[indx2];
s[indx2] = temp;
}

double Sa::citySwap_cost(int a, int b)
{
//cout<<"here "<<a<<"   "<<b<<endl;	

int anterior_a=a-1;
if(a==0) anterior_a=N_Cities-1;
int post_a=a+1;
if (a==N_Cities-1) post_a=0;

int anterior_b=b-1;
if(b==0) anterior_b=N_Cities-1;
int post_b=b+1;

if (b==N_Cities-1) post_b=0;

//cout<<"aqui "<<a<<"   "<<b<<endl;
double d1=tour.getCityDist(sol[anterior_a],sol[a]);
double d2=tour.getCityDist(sol[a],sol[post_a]);
double d3=tour.getCityDist(sol[anterior_b],sol[b]);
double d4=tour.getCityDist(sol[b],sol[post_b]);
double d5=tour.getCityDist(sol[anterior_a],sol[b]);
double d6=tour.getCityDist(sol[b],sol[post_a]);
double d7=tour.getCityDist(sol[anterior_b],sol[a]);
double d8=tour.getCityDist(sol[a],sol[post_b]);
double d=(d8 + d7 + d6 + d5)-(d1 + d2 + d3 + d4);
//cout<<"aqui?"<<endl;
return d;
	
}

void Sa::reverse(int* array, int start, int end)
    {
        int length = end - start;
        if(length < 0)
            length+=N_Cities;
        length = length / 2 + 1;
        for(int l = 0; l < length; l++)
        {
            int temp = array[start];
            array[start] = array[end];
            array[end] = temp;
            if(++start >= N_Cities)
                start = 0;
            if(--end < 0)
                end = N_Cities-1;
        }
 
    }

void Sa::revOrder(int* s,int start, int end)
{
	
  int c, i, j;
  if(end<start)
{
int temp=start;
 start=end;
 end=temp;

} 
  for (i=start, j=end; i < j;i++, j--)
  {
    c = s[i];
    s[i] = s [j];
    s[j] = c;
}
  
}

void Sa::printSol()
{
	
cout<<endl;
for(int i=0;i<N_Cities;i++) 
{
cout<<sol_best[i]<<"  ";	
}	
cout<<endl;
	
	
}

void Sa::solApprox()
{
	for(int k=0;k<N_Cities;k++)
	{
	 for(int i=0;i<N_Cities-3;i++) 	
 {
 for(int j=i+2;j<N_Cities;j++)
 {
 	
 	  int c1=i;
	  int c2;
	  if(c1==(N_Cities-1)) c2=0;
	  else c2=c1+1;
	  
	  int c3=j;
	  int c4;
	  if(c3==(N_Cities-1)) c4=0;
	  else c4=c3+1;
	  
	    
	  double d12=tour.getCityDist(sol[c1],sol[c2]);
	  double d13=tour.getCityDist(sol[c1],sol[c3]);
	  
	//  int d14=tour.getCityDist(sol[c1],sol[c4]);
	  //int d23=tour.getCityDist(sol[c2],sol[c3]);
	  double d24=tour.getCityDist(sol[c2],sol[c4]);
	  double d34=tour.getCityDist(sol[c3],sol[c4]);
	 
      double Delta=(d13 + d24)-(d12 + d34);
      	if(Delta<0) 
	{
		//cout<<"siDelta<0"<<endl;
	citySwap(c2,c3,sol);
	//reverse(sol,index1,index2);
	//revOrder2(sol,index1,index2);
	//twoOpt(sol, c1,c2, c3 ,c4);
	
	}
 }	
 }
 sol_length=tour.getTourDist(sol); 
	}
}

void Sa::displace(int i,int j)
{
	int c1=i;
	int c2=j;
	 if(c2<c1) {
                int aux=c1;
                c1=c2;
                c2=aux;
        }
        citySwap(c1,c2,sol);
        for(int k=c2;k>c1;k--)
                citySwap(k,k-1,sol);	
}

double Sa::displace_cost(int i,int j)
{
	int ai=i-1;
	if(i==0) ai=N_Cities-1;
	
	int aj=j-1;
	int pj=j+1;
	if(j==0) aj=N_Cities-1;
	if(j==N_Cities-1) pj=0;
	
	double d=tour.getCityDist(sol[ai],sol[j])+tour.getCityDist(sol[i],sol[j])+tour.getCityDist(sol[aj],sol[pj])
          -(tour.getCityDist(sol[ai],sol[i])+tour.getCityDist(sol[pj],sol[j])+tour.getCityDist(sol[j],sol[pj]));	
	return d;
}

void Sa::twoOpt(int* s, int c2, int c3)
{
int temp = s[c2];
s[c2] = s[c3];
s[c3] = temp;
}

double Sa::twoOpt_cost(int a,int b)
{

	  int c1=a;
	  int c2;
	  if(c1==(N_Cities-1)) c2=0;
	  else c2=c1+1;
	  
	  int c3=b;
	  int c4;
	  if(c3==(N_Cities-1)) c4=0;
	  else c4=c3+1;
	  
	    
	  double d12=tour.getCityDist(sol[c1],sol[c2]);
	  double d13=tour.getCityDist(sol[c1],sol[c3]);
	  
	//  int d14=tour.getCityDist(sol[c1],sol[c4]);
	  //int d23=tour.getCityDist(sol[c2],sol[c3]);
	  double d24=tour.getCityDist(sol[c2],sol[c4]);
	  double d34=tour.getCityDist(sol[c3],sol[c4]);
	 
      double Delta=(d13 + d24)-(d12 + d34);
      return Delta;
	
}

double Sa::revOrder_cost(int i, int j)
{ 
	int ai=i-1;
	if(i==0) ai=N_Cities-1;
	int pj=j+1;
	if(pj==N_Cities) pj=0;
	
	double d1=tour.getCityDist(sol[ai],sol[j]);
	double d2=tour.getCityDist(sol[i],sol[pj]);
	double d3=tour.getCityDist(sol[ai],sol[i]);
	double d4=tour.getCityDist(sol[j],sol[pj]);
	
	return ((d1+ d2)- (d3 + d4));
		
}

void Sa::move(int t,int c1, int c2, int c3, int a,int b )
{	
	switch(t)
	{
	case 0:
		citySwap (a, b,sol); 
		break;
	case 1:	
		citySwap( a, b,sol);        
        break;
    case 2:  
    	displace(c1,c3);
	    break;
	case 3:
		revOrder(sol,a,b);
	  	break;	
	case 4:
	    revOrder(sol,a,b);
	    break;
    case 5:
	    revOrder(sol,a,b);
	    break;	 
	     	   
	case 6:
	    twoOpt(sol,c2,b);
	    break; 
	}	
}

void Sa::printBestSolution()
{
	
for(int i=0;i<N_Cities;i++)
cout<<sol_best[i]<<"   ";
cout<<endl;
cout<<"Longitud : "<<sol_best_length<<endl;
}



