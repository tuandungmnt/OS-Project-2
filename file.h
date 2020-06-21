#ifndef file_h
#define file_h

#include "sup.h"
#include "data.h"
#include <bits/stdc++.h>
using namespace std;

void setFileName(int id, string s);
string getFileName(int id);
void setFileOwner(int id, int owner);
int getFileOnwer(int id);
void setFileParentFolder(int id,int pid);
int getFileParentFolder(int id);
void setFileSize(int id, int size);
int getFileSize(int id);
void setDirectBlock(int id, int i, int x);
int getDirectBlock(int id, int i);
void setSingleIndirectBlock(int id, int x);
int getSingleIndirectBlock(int id);
void setDoubleIndirectBlock(int id, int x);
int getDoubleIndirectBlock(int id);
int findDataBlock(int id, int i);
int createFile(string name, int owner, int parent, int size);
void pasteFile(int id, int idx);
void deleteFile(int id);

#endif 