#include<fstream>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include "addmod.h"
#include "solitaire.h"

using namespace std;

const int interval = 10000;



void keyadvance(string& key);

void format(string& text);

double* asciistat(string text);

long double howmany(int, int);

string convertime(double a);

string itoa(int a);

int main(int argc, char **argv)
{

 string folder = "", cipher = "", key = "";
 string name = "";
 int length=0, strlength, min=0;
 char tmp;
 ofstream fout;
 
 bool preread = false;



  if(argc > 1)
    {

      string help = "Usage: alphabreaker (OPTIONS) ciphertext\n\nOptions:\n-f || --folder\tOutput Folder\n--max\t\tMax number of characters to key\n--min\t\tMinimum characters to use in key.\n-p\t\tSet for preread on \n\t\t(only takes ouput with < 2% X's and Z's and > 4% A's and E's\n";
      for(int i=1; i < argc; ++i)
	{
	  if(argv[i][0] == '-')
	    {
	      if(argv[i][1] == 'f' || strcmp(argv[i], "--folder") == 0 )

		{
		  if(i + 1 < argc)
		    folder = argv[i + 1];    
		  else
		    {
		      cout << help;
		      return 0;
		    }
		    
		}
	      else if(!strcmp(argv[i], "--max"))
		{
		  if(i + 1 < argc)
		    length = atoi(argv[i + 1]);
		  else
		    {
		      cout << help;
		      return 0;
		    }
		}
	      else if(!strcmp(argv[i],"--min"))
		{
		  if(i + 1 < argc)
		    min = atoi(argv[i + 1]);
		  else
		    {
		      cout << help;
		      return 0;
		    }
		}
	      else if(argv[i][1] == 'p')
		{
		  preread = true;
		}
	      else
		{
		  cout << help;
		  return 0;
		}
	    }
	//   else
// 	    {
// 	      if(cipher == "")
// 		cipher = argv[i];
// 	      else
// 		{
// 		  cout << help;
// 		  return 0;
// 		}


// 	    }
	}
    

    }
  //////////////////////////////////////////////////////////////////
           
  if(folder == "")
    {      
      cout << "Enter Folder name:";
      cin >> folder;
    }
  if(length == 0)
    {
      cout << "How many characters int? (MAX)";
      cin >> length;
    
      
      cout << "How few characters?(MIN)";
      cin >> min;
    }  
  if(cipher == "")
    {
      cout << "Enter ciphertext(finish with Ctrl-d):";
      while(cin.get(tmp))
	{
	  cipher += tmp;
	}
    }
      
  format(cipher);
  cout << "Ciphertext: " << cipher << endl;
  strlength = cipher.length();

  long double possibilities = howmany(min, length);

  cout << "There are " << possibilities << " possible comibinations\n";
      
  for(int i = 0; i < min;i++)
    {
      key += "A";
    }
  SolDeck *temp;


  string tempdec;
  double* asciiarray;

  long double count = 0;
  int tempcount = 0;

  int lasttime = time(0);

  cout << "0% complete\n";

  while(key.length() <= length)
    {

      temp = new SolDeck(key.c_str());

      tempdec = submod(cipher, temp->getdeck(strlength));

      if(preread)
	asciiarray = asciistat(tempdec);

      if(!(preread) || (asciiarray[88] < 2 && asciiarray[90] < 2 && asciiarray[65] > 4 && asciiarray[69] > 4))
	{
	  fout.open((folder + key + ".txt").c_str());
	  if(fout.fail())
	    {
	      cout << "Opening file " << (folder + key + ".txt") 
		   << " failed -- Exiting\n";
	      exit(1);
	    }
	  
	  
	  fout << tempdec;
	  
	  fout.close();
	}
      
      delete temp;

      if (preread)
	delete asciiarray;


      ////////////////////
      keyadvance(key);

      ++count;
      ++tempcount;
      if(tempcount >= interval)
	{
	  cout << (count/possibilities)*100 << "% complete (" << count 
	       << " of " << possibilities << ") " 
	       << convertime((possibilities - count)/(interval/(time(0) - lasttime)))    
	       << " left\n";
	  lasttime = time(0);
	  tempcount = 0;
	}

    }

  cout << count;


}

void keyadvance(string& key)
{
  bool end = true;
  if(key[key.length() - 1] == 'Z')
    {
      for(int i = key.length() - 1; i >= 0; i--)
	{
	  if(key[i] == 'Z')
	    {
	      key[i] = 'A';
	    }
	  else
	    {
	      end = false;
	      key[i]++;
	      break;
	    }
	  
	}
      if(end)
	key = key + "A";
    }
  else
    {
      key[key.length() - 1]++;
    }
}

void format(string& text)
{
  string returnstring = "";

  for(int i = 0; i < text.length(); i++)
    {
      
      if (text[i] >=97 && text[i] <= 122)
	{
	  returnstring += (text[i] - 32);
	}
      else if (text[i] >= 65 && text[i] <= 90)
	{
	  returnstring += text[i];
	}
    }

  text = returnstring;
}

double* asciistat(string text)
{

  int counttotal=0;

  int ascii[255];

  double* asciir;
    asciir = new double[255];

  for(int i = 0; i < 255; i++)
    {
      ascii[i] = 0;
    }
  for(int i = text.length(); i > 0; --i)
    {
      ascii[((int)text.at(i-1))]++;
      counttotal++;
    }

  for(int i = 0; i < 255; i++)
    {

      asciir[i] = (ascii[i] / (double)counttotal)*100;

    }
  
  return asciir;
}

long double howmany(int min, int max)
{

 long double total = 0;

  for(int i = min; i <= max; ++i)
    {
      total += pow(26.0,i);
    }
  return total;
}

string convertime(double a)
{

  string r = "";
  int seconds;
  int minutes;
  int hours;
  int days;
  int months;
  int years;

  years = (int)(a / 31536000);
  a = a - (years * 31536000.0);
  months = (int)(a / 1036800);
  a = a - (months * 1036800.0);
  while(months >= 12)
    {
      ++ years;
      months -= 12;
    }
  days = (int)(a / 86400);
  a = a - (days * 86400.0);
  hours = (int)(a / 3600);
  a = a - (hours * 3600.0);
  minutes = (int)(a / 60);
  a = a - (minutes * 60.0);
  seconds = (int)a;

  r = itoa(seconds) + 's';
  if(minutes > 0)
    r = itoa(minutes) + "m " + r;
  if(hours > 0)
    r = itoa(hours) + "H " + r;
  if(days > 0)
    r = itoa(days) + "D " + r;
  if(months > 0)
    r = itoa(months) + "M " + r;
  if(years > 0)
    r = itoa(years) + "Years and " + r;

  if(years < 0)
    r = "More than 2147483648 Years";

  return r;
}

string itoa(int a)
{
  string tmp = "";
  while(a > 0)
    {
      tmp = (char)((a % 10) + 48) + tmp;
      a = a / 10;
    }
  return tmp;
}
