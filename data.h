#ifndef data_h
#define data_h

#include "sup.h"
#include <bits/stdc++.h>
using namespace std;

int takeBlock();
void freeBlock(int id);
void printBlockHex(int id);
void printBlockBit(int id);
void printBlockString(int id);
void setType(int id, int type);
int getType(int id);

#endif 