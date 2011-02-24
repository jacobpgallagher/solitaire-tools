#include<cstdlib>
#include "solitaire.h"

using namespace std;


SolDeck::SolDeck()
{
  first = new Card;
  CardPtr current = first;
  for(int i = 0; i < (DECKSIZE - 1); ++i)
    {
      current->value = i+1;
      current->link = new Card;
      if(i+1 == DECKSIZE - 1)
	{
	  JokerA = current;
	  PrevB = current;
	}
      else if(i+1 == DECKSIZE - 2)
	PrevA = current;

      current = current->link;
    }
  last = current;
  current->value = DECKSIZE;
  current->link = NULL;
  JokerB = current;
  Afirst = true;
}

SolDeck::SolDeck(int a[])
{
  JokerA = NULL;
  JokerB = NULL;
  PrevA = NULL;
  PrevB = NULL;

  CardPtr current;
  first = new Card;
  current = first;
  for(int i = 0; i < DECKSIZE; ++i)
    {
      current->value = a[i];
      if(a[i] == (DECKSIZE - 1))
	{
	  JokerA = current;
	  if(JokerB == NULL)
	    Afirst = true;
	}
      else if(a[i] == DECKSIZE)
	{
	  JokerB = current;
	  if(JokerA == NULL)
	    Afirst = false;
	}
      if(i + 1 < DECKSIZE && a[i + 1] == (DECKSIZE - 1))
	PrevA = current;
      else if(i + 1 < DECKSIZE && a[i + 1] == DECKSIZE)
	PrevB = current;
      if(i == (DECKSIZE - 1))
	{
	  last = current;
	  current->link = NULL;
	}
      else
	{
	  current->link = new Card;
	  current = current->link;
	}
    }
  if(PrevA == NULL)
    PrevA = last;
  if(PrevB == NULL)
    PrevB = last;
}

SolDeck::SolDeck(const char* a)
{
  first = new Card;
  CardPtr current = first;
  for(int i = 0; i < (DECKSIZE - 1); ++i)
    {
      current->value = i+1;
      current->link = new Card;
      if(i+1 == DECKSIZE - 1)
	{
	  JokerA = current;
	  PrevB = current;
	}
      else if(i+1 == DECKSIZE - 2)
	PrevA = current;

      current = current->link;
    }
  last = current;
  current->value = DECKSIZE;
  current->link = NULL;
  JokerB = current;
  Afirst = true;

  keyin(a);
}

SolDeck::SolDeck(vector<int> a)
{
  JokerA = NULL;
  JokerB = NULL;
  PrevA = NULL;
  PrevB = NULL;

  CardPtr current;
  first = new Card;
  current = first;
  for(int i = 0; i < DECKSIZE; i++)
    {
      current->value = a[i];
      if(a[i] == (DECKSIZE - 1))
	{
	  JokerA = current;
	  if(JokerB == NULL)
	    Afirst = true;
	}
      else if(a[i] == DECKSIZE)
	{
	  JokerB = current;
	  if(JokerA == NULL)
	    Afirst = false;
	}
      if(a[i + 1] == (DECKSIZE - 1) && JokerA == NULL)
	PrevA = current;
      else if(a[i + 1] == DECKSIZE && JokerB == NULL)
	PrevB = current;
      if(i == (DECKSIZE - 1))
	last = current;
      else
	{
	  current->link = new Card;
	  current = current->link;
	}
    }
  if(PrevA == NULL)
    PrevA = last;
  else if(PrevB == NULL)
    PrevB = last;
}


SolDeck::~SolDeck()
{
  CardPtr tmp;
  for(CardPtr iter = first; iter != NULL; )
    {
      tmp = iter->link;
      delete iter;
      iter = tmp;
    }

}


int SolDeck::step()
{
  jokerswap();
  jokercut();

  //count cut////////////////////////////////////////////////////////////
  {
    if(last->value == (DECKSIZE - 1) || last->value == DECKSIZE)
      countcut((DECKSIZE - 1));
    else 
      countcut(last->value);
  }
  //Final Step/////////////////////////////////////////////////////////////

  return finalcount(first->value);

}

vector<int> SolDeck::getdeck(int num)
{
  if(pad.size() >= num)
    {
      return pad;
    }
  else
    {
      while(pad.size() < num)
	{
	  pad.push_back(step());
	}
      return pad;
    }
}







void SolDeck::countcut(int count)
{
  if(count != (DECKSIZE - 1))
    {
      
      CardPtr PreLast;
      for(PreLast = first; PreLast->link->link !=NULL; PreLast = PreLast->link)
	{
	}
      
      CardPtr iter = first;
      
      
      CardPtr BackOfCount = NULL;
      
      for(int i = 0; i < count; ++i)
	{
	  if(iter != NULL && (iter->value == (DECKSIZE - 1) || iter->value == DECKSIZE))
	    {
	      if(Afirst)
		Afirst = false;
	      else
		Afirst = true;
	    }
	  iter = iter->link;
	  if(i == count - 2)
	    {
	      BackOfCount = iter;
	    }
	}
      
      if(BackOfCount == NULL)
	{
	  BackOfCount = first;
	}
      if(JokerA == first)
	PrevA = PreLast;
      else if(JokerB == first)
	PrevB = PreLast;
      if(BackOfCount->link == JokerA)
	PrevA = last;
      else if(BackOfCount->link == JokerB)
	PrevB = last;
      CardPtr tmpfirst = first;
      first = iter;
      PreLast->link = tmpfirst;
      BackOfCount->link = last;
    }
}


void SolDeck::jokerswap()
{


  //////this fucntion needs work.

  CardPtr tmp;


  if(
     (JokerB->link == JokerA) || 
     (JokerA == last && JokerB->link->link != JokerA) ||
     (JokerB == last && first != JokerA) ||
     (JokerB->link == last && JokerA->link != JokerB)
     )
    {
      if(Afirst)
	Afirst = false;
      else
	Afirst = true;
    }

  last->link = first;

  if(last == JokerB)
    {
      last = PrevB;
    }
  else if(last == JokerA)
    {
      last = PrevA;
      if(PrevA == JokerB)
	last = PrevB;
    }
  if(first == JokerA && JokerA->link != JokerB)
    {
      first = JokerA->link;
    }
  else if(first == JokerB)
    {
      first = JokerB->link;
      if(first == JokerA)
	first = JokerA->link;
    }

  if(PrevB == JokerA)
    PrevB = PrevA;
  tmp = JokerA->link;
  JokerA->link = JokerA->link->link;
  PrevA->link = tmp;
  PrevA->link->link = JokerA;
  PrevA=PrevA->link;
  if(PrevB == PrevA)
    PrevB = PrevB->link;
  if(last == PrevA)
    last = JokerA;


  if(PrevA == JokerB)
    PrevA = PrevB;
  tmp = JokerB->link;
  JokerB->link = JokerB->link->link->link;
  PrevB->link = tmp;//this seems to be the problem.
  PrevB->link->link->link = JokerB;
  PrevB=PrevB->link->link;
  if(PrevA == PrevB)
    PrevA = PrevA->link;
  if(last == PrevB)
    last = JokerB;

  last->link = NULL;

}

void SolDeck::jokercut()
{

  //triple cut///////////////////////////////////////////////
  {

    CardPtr tmp;
    CardPtr tmplast;

    if(Afirst)
      {
	tmp = first;
	tmplast = last;
	if(JokerB->link != NULL)
	  {
	    first = JokerB->link;
	    last->link = JokerA;
	  }
	else
	  {
	    first = JokerA;
	  }
	if(JokerB->link != JokerA && tmp != first && tmp != JokerA)
	  JokerB->link = tmp;
	else
	  JokerB->link = NULL;
	if(PrevA != last)
	  {
	    PrevA->link = NULL;
	    last = PrevA;
	  }
	else
	  {
	    last = JokerB;
	  }
	if(tmplast != JokerB)
	  PrevA = tmplast;
	else
	  {
	    //  PrevA = last;
	  }
      }
    else
      {
	tmp = first;
	tmplast = last;
	if(JokerA->link != NULL)
	  {
	    first = JokerA->link;
	    last->link = JokerB;
	  }
	else
	  {
	    first = JokerB;
	  }
	if(JokerA->link != JokerB && tmp != first && tmp != JokerB)
	  JokerA->link = tmp;
	else
	  JokerA->link = NULL;
	if(PrevB != last)
	  {
	    PrevB->link = NULL;
	    last = PrevB;
	  }
	else
	  {
	    last = JokerA;
	  }
	if(tmplast != JokerA)
	  PrevB = tmplast;
	else
	  {
	  //  PrevB = last;
	  }

      }


  }

}

int SolDeck::finalcount(int count)
{
  
  CardPtr iter = first;
  if(count == DECKSIZE)
    count = (DECKSIZE - 1);
  for(int i = 0; i < count; ++i)
    {
      iter = iter->link;
    }
  
  if(iter->value == (DECKSIZE - 1) || iter->value == DECKSIZE)
    {
      return step();
    }
  else
    {
      return iter->value;
    }
  }


bool SolDeck::keyin(const char* key)
{
  int count = 0;
  for(int i = 0; key[i] != '\0'; i++)
    {
      count++;
    }
  int* keyint;
  keyint = new int[count];

  for(int i = 0; i < count; i++)
    {
      if(key[i] >= 97 && key[i] <= 122)
	{
	  keyint[i] = key[i] - 96;
	}
      else if(key[i] >= 65 && key[i] <= 90)
	{
	  keyint[i] = key[i] - 64;
	}
      else
	{
	  delete []keyint;
	  return false;
	}
    }
  for(int i = 0; i < count; i++)
    {
      jokerswap();
      jokercut();
      {
	if(last->value == (DECKSIZE - 1) || last->value == DECKSIZE)
	  countcut((DECKSIZE - 1));
	else 
	  countcut(last->value);
      }
      countcut(keyint[i]);
    }
  delete []keyint;
  return true;


}

//remove!
void SolDeck::showdeck()
{
  for(CardPtr iter=first; iter != NULL; iter=iter->link)
    {
      if(iter->value < 10)
	{
	  cout << "0";
	}
      cout << iter->value << ", ";
    }
  cout << "\nfirst:" << first->value
       << "\nlast:" << last->value
       << "\nPrevA:" << PrevA->value
       << "\nJokerA:" << JokerA->value
       << "\nPrevB:" << PrevB->value
       << "\nJokerB:" << JokerB->value
       << "\nAfirst:" << Afirst;
  cout << endl << endl;
}

int* SolDeck::getcards()
{

  int* temp;
  temp = new int[DECKSIZE];

  int i = 0;

  for(CardPtr iter=first; iter != NULL; iter=iter->link)
    {
      temp[i] = iter->value;
      ++i;
    }

  return temp;
}
