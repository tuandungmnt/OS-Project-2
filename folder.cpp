#include <bits/stdc++.h>
#include "folder.h"
using namespace std;

void setFolderName(int id, string s) {
	bit b = StringtoBit(s);
	assignBittoBit(id, 0, b, 0, 128);
}

string getFolderName(int id) {
	return BittoString(id, 0, 128);
}

void setFolderOwner(int id, int owner) {
	assignInttoBit(id, 128, owner, 4);
}

int getFolderOwner(int id) {
	return BittoInt(id, 128, 4);
}

void setFolderParentFolder(int id,int pid) {
	assignInttoBit(id, 132, pid, 4);
} 

int getFolderParentFolder(int id) {
	return BittoInt(id, 132, 4);
}

void setFolderList(int id, int i, int id1) {
	assignInttoBit(id, 136 + i * 4, id1, 4);
}

int getFolderList(int id, int i) {
	return BittoInt(id, 136 + i * 4, 4);
}

void setFileList(int id, int i, int id1) {
	assignInttoBit(id, 648 + i * 4, id1, 4);
}

int getFileList(int id, int i) {
	return BittoInt(id, 648 + i * 4, 4);
}

int checkFolderName(int id, string s) {
	for (int i = 0; i < 512; ++i) {
		int k = getFolderList(id, i);
		if (k == 0) break;
		if (getFolderName(k) == s) return k;
	}
	return 0;
}

int checkFileName(int id, string s) {
	for (int i = 0; i < 512; ++i) {
		int k = getFileList(id, i);
		if (k == 0) break;
		if (getFileName(k) == s) return k;
	}
	return 0;
}

void addFolderList(int id, int idx) {
	for (int i = 0; i < 512; ++i) {
		int k = getFolderList(id, i);
		if (k == 0) {
			setFolderList(id, i, idx);
			return;
		}
	}
}

void removeFolderList(int id,int idx) {
	bool s = false;
	for (int i = 0; i < 512; ++i) {
		int k = getFolderList(id, i);
		if (k == 0) break;

		if (k == idx) s = true;
		if (s) setFolderList(id, i, getFolderList(id, i + 1));
	}	
}

void addFileList(int id, int idx) {
	for (int i = 0; i < 512; ++i) {
		int k = getFileList(id, i);
		if (k == 0) {
			setFileList(id, i, idx);
			return;
		}
	}
}

void removeFileList(int id,int idx) {
	bool s = false;
	for (int i = 0; i < 512; ++i) {
		int k = getFileList(id, i);
		if (k == 0) break;
		
		if (k == idx) s = true;
		if (s) setFileList(id, i, getFileList(id, i + 1));
	}	
}

int createFolder(string name, int o, int parent) {
	if (parent != 0) {
		int x = checkFolderName(parent, name);
		if (x != 0) {
			cout << "\n FolderName already exist.";
			return 0;
		}
	}

	int id = takeBlock();
	setType(id, 2);
	setFolderName(id, name);
	setFolderParentFolder(id, parent);
	setFolderOwner(id, o);
	//cout << "-- " << name << " " << o << " " << parent << endl;
	//cout << id << " " << getFolderName(id) << " " << getFolderOwner(id) << " " << getFolderParentFolder(id) << endl;

	if (parent != 0) addFolderList(parent, id);

	return id;
} 

void deleteFolder(int id) {
	for (int i = 0; i < 512; ++i) {
		int k = getFolderList(id, i);
		if (k == 0) break;
		deleteFolder(k);
	}
	for (int i = 0; i < 512; ++i) {
		int k = getFileList(id, i);
		if (k == 0) break;
		deleteFile(k);
	}

	freeBlock(id);
}

void writeList(int id) {
	cout << "\n Folder: ";
	for (int i = 0; i < 512; ++i) {
		int k = getFolderList(id, i);
		if (k == 0) break;
		cout << getFolderName(k) << " ";
	}
	cout << "\n File: ";
	for (int i = 0; i < 512; ++i) {
		int k = getFileList(id, i);
		if (k == 0) break;
		cout << getFileName(k) << " ";
	}
	cout << endl;
}

void pasteFolder(int id, int idx) {
	for (int i = 0; i < 512; ++i) {
		int k = getFolderList(id, i);
		if (k == 0) break;
		int z = createFolder(getFolderName(k), getFolderOwner(idx), idx);
		pasteFolder(k, z);
	}
	for (int i = 0; i < 512; ++i) {
		int k = getFileList(id, i);
		if (k == 0) break;
		int z = createFile(getFileName(k), getFolderOwner(idx), idx, getFileSize(k));
		addFileList(idx, z);
		pasteFile(k, z);
	}
}

