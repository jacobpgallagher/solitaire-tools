#ifndef NFRONT_H
#define NFRONT_H
#include<ncurses.h>
#include<cstring>
#include<string>
#include "addmod.h"
#include "solitaire.h"



using namespace std;

string keystring(int* a, int position);

int* enterOwn();

int format(int a);

int row(int index);

int col(int index);

string center(string title, int width);

void nfront(SolDeck thedeck);

SolDeck* nkey();

SolDeck* keyphrasemaker();


#endif
