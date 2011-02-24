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
  key = new int[54];
  SolDeck* thedeck;
  //  char go;
//   do
//     {
//       cout << "Enter the key, represented in numbers and Joker A is 53 and Joker B is 54:\n";
      
//       for(int i = 0; i < 54; ++i)
// 	{
// 	  cin >> key[i];
// 	}
//       cout << endl << "Key:";
      
//       for(int i = 0; i < 54; ++i)
// 	{
// 	  cout << key[i] << ", ";
// 	}
//       if(keycheck(key))
// 	{
//       cout << endl << "Is this correct? (y or n)";
//       cin >> go;
// 	}
//       else
// 	{
// 	  cout << endl << "Incorrect Key.";
// 	}
//     }while(go != 'y' && go != 'Y');

  thedeck=nkey();
  

  nfront(*thedeck);

  return 0;
}


bool keycheck(int a[])
{

  for(int i = 1; i <= 54; ++i)
    {
      int count = 0;
      for(int j = 0; j < 54; ++j)
	{
	  if(a[j] == i)
	    ++count;
	}
      if(count != 1)
	return false;
    }

  for(int i = 0; i < 54; ++i)
    {
      if(a[i] > 54 || a[i] < 1)
	return false;
    }

  return true;

}
