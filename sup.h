#ifndef sup_h
#define sup_h

#include <bits/stdc++.h>
using namespace std;
typedef bitset<32768> bit;

bit Block(int id);
void setBlock(int id);
int BittoInt(int id, int x, int l);
string BittoString(int id, int x, int l);
bit StringtoBit(string s);
bit InttoBit(int x, int l);
void assignBittoBit(int id1, int x1, bit id2, int x2, int l);
void assignInttoBit(int id, int x, int val, int l);

#endif 
