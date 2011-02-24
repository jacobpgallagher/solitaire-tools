#include<iostream>
#include "solitaire.h"
#include "addmod.h"

int main(int argc, char **argv)
{

  int whicharg;
  bool encrypt;

  if(!(argc > 2))
    {
      cout << "Usage: " << argv[0] << " -{e,d} <PASSPHRASE>\n";
      exit(1);
    }
  else
    {
      if(argv[1][0] == '-')
	{
	  if(argv[1][1] == 'e')
	    encrypt = true;
	  else if(argv[1][1] == 'd')
	    encrypt = false;
	  else
	    {
	      cout << "Usage: " << argv[0] << " -{e,d} <PASSPHRASE>\n";
	      exit(1);
	    }
	}
      else
	{
	  cout << "Usage: " << argv[0] << " -{e,d} <PASSPHRASE>\n";
	  exit(1);
	}
    }

      
  
  SolDeck thedeck(argv[2]);

  char input;
  string wholething = "";

  while(cin.get(input))
    {
      if(input >= 97 && input <= 122)
	{
	  input -= 32;
	}
      if(input >= 65 && input <= 90)
	{
	  wholething += input;
	}
    }
  if(encrypt)
    cout << addmod(wholething, thedeck.getdeck(wholething.length()));
  else
    cout << submod(wholething, thedeck.getdeck(wholething.length()));

  return 0;
}
