#include<ncurses.h>
#include<cstring>
#include<string>
#include "addmod.h"
#include "solitaire.h"
#include "nfront.h"
using namespace std;

int rowmax, colmax;


string keystring(int a)
{
  string thestring = "";
  int tmp;
  char crap;
  tmp = a;
  while(tmp >= 10)
    {
      crap = (tmp % 10) + 48;
      thestring = crap + thestring;
      tmp = tmp/10;
    }
  crap = tmp + 48;
  thestring = crap + thestring;
  if(thestring == "0")
    return "_";
  else
    return thestring;
}


int format(int a)
{
  if (a >=97 && a <= 122)
    {
      return(a - 32);
    }
  else if (a >= 65 && a <= 90)
    {
      return a;
    }
  else
    {
      return 0;
    }
}


  
int row(int index)
{
  return (index / (colmax));
}

int col(int index)
{
  return(index % (colmax));
}


string center(string title, int width)
{
  int side = (width / 2) - ((title.length() + 1) / 2);
  string top = "";
  for(int i = 0; i < side; ++i)
    {
      top = top + "-";
    }
  top = top + title + top;
  return top;
}

SolDeck* nkey()
{
  SolDeck* thedeck;

  int* key;
  key = new int[DECKSIZE];
  int ch;
  int choice=1;
  int choicemax=3;//MAX CHOICE
  bool go = true;

  string blank = "Blank Key";
  string enterown = "Enter Own key";
  string keyphrase = "Create a Key with a keyphrase";

  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  getmaxyx(stdscr, rowmax, colmax);
  while(go)
    {
      refresh();
      clear();
      mvprintw(0,0, center("Solitaire Encryption Key", colmax).c_str());
      if(choice == 1)
	mvprintw(2,0, (">" + blank + "<").c_str());
      else
	mvprintw(2,1, blank.c_str());
      if(choice == 2)
	mvprintw(3,0, (">" + enterown + "<").c_str());
      else
	mvprintw(3,1, enterown.c_str());
      if(choice == 3)
	mvprintw(4,0, (">" + keyphrase + "<").c_str());
      else
	mvprintw(4,1, keyphrase.c_str());

      move(0,0);

      ch = getch();

      if(ch == KEY_DOWN)
	{
	  if(choice < choicemax)
	    {
	      choice++;
	    }
	}
      else if (ch == KEY_UP)
	{
	  if(choice > 1)
	    {
	      choice--;
	    }
	}
      else if (ch == KEY_RESIZE)
	{
	  getmaxyx(stdscr, rowmax, colmax);
	}

      else if (ch == 10)
	{
	  go = false;

	}
     
    }


  if(choice == 1)
    {
      thedeck = new SolDeck();
    }
  else if(choice == 2)
    {
      key = enterOwn();
      thedeck = new SolDeck(key);
    }
  else if(choice == 3)
    {
      thedeck = keyphrasemaker();
    }




  return thedeck;
}

      



void nfront(SolDeck thedeck)
{

  bool go=true, plain=true;
  int ch, index=0;
  string plainstr, cipherstr;




  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  getmaxyx(stdscr, rowmax, colmax);

  while(go == true)
    {

      ////////////////////////////////////////////////////////////////////////////////////////
      refresh();
      if(ch == KEY_LEFT)
	{
	  if(index > 0)
	    index--;
	}
      else if(ch == KEY_RIGHT)
	{
	  if(index < plainstr.length())
	    index++;
	}
      else if(ch == KEY_DOWN)
	{
	  if(index + colmax < plainstr.length())
	    index += colmax;
	  else
	    index = plainstr.length();
	}
      else if (ch == KEY_UP)
	{
	  if(index >= colmax)
	    index -= colmax;
	  else
	    index = 0;

	}
      else if (ch == KEY_END)
	{
	  if((index + (colmax - (index % (colmax)))) < plainstr.length())
	    {
	      index = index + (colmax - (index % (colmax))) - 1;
	    }
	  else
	    {
	      index = plainstr.length();
	    }	   
	}
      else if (ch == KEY_HOME)
 	{
	  if(index - (index % colmax) >= 0)
	    {
	      index = index - (index % colmax);
	    }
	  else
	    {
	      index = 0; 	  
	    }
 	}

      ////////////////////////////////////////////////////////////////////////////////////////

      else if (ch == 127)//BackSpace
	{
	 
	
	  if(index > 0)
	    {
	      if(plain)
		{
		  plainstr = 
		    plainstr.substr(0,index - 1) + 
		    plainstr.substr(index,(plainstr.length() + 1) - (index));
		  
		  cipherstr = addmod(plainstr, 
				     thedeck.getdeck(plainstr.length()));
		  index--;
		}
	      else
		{
		  cipherstr = 
		    cipherstr.substr(0,index - 1) + 
		    cipherstr.substr(index,(plainstr.length() + 1) - (index));
		  
		  plainstr = submod(cipherstr, 
				     thedeck.getdeck(cipherstr.length()));
		  index--;

		}
	    }
	
	}
      else if (ch == 330)//Delete
	{
	 
	
	  if(index < (rowmax * colmax) - 1 && index < plainstr.length())
	    {
	      if(plain)
		{
		  plainstr = 
		    plainstr.substr(0,index) + 
		    plainstr.substr(index + 1,(plainstr.length() + 1) 
				    - (index));
		  
		  cipherstr = addmod(plainstr, 
				     thedeck.getdeck(plainstr.length()));
		}
	      else
		{	
	      cipherstr = 
		cipherstr.substr(0,index) + 
		cipherstr.substr(index + 1,(cipherstr.length() + 1) - (index));
	      plainstr = submod(cipherstr, 
				thedeck.getdeck(cipherstr.length()));
		}
	    }
	
	}

      ////////////////////////////////////////////////////////////////////////////////////////

      else if (ch == KEY_RESIZE)
	{
	  getmaxyx(stdscr, rowmax, colmax);
	}
      else if (ch == 9)
	{
	  if (plain)
	    plain = false;
	  else
	    plain = true;
	}
     
      ////////////////////////////////////////////////////////////////////////////////////////

      else
	{
	  if(plain)
	    {
	      if (format(ch) != 0)
		{
		  string tmp;
		  tmp += format(ch);
		  
		  plainstr = 
		    plainstr.substr(0,index) + 
		    tmp + 
		    plainstr.substr(index,(plainstr.length() + 1) - (index));
		  index++;
		  
		  
		  
		}
	      cipherstr = addmod(plainstr, thedeck.getdeck(plainstr.length()));
	    }
	  else
	    {
	      if (format(ch) != 0)
		{
		  string tmp;
		  tmp += format(ch);
		  
		  cipherstr = 
		    cipherstr.substr(0,index) + 
		    tmp + 
		    cipherstr.substr(index,(cipherstr.length() + 1) - (index));
		  index++;	  
		}
	      plainstr = submod(cipherstr, thedeck.getdeck(cipherstr.length()));
	    }
	}

      clear();
      mvprintw(0,0,(center("Plain Text", colmax)).c_str());
      mvprintw(1,0,plainstr.c_str());
      mvprintw(rowmax/2,0,(center("Cipher Text", colmax)).c_str());
      mvprintw(rowmax/2 + 1,0,cipherstr.c_str());
      
      
      //       mvprintw(20,20,("ASCII Code: " + inttostring(ch)).c_str());
      //       mvprintw(21,20,("rowmax: " + inttostring(rowmax)).c_str());
      //       mvprintw(22,20,("colmax: " + inttostring(colmax)).c_str());
      //       mvprintw(21,35,("row: " + inttostring(row(index))).c_str());
      //       mvprintw(22,35,("col: " + inttostring(col(index))).c_str());
      //       mvprintw(23,20,("index: " + inttostring(index)).c_str());
      //       mvprintw(23,35,("strlength: " + inttostring(plainstr.length())).c_str());

      
      if(plain)
	{
	  move(row(index) + 1,col(index));
	}
      else
	{
	  move(row(index) + (rowmax/2) + 1,col(index));
	}
 
      ch = getch();

    }
    


  endwin();
}

bool checkDupe(int* key, int size)
{
  bool* already;
  already = new bool[DECKSIZE];
  for (int i = 0; i < DECKSIZE; ++i)
    {
      already[i]=false;
    }
  for (int i = 0; i < size; ++i)
    {
      if (key[i] > 0 && key[i] <= DECKSIZE && already[key[i]-1])
	{
	  return true;
	}
      else if(key[i] > 0)
	{
	  already[key[i]-1]=true;
	}
    }
  
  return false;

}

bool checkDone(int* key, int size)
{
  for (int i = 0; i < size; ++i)
    {
      if (key[i] ==0)
	{
	  return false;
	}
    }
  return true;
}

int* enterOwn()
{
  ///////////////////////////////////////////////////////////////////////
  //enterown
  int* key;
  key = new int[DECKSIZE];
  for (int i = 0; i < DECKSIZE; ++i)
    {
      key[i]=0;
    }
  bool go = true;
  int ch = 0, tmp;
  string keystuff = "";
  int index = 0;
  int indexmax = 0;
  while(go)
    {
      refresh();
      clear();
      if(checkDupe(key, indexmax))
	{
	  mvprintw(rowmax/2, colmax/2, "Cannot create duplicate cards");
	}
      mvprintw(0,0,keystuff.c_str());
      move(row(tmp), col(tmp));
      ch = getch();

      if(ch >= 48 && ch <= 57 && (key[index]*10 + (ch - 48)) < DECKSIZE+1)
	{
	  key[index] = key[index]*10 + (ch -48);
	}
      else if(ch == 10 || ch == 32)
	{
	  if(index == indexmax && index < DECKSIZE-1 
	     && key[index] > 0 && key[index] < DECKSIZE+1)
	    {
	      index++;
	      indexmax++;
	    }
	  else if(index < indexmax
		  && key[index] > 0 && key[index] < DECKSIZE+1)
	    {
	      index++;
	    }
	  else if(index == indexmax && index == DECKSIZE-1 
		  && key[index] > 0 && key[index] < DECKSIZE+1)
	    {
	      
	      if (!checkDupe(key, indexmax) && checkDone(key,indexmax))
		{
		  return key;
		}
	    }
	}
      else if(ch == KEY_RIGHT)
	{
	  if(index < indexmax)
	    {
	      index++;
	    }
	}
      else if(ch == KEY_LEFT)
	{
	  if(index > 0)
	    {
	      index--;
	    }
	}
      else if(ch == 127)
	{
	  key[index] = key[index]/10;
	}



      keystuff = "";
      tmp = 0;

      for(int j=0; j <= indexmax; j++)
	{
	  if(j < index)
	    {
	      if(key[j] > 99)
		{
		  tmp += 4;
		}
	      else if(key[j] > 9)
		{
		  tmp +=3;
		}
	      else
		{
		  tmp +=2;
		}
	    }
	  else if(j == index && key[j] == 0)
	    {
	    }
	  else if(j == index)
	    {
	      if(key[j] > 99)
		{
		  tmp +=3;
		}
	      else if(key[j] > 9)
		{
		  tmp +=2;
		}
	      else
		{
		  tmp +=1;
		}
	    }

	  keystuff = keystuff + keystring(key[j]) + " ";
	}



	 
    }
}


SolDeck* keyphrasemaker()
{
  bool go = true;
  string keyphrase = "";
  int ch, index=0;
  SolDeck* thedeck;

  thedeck = new SolDeck();

  do{

  while(go == true)
    {





      ////////////////////////////////////////////////////////////////////////////////////////
      refresh();

      if(ch == KEY_LEFT)
	{
	  if(index > 0)
	    index--;
	}
      else if(ch == KEY_RIGHT)
	{
	  if(index < keyphrase.length())
	    index++;
	}
      else if(ch == KEY_DOWN)
	{
	  if(index + colmax < keyphrase.length())
	    index += colmax;
	  else
	    index = keyphrase.length();
	}
      else if (ch == KEY_UP)
	{
	  if(index >= colmax)
	    index -= colmax;
	  else
	    index = 0;

	}
      else if (ch == KEY_END)
	{
	  if((index + (colmax - (index % (colmax)))) < keyphrase.length())
	    {
	      index = index + (colmax - (index % (colmax))) - 1;
	    }
	  else
	    {
	      index = keyphrase.length();
	    }	   
	}
      else if (ch == KEY_HOME)
 	{
	  if(index - (index % colmax) >= 0)
	    {
	      index = index - (index % colmax);
	    }
	  else
	    {
	      index = 0; 	  
	    }
 	}
      else if(ch == 10)
	{
	  go = false;
	  break;
	}

      ////////////////////////////////////////////////////////////////////////////////////////

      else if (ch == 127)//BackSpace
	{
	 
	
	  if(index > 0)
	    {
	      keyphrase = 
		keyphrase.substr(0,index - 1) + 
		keyphrase.substr(index,(keyphrase.length() + 1) - (index));
	
	      index--;
	    }
	
	}
      else if (ch == 330)//Delete
	{
	 
	
	  if(index < (rowmax * colmax) - 1 && index < keyphrase.length())
	    {
	      keyphrase = 
		keyphrase.substr(0,index) + 
		keyphrase.substr(index + 1,(keyphrase.length() + 1) - (index));
	
	    }
	
	}

      ////////////////////////////////////////////////////////////////////////////////////////

      else if (ch == KEY_RESIZE)
	{
	  getmaxyx(stdscr, rowmax, colmax);
	}

     
      ////////////////////////////////////////////////////////////////////////////////////////

      else
	{
	  
	  
	  if (format(ch) != 0)
	    {
	      string tmp;
	      tmp += format(ch);
	      
	      keyphrase = 
		keyphrase.substr(0,index) + 
		tmp + 
		keyphrase.substr(index,(keyphrase.length() + 1) - (index));
	      index++;
	      
	      
	      
	    }
	  
	    
	  
	}

      clear();
      mvprintw(0,0,(center("Enter the Phrase", colmax)).c_str());
      mvprintw(1,0,keyphrase.c_str());
      
      
      //       mvprintw(20,20,("ASCII Code: " + inttostring(ch)).c_str());
      //       mvprintw(21,20,("rowmax: " + inttostring(rowmax)).c_str());
      //       mvprintw(22,20,("colmax: " + inttostring(colmax)).c_str());
      //       mvprintw(21,35,("row: " + inttostring(row(index))).c_str());
      //       mvprintw(22,35,("col: " + inttostring(col(index))).c_str());
      //       mvprintw(23,20,("index: " + inttostring(index)).c_str());
      //       mvprintw(23,35,("strlength: " + inttostring(plainstr.length())).c_str());

      
	  move(row(index) + 1,col(index));

	  ch = getch();
 


    }
  }while(!(*thedeck).keyin(keyphrase.c_str()));



  return thedeck;
}
