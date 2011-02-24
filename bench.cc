#include<iostream>
#include<string>
#include "solitaire.h"
using namespace std;

int main(int argc, char **argv)
{

  string help="-n \t<number> Number of integers to produce\n-q \tQuiet (benchmarking)\n";
  bool quiet = false;
  int num=0;
  
  if (argc > 1 && (static_cast<string>(argv[1]) == "-h" || 
		   static_cast<string>(argv[1]) == "--help"))
   
    {
      cout << help;
      return 0;
    }
  else if(argc > 1)
    {
      for(int i=1; i < argc; ++i)
	{
	  if(argv[i][0] == '-')
	    {
	      if(argv[i][1] == 'n')
		{
		  if(i+1 < argc)
		    {
		      num = atoi(argv[i + 1]);
		      if(!(num > 0))
			{
			  cout << "Number must be greater than 0\n" << help;
			  return 0;
			}
		    }
		  else
		    {
		      cout << "Number must be greater than 0\n" << help;
		      return 0;
		    }
		      
		}
	      else if(argv[i][1] == 'q')
		{
		  quiet = true;
		}
	      else
		{
		  cout << help;
		  return 0;
		}
	    }
	}
    }






  int key[54];
  
  //   cout << "Enter the numbers, with space between them:";
  
  for(int i = 0; i < 54; ++i)
    {
      key[i] = i + 1;
    }

  if(!quiet)
    {
      cout << endl << "Key:";
      
      for(int i = 0; i < 54; ++i)
	{
	  cout << key[i] << ", ";
	}
      
      cout << endl;
    }

   if(num == 0)
     {
   cout << "\nhow many numbers?:";
   cin >> num;
     }

 
  SolDeck mydeck(key);

  //  cout << "Deck:\n";
  //mydeck.showdeck();
  //cout << endl << endl;

  vector<int> p;
  p = mydeck.getdeck(num);

  if(!quiet)
    {
      
      cout << "String of Ints:\n";
      
      for(int i = 0; i < num; ++i)
	{
	  cout << p[i] << " ";
	}
      cout << endl << endl;
    }

//   char crap;
//   mydeck.showdeck();
//   cin.get(crap);
//   cout << "Jokerswap:\n";
//   mydeck.jokerswap();
//   mydeck.showdeck();
//   cin.get(crap);
//   mydeck.jokercut();
//   cout << "Jokercut:\n";
//   mydeck.showdeck();
//   cin.get(crap);
//   mydeck.countcut(mydeck.last->value);
//   cout << "countcut:\n";
//   mydeck.showdeck();

   return 0;
}
