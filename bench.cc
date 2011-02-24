#include<iostream>
#include<string>
#include "solitaire.h"
using namespace std;

int main(int argc, char **argv)
{

  string help="-n \t<number> Number of integers to produce\n-q \tQuiet (benchmarking)\n-p \tShow probability of a repeate\n";
  bool quiet = false;
  bool probability = false;
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
	      else if(argv[i][1] == 'p')
		{
		  probability = true;
		}
	      else
		{
		  cout << help;
		  return 0;
		}
	    }
	}
    }






  int key[DECKSIZE];
  
  //   cout << "Enter the numbers, with space between them:";
  
  for(int i = 0; i < DECKSIZE; ++i)
    {
      key[i] = i + 1;
    }

  if(!quiet)
    {
      cout << endl << "Key:";
      
      for(int i = 0; i < DECKSIZE; ++i)
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

  if(probability)
    {
      for(int i = 1; i < num; ++i)
	{
	  p = mydeck.getdeck(i);
		  mydeck.showdeck();
	  int repeat = 0;
	  int modded = 0;
	  int mod = 26;
	  //      cout << "String of Ints:\n";
	  
	  int lastrepeat=1;
	  vector<int> repeats;
	  
	  for(int i = 1; i < num; ++i)
	    {
	      if(p[i-1] == p[i])
		{
		  repeat++;
		  modded++;
		}
	      else if(p[i-1]%mod == p[i]%mod)
		{
		  //		  mydeck.showdeck();
		  modded++;
		  repeats.push_back(lastrepeat);
		  lastrepeat=-1;
		}
	      lastrepeat++;
	      
	    }
	  
	  
	  //      cout << "The probability of a repeated output is 1 in " << (double)num/(double)repeat << endl;
	  //      cout << "The probability of a repeated output modded " << mod << "  by is 1 in " << (double)num/(double)modded << endl;
	  for(int i = 0; i < repeats.size(); ++i)
	    {
	      //	  cout << repeats[i] << ", ";
	    }
	  //      cout << endl;
	  
	}
    }
  else
    {

  p = mydeck.getdeck(num);
    }



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
