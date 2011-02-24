#include<cstdlib>
#include<iostream>
#include<string>
#include "nfront.h"
#include "solitaire.h"
using namespace std;

bool keycheck(int a[]);

int main()
{
  int* key;
  key = new int[DECKSIZE];
  SolDeck* thedeck;

  thedeck=nkey();
  

  nfront(*thedeck);

  return 0;
}


bool keycheck(int a[])
{

  for(int i = 1; i <= DECKSIZE; ++i)
    {
      int count = 0;
      for(int j = 0; j < DECKSIZE; ++j)
	{
	  if(a[j] == i)
	    ++count;
	}
      if(count != 1)
	return false;
    }

  for(int i = 0; i < DECKSIZE; ++i)
    {
      if(a[i] > DECKSIZE || a[i] < 1)
	return false;
    }

  return true;

}
