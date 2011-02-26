#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

#include "solitaire.h"

using namespace std;


int MAX=100000000;

int HASHSIZE=23;

int main()
{
  if (HASHSIZE > DECKSIZE)
    {
      HASHSIZE = DECKSIZE;
    }

  int key[DECKSIZE];

  for(int i = 0; i < DECKSIZE; ++i)
    {
      key[i]=i;
    }

  SolDeck mydeck;


  string* hashTable;

  hashTable=new string[int(pow(2,HASHSIZE))];
  int* nowDeck;
  unsigned int hashMap;
  string toHash;

  for(int i = 0; i < MAX; ++i)
    {
      
      if (i % 10000 == 0)
	{
	  int sumHit=0;
	  int sumLen=0;

	  for (int j = 0; j < int(pow(2,HASHSIZE)); ++j)
	    {
	      if(hashTable[j].length() > 0)
		{
		  sumHit++;
		  sumLen += hashTable[j].length();
		}

	    }
	  cerr << "Hit:" << (sumHit/pow(2,HASHSIZE))*100 << "%\n";
	  cerr << "Average length: " << sumLen/double(sumHit) << endl;

	  cerr << i << endl;
	}

      mydeck.getdeck(i+1);
      nowDeck=mydeck.getcards();
      
      hashMap = 0;
      toHash = "";
      for(int j = 0; j < HASHSIZE; ++j)
  	{
  	  hashMap = hashMap | ((nowDeck[j] & 1) << j);
  	}

      for(int j = 0; j < DECKSIZE; ++j)
  	{
	  
  	  toHash += char(nowDeck[j]);
	}
      //      cout << hashMap << endl;

      for (int j = 0; j < hashTable[hashMap].length(); j = j + DECKSIZE)
	{
	  if (hashTable[hashMap].substr(j,DECKSIZE) == toHash)
	    {
	      cout << "Step " << i << endl;
	      for (int k = 0; k < toHash.length(); ++k)
		{
		  cout << int(toHash[k]) << " ";
		}
	      cout << endl;
	    }
	}
      hashTable[hashMap]+=toHash;
      
    }
      
      
}
