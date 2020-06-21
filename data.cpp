#include <bits/stdc++.h>
#include "data.h"
using namespace std;

int takeBlock() {
	int id = BittoInt(1, 0, 4);
	if (id == 0) {
		return 0;
	}
	assignBittoBit(1, 0, Block(id), 0, 4096);
	setBlock(id);
	return id;
}

void freeBlock(int id) {
	setBlock(id);
	assignBittoBit(id, 0, Block(1), 0, 4096);
	assignBittoBit(1, 0, InttoBit(id, 4), 0, 4096);
}

void printBlockHex(int id) {
	int tmp = 0;
	bit b = Block(id);
	for (int i = 0; i < 32768; ++i) {
		tmp = tmp * 2 + b[i];
		if (i % 8 == 7) {
			cout << hex << tmp << " ";
			tmp = 0;
		}
	}
	cout << endl;
}

void printBlockBit(int id) {
	bit b = Block(id);

	for (int i = 0; i < 32768; ++i) {
		cout << b[i];
		if (i % 8 == 7) cout << " ";
	}
	cout << endl;
}

void printBlockString(int id) {
	string s = BittoString(id, 0, 4096);
	cout << s << endl;
}

void setType(int id, int type) {
	assignInttoBit(id, 4092, type, 4);
} 

int getType(int id) {
	return BittoInt(id, 4092, 4);
}