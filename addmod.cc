#include<string>
#include "addmod.h"

using namespace std;


string addmod(string plain, vector<int> a)
{
  int *cipher;


  cipher = new int[plain.length()];

  for(int i = 0; i < plain.length(); ++i)
    {
      cipher[i] = plain.at(i) - 64;
    }


  for(int i = 0; i < plain.length(); ++i)
    {
      cipher[i] = ((cipher[i] + a[i]) % 26);
      if(cipher[i] == 0)
	cipher[i] = 26;
      cipher[i] += 64;
    }

  string cipherstr;

  for(int i = 0; i < plain.length(); ++i)
    {
      cipherstr += cipher[i];
    }

  delete cipher;


  return cipherstr;
} 


string submod(string plain, vector<int> a)
{
  int *cipher;


  cipher = new int[plain.length()];

  for(int i = 0; i < plain.length(); ++i)
    {
      cipher[i] = plain.at(i) - 64;
    }


  for(int i = 0; i < plain.length(); ++i)
    {
      cipher[i] = ((cipher[i] - a[i] + 52) % 26);
      if(cipher[i] == 0)
	cipher[i] = 26;
      cipher[i] += 64;
    }

  string cipherstr;

  for(int i = 0; i < plain.length(); ++i)
    {
      cipherstr += cipher[i];
    }

  delete cipher;

  return cipherstr;
} 

