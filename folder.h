#ifndef folder_h
#define folder_h

#include "sup.h"
#include "data.h"
#include "file.h"
#include <bits/stdc++.h>
using namespace std;

void setFolderName(int id, string s);
string getFolderName(int id);
void setFolderOwner(int id, int owner);
int getFolderOwner(int id);
void setFolderParentFolder(int id,int pid);
int getFolderParentFolder(int id);
void setFolderList(int id, int i, int id1);
int getFolderList(int id, int i);
void setFileList(int id, int i, int id1);
int getFileList(int id, int i);
int checkFolderName(int id, string s);
int checkFileName(int id, string s);
void addFolderList(int id, int idx);
void removeFolderList(int id,int idx);
void addFileList(int id, int idx);
void removeFileList(int id,int idx);
int createFolder(string name, int owner, int parent);
void deleteFolder(int id);
void writeList(int id);
void pasteFolder(int id, int idx);

#endif 