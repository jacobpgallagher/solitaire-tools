#include<fstream>
#include<iostream>
#include<cstring>
#include<string>
#include<cmath>
#include<cstdlib>
#include "addmod.h"
#include "solitaire.h"

using namespace std;

const int interval = 100000;


struct Node
{
  int* deck;
  string key;
  Node* next;
};

void keyadvance(string& key);



int main(int argc, char **argv)
{

  int length = 0;

  if(argc > 1)
    {
      length = atoi(argv[1]);
    }


  if(length == 0)
    {
      cout << "how long?\n";
      cin >> length;
    }
 string key = "A";
      

  SolDeck *temp;


  Node* head;
  
  head = new Node;
  head->next = NULL;

  Node* current = head;

  bool match;

  while(key.length() <= length)
    {

      temp = new SolDeck(key.c_str());

      current->deck = temp->getcards();
      current->key = key;

      for(Node* iter=head; iter != NULL; iter=iter->next)
	{
	  match = true;
	  for(int i = 0; i < DECKSIZE; ++i)
	    {
	      if(!(iter->deck[i] == current->deck[i]) || iter->key == current->key)
		{
		  match = false;
		  break;
		}
	    }

	  if(match)
	    {
	      cout << iter->key << " and " << current->key << endl;
	    }
	}
      current->next = new Node;
      current = current->next;
      current->next = NULL;
    
      ////////////////////
      keyadvance(key);

    }
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

