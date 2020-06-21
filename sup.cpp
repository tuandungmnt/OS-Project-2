#include <bits/stdc++.h>
#include "sup.h"
using namespace std;

bit block[32768];

bit Block(int id) {
	return block[id];
}

void setBlock(int id) {
	for (int i = 0; i < 4096; ++i) block[id][i] = 0;
}

int BittoInt(int id, int x, int l) {
	int tmp = 0;
	bit b = Block(id);
	for (int i = 0; i < l * 8; ++i) 
		tmp = tmp * 2 + b[x*8 + i]; 
	return tmp;
} 

string BittoString(int id, int x, int l) {
	string s = "";
	bit b = Block(id);
	x *= 8;
	while (l--) {
		int tmp = 0;
		for (int i = 0; i < 8; ++i) 
			tmp = tmp * 2 + b[x + i];
		if (tmp == 0) break;
		s = s + char(tmp);
		x += 8; 
	}
	return s;
}

bit StringtoBit(string s) {
	//cout << s << endl;
	bit b;
	for (int i = 0; i < s.size(); ++i) {
		int x = int(s[i]);
		for (int j = i * 8 + 7; j >= i * 8; --j) {
			b[j] = x % 2;
			x = x / 2;
		}
	}
	return b;
}

bit InttoBit(int x, int l) {
	bit b;
	for (int i = l * 8 - 1; i >= 0; --i) { 
		b[i] = x % 2;
		x = x / 2;
	}
	return b;
}

void assignBittoBit(int id1, int x1, bit b, int x2, int l) {
	for (int i = 0; i < l * 8; ++i) {
		block[id1][x1*8 + i] = b[x2*8 + i];
		//cout << x1*8 + i << " " << b[x2*8 + i] << endl;
	}
}

void assignInttoBit(int id, int x, int val, int l) {
	bit b = InttoBit(val, l);
	assignBittoBit(id, x, b, 0, l);
}