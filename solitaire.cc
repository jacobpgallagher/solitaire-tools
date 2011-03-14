#include<cstdlib>
#include "solitaire.h"

using namespace std;


SolDeck::SolDeck()
{
  first = new Card;
  CardPtr current = first;
  first->prev=NULL;
  for(int i = 0; i < (DECKSIZE - 1); ++i)
    {
      current->value = i+1;
      current->next = new Card;
      current->next->prev=current;
      if(i+1 == DECKSIZE - 1)
	{
	  JokerA = current;
	}
      current = current->next;
    }
  last = current;
  current->value = DECKSIZE;
  current->next = NULL;
  JokerB = current;
  Afirst = true;
}

SolDeck::SolDeck(int a[])
{
  JokerA = NULL;
  JokerB = NULL;

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
      if(i == (DECKSIZE - 1))
	{
	  last = current;
	  current->next = NULL;
	}
      else
	{
	  current->next = new Card;
	  current->next->prev=current;
	  current = current->next;
	}
    }
}

// SolDeck::SolDeck(const char* a)
// {
//   first = new Card;
//   CardPtr current = first;
//   for(int i = 0; i < (DECKSIZE - 1); ++i)
//     {
//       current->value = i+1;
//       current->link = new Card;
//       if(i+1 == DECKSIZE - 1)
// 	{
// 	  JokerA = current;
// 	  PrevB = current;
// 	}
//       else if(i+1 == DECKSIZE - 2)
// 	PrevA = current;

//       current = current->link;
//     }
//   last = current;
//   current->value = DECKSIZE;
//   current->link = NULL;
//   JokerB = current;
//   Afirst = true;

//   keyin(a);
// }

// SolDeck::SolDeck(vector<int> a)
// {
//   JokerA = NULL;
//   JokerB = NULL;
//   PrevA = NULL;
//   PrevB = NULL;

//   CardPtr current;
//   first = new Card;
//   current = first;
//   for(int i = 0; i < DECKSIZE; i++)
//     {
//       current->value = a[i];
//       if(a[i] == (DECKSIZE - 1))
// 	{
// 	  JokerA = current;
// 	  if(JokerB == NULL)
// 	    Afirst = true;
// 	}
//       else if(a[i] == DECKSIZE)
// 	{
// 	  JokerB = current;
// 	  if(JokerA == NULL)
// 	    Afirst = false;
// 	}
//       if(a[i + 1] == (DECKSIZE - 1) && JokerA == NULL)
// 	PrevA = current;
//       else if(a[i + 1] == DECKSIZE && JokerB == NULL)
// 	PrevB = current;
//       if(i == (DECKSIZE - 1))
// 	last = current;
//       else
// 	{
// 	  current->link = new Card;
// 	  current = current->link;
// 	}
//     }
//   if(PrevA == NULL)
//     PrevA = last;
//   else if(PrevB == NULL)
//     PrevB = last;
// }


SolDeck::~SolDeck()
{
  CardPtr tmp;
  for(CardPtr iter = first; iter != NULL; )
    {
      tmp = iter->next;
      delete iter;
      iter = tmp;
    }

}


int SolDeck::step()
{
  // cout << "Showing" <<endl;
  // showdeck();
  jokerswap();
  // cout << "swapped\n";
  // showdeck();
  jokercut();
  // cout << "triple cut\n";
  // showdeck();

  //count cut////////////////////////////////////////////////////////////
  {
    if(last->value == (DECKSIZE - 1) || last->value == DECKSIZE)
      countcut((DECKSIZE - 1));
    else 
      countcut(last->value);
  }
  //Final Step/////////////////////////////////////////////////////////////
  // cout << "count cut\n";
  // showdeck();

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








void SolDeck::jokerswap()
{
  CardPtr tmp;

  last->next=first;
  first->prev=last;

  if (last == JokerA)
    {
      last = JokerA->prev;
    }
  else if (first == JokerA)
    {
      first = JokerA->next;
    }
  else if (JokerA->next == last)
    {
      last = JokerA;
    }
  tmp=JokerA->next;
  JokerA->next=JokerA->next->next;
  tmp->prev=JokerA->prev;
  
  tmp = JokerA->prev;
  JokerA->prev = JokerA->next->prev;
  tmp->next=JokerA->prev;

  tmp = JokerA->next->prev;
  JokerA->next->prev=JokerA;
  tmp->next = JokerA;

  //JokerA Moved.

  // last->next = NULL;
  // first->prev= NULL;
  // showdeck();
  // last->next=first;
  // first->prev=last;
  

  if (last == JokerB)
    {
      last = JokerB->prev;
    }
  else if (first == JokerB)
    {
      first = JokerB->next;
    }
  else if(JokerB->next->next == last)
    {
      last = JokerB;
    }
  
  tmp = JokerB->next;
  JokerB->next = JokerB->next->next->next;
  tmp->prev=JokerB->prev;

  tmp = JokerB->prev;
  JokerB->prev=JokerB->next->prev;
  tmp->next=JokerB->next->prev->prev;

  tmp=JokerB->next->prev;
  JokerB->next->prev = JokerB;
  tmp->next=JokerB;

  last->next = NULL;
  first->prev = NULL;


  if (JokerA->next == JokerB)
    {
      Afirst = true;
    }
  else if (first == JokerA)
    {
      Afirst = true;
    }
  else if (first == JokerB)
    {
      Afirst = false;
    }
  else if (first->next == JokerA)
    {
      Afirst = true;
    }
  else if (first->next == JokerB)
    {
      Afirst = false;
    }
  else if (first->next->next == JokerB)
    {
      Afirst = false;
    }

}

void SolDeck::jokercut()
{

  CardPtr tmp;

  if(Afirst)
    {
      if(JokerA->prev == NULL && JokerB->next == NULL)
	{
	  //Do Nothing.
	}
      else if(JokerA->prev == NULL)
	{
	  JokerA->prev = last;
	  last->next=JokerA;
	  first = JokerB->next;
	  last = JokerB;
	  last->next=NULL;
	  first->prev=NULL;
	}
      else if(JokerB->next == NULL)
	{
	  JokerB->next = first;
	  first->prev=JokerB;
	  last=JokerA->prev;
	  first = JokerA;
	  last->next=NULL;
	  first->prev=NULL;
	}
      else
	{
	  tmp = first;
	  first=JokerB->next;
	  first->prev = NULL;
	  JokerB->next = tmp;
	  JokerB->next->prev=JokerB;

	  tmp = last;
	  last = JokerA->prev;
	  last->next = NULL;
	  JokerA->prev = tmp;
	  JokerA->prev->next = JokerA;
	}
    }
  else
    {
      if(JokerA->prev == NULL && JokerB->next == NULL)
	{
	  //Do Nothing.
	}
      else if(JokerB->prev == NULL)
	{
	  JokerB->prev = last;
	  last->next=JokerB;
	  first = JokerA->next;
	  last = JokerA;
	  last->next=NULL;
	  first->prev=NULL;
	}
      else if(JokerA->next == NULL)
	{
	  JokerA->next = first;
	  first->prev=JokerA;
	  last=JokerB->prev;
	  first = JokerB;
	  last->next=NULL;
	  first->prev=NULL;
	}
      else
	{
	  tmp = first;
	  first=JokerA->next;
	  first->prev = NULL;
	  JokerA->next = tmp;
	  JokerA->next->prev=JokerA;

	  tmp = last;
	  last = JokerB->prev;
	  last->next = NULL;
	  JokerB->prev = tmp;
	  JokerB->prev->next = JokerB;
	}

    }
}


void SolDeck::countcut(int count)
{
  //  cout << count << endl << DECKSIZE << endl;
  if (count < (DECKSIZE - 1))
    {
      CardPtr iter = first;
      if(iter == JokerA || iter == JokerB)
	{
	  //If we see one Joker then Afirst needs to be switched.
	  //If we see two Jokers it should remain the same.
	  Afirst = !Afirst;
	}
      //start at 1 because iter=first is one.
      for(int i = 1; i < count; ++i)
	{
	  iter = iter->next;
	  if(iter == JokerA || iter == JokerB)
	    {
	      //If we see one Joker then Afirst needs to be switched.
	      //If we see two Jokers it should remain the same.
	      Afirst = !Afirst;
	    }
	}
      //cout << "Cutting after " << iter->value << endl;


      CardPtr tmp;
      tmp = iter->next;
      iter->next = last;
      tmp->prev=NULL;

      first->prev=last->prev;
      first->prev->next=first;

      last->prev=iter;

      first = tmp;
    }

}
int SolDeck::finalcount(int count)
{
  
  CardPtr iter = first;
  if(count == DECKSIZE)
    count = (DECKSIZE - 1);
  for(int i = 0; i < count; ++i)
    {
      iter = iter->next;
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


// bool SolDeck::keyin(const char* key)
// {
//   int count = 0;
//   for(int i = 0; key[i] != '\0'; i++)
//     {
//       count++;
//     }
//   int* keyint;
//   keyint = new int[count];

//   for(int i = 0; i < count; i++)
//     {
//       if(key[i] >= 97 && key[i] <= 122)
// 	{
// 	  keyint[i] = key[i] - 96;
// 	}
//       else if(key[i] >= 65 && key[i] <= 90)
// 	{
// 	  keyint[i] = key[i] - 64;
// 	}
//       else
// 	{
// 	  delete []keyint;
// 	  return false;
// 	}
//     }
//   for(int i = 0; i < count; i++)
//     {
//       jokerswap();
//       jokercut();
//       {
// 	if(last->value == (DECKSIZE - 1) || last->value == DECKSIZE)
// 	  countcut((DECKSIZE - 1));
// 	else 
// 	  countcut(last->value);
//       }
//       countcut(keyint[i]);
//     }
//   delete []keyint;
//   return true;


// }

//remove!
void SolDeck::showdeck()
{
  for(CardPtr iter=first; iter != NULL; iter=iter->next)
    {
      if (iter != first)
	{
	  if (iter->prev->next != iter)
	    {
	      cout << "Error on " << iter->value << endl;
	    }
	}
      if (iter != last)
	{
	  if (iter->next->prev != iter)
	    {
	      cout << "Error on " << iter->value << endl;
	    }
	}
    }
  for(CardPtr iter=first; iter != NULL; iter=iter->next)
    {
      if (iter->prev != NULL)
	{
	  cout << iter->prev->value << ", ";
	}
      else 
	{
	  cout << "N, ";
	}
    }
  cout << endl;
  for(CardPtr iter=first; iter != NULL; iter=iter->next)
    {
      cout << iter->value << ", ";
    }
  cout << endl;
  for(CardPtr iter=first; iter != NULL; iter=iter->next)
    {
      if (iter->next != NULL)
	{
	  cout << iter->next->value << ", ";
	}
      else
	{
	  cout << "N, ";
	}
    }
  cout << "\nfirst:" << first->value
       << "\nlast:" << last->value
       << "\nJokerA:" << JokerA->value
       << "\nJokerB:" << JokerB->value
       << "\nAfirst:" << Afirst;
  cout << endl << endl;
}

int* SolDeck::getcards()
{

  int* temp;
  temp = new int[DECKSIZE];

  int i = 0;

  for(CardPtr iter=first; iter != NULL; iter=iter->next)
    {
      temp[i] = iter->value;
      ++i;
    }

  return temp;
}
