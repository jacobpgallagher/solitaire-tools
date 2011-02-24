#ifndef SOLATAIRE_H
#define SOLATAIRE_H
#include<cstdlib>
#include<vector>

//remove later!
#include<iostr2eam>

const int DECKSIZE=54;

using namespace std;

struct Card
{
  int value;
  Card *link;
};

typedef Card* CardPtr;

class SolDeck
{
 public:
  SolDeck();
  SolDeck(int a[]);
  SolDeck(const char* a);
  SolDeck(vector<int> a);
  ~SolDeck();
  vector<int> getdeck(int num);
  bool keyin(const char* key);

 private:
  int step();
  void jokerswap();
  void jokercut();
  void countcut(int count);
  int finalcount(int count);
  CardPtr first;
  CardPtr last;
  CardPtr JokerA, JokerB, PrevA, PrevB;
  bool Afirst;
  vector<int> pad;

 public:
  //Delete later
  void showdeck();

  int* getcards();
};

void swap(CardPtr first, CardPtr a, CardPtr b);

#endif
