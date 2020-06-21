#include <bits/stdc++.h>
#include "user.h"
using namespace std;

void setUserName(int id, string s) {
	bit b = StringtoBit(s);
	assignBittoBit(id, 0, b, 0, 128);
}

string getUserName(int id) {
	return BittoString(id, 0, 128);
}

void setPassword(int id, string s) {
	bit b = StringtoBit(s);
	assignBittoBit(id, 128, b, 0, 128);
}

string getPassword(int id) {
	return BittoString(id, 128, 128);
}

void setRootFolder(int id, int x) {
	assignInttoBit(id, 256, x, 4);
}

int getRootFolder(int id) {
	return BittoInt(id, 256, 4);
}

int createUser() {
	int id = takeBlock();
	setType(id, 1);

	string s;
	while (true) {
		cout << "\n Enter Username: "; cin >> s;

		bool check = false;
		for (int i=0; i < 1024; ++i) {
			int id = BittoInt(0, i * 4, 4);
			if (s == getUserName(id)) check = true;
		}
		if (check) cout << "\n This Username exists, please enter another Username.";
			else break;
	}

	for (int i = 0; i < 1024; ++i) {
		int x = BittoInt(0, i * 4, 4);
		if (x == 0) {
			assignInttoBit(0, i * 4, id, 4);
			break;
		}
	}

	setUserName(id, s);
	int rf = createFolder(s, id, id);
	setRootFolder(id, rf);

	cout << "\n Enter Password: "; cin >> s;
	setPassword(id, s);
	return id;
}

void deleteUser(int id) {
	deleteFolder(getRootFolder(id));
	freeBlock(id);
}

int login() {
	string s1, s2;
	cout << "\n UserName: "; cin >> s1;
	cout << "\n Password: "; cin >> s2;

	int id = 0;
	for (int i = 0; i < 1024; ++i) {
		id = BittoInt(0, i * 4, 4);
		if (id == 0) break;
		if (s1 == getUserName(id) && s2 == getPassword(id)) break;
		id = 0;
	}
	if (id > 0) {
        cout << "\n Login success!";
        return id;
	}
	cout << "\n No user match, log in again()";
	return login();
}




