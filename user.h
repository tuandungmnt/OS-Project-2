#ifndef user_h
#define user_h

#include "sup.h"
#include "data.h"
#include "file.h"
#include "folder.h"
#include <bits/stdc++.h>
using namespace std;

void setUserName(int id, string s);
string getUserName(int id);
void setPassword(int id, string s);
string getPassword(int id);
void setRootFolder(int id, int x);
int getRootFolder(int id);
int createUser();
void deleteUser(int id);
int login();

#endif 