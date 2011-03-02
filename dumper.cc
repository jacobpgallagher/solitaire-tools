#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

#include "solitaire.h"

using namespace std;


int main(int argc, char** argv)
{

  SolDeck* mydeck;

  if (argc > 1)
    {
      int key[DECKSIZE];
      for (int i = 0; i < DECKSIZE; ++i)
	{
	  key[i]=int(argv[1][i]) - 31;
	}
      mydeck = new SolDeck(key);

    }
  else
    {
      mydeck=new SolDeck;
    }

  int* lastDeck;

  while (true)
    {
      lastDeck = mydeck->getcards();
      for (int i=0; i < DECKSIZE; ++i)
	{
	  cout << char(lastDeck[i]);
	}
      cerr << char(mydeck->step());
      delete lastDeck;
    }

  delete mydeck;

}
