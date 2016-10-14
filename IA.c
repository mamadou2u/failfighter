//IntelligenceArtificielle
#include <stdio.h>

#include <stdlib.h>
#include <time.h>

int rand_a_b(int a, int b)
{
  return rand()%(b-a) +a;
}
void IA_Niv1(P1,P2)
{
  0=coupPoing ;
  1=coupPied;
  2=kamehameha;
  4=barre;
  3=attrape;
  5=avance;
  6=recule;
  
  if(distance>15 && P1==6)
    {
      P2= rand_a_b(4,6);
    }

  if (P1==rand()%5 && distance=15)
    {
      P2=rand()%7;
    }
}
      
void IA_NIV2(P1,P2)
{
  0=coupPoing ;
  1=coupPied;
  2=kamehameha;
  4=barre;
  3=attrape;
  5=avance;
  6=recule;
  
  if(distance>20)
    {
      if(P1==2)
	{
	  P2=4;
	}
      else 
	{
	  P2=5;
	}
    }

  if (P1==rand()%5  && distance==15)
    {
      P2=rand()%5;
    }
  
}

