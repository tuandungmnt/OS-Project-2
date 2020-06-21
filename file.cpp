#include <bits/stdc++.h>
#include "file.h"
using namespace std;

void setFileName(int id, string s) {
	bit b = StringtoBit(s);
	assignBittoBit(id, 0, b, 0, 128);
}

string getFileName(int id) {
	return BittoString(id, 0, 128);
}

void setFileOwner(int id, int owner) {
	assignInttoBit(id, 128, owner, 4);
}

int getFileOnwer(int id) {
	return BittoInt(id, 128, 4);
}

void setFileParentFolder(int id,int pid) {
	assignInttoBit(id, 132, pid, 4);
} 

int getFileParentFolder(int id) {
	return BittoInt(id, 132, 4);
}

void setFileSize(int id, int size) {
	assignInttoBit(id, 136, size, 4);
}

int getFileSize(int id) {
	return BittoInt(id, 136, 4);
}

void setDirectBlock(int id, int i, int x) {
	assignInttoBit(id, 140 + i * 4, x, 4);
}

int getDirectBlock(int id, int i) {
	return BittoInt(id, 140 + i * 4, 4);
} 

void setSingleIndirectBlock(int id, int x) {
	assignInttoBit(id, 188, x, 4);
} 

int getSingleIndirectBlock(int id) {
	return BittoInt(id, 188, 4);
}

void setDoubleIndirectBlock(int id, int x) {
	assignInttoBit(id, 192, x, 4);
} 

int getDoubleIndirectBlock(int id) {
	return BittoInt(id, 192, 4);
}

int findDataBlock(int id, int i) {
	if (i >= getFileSize(id)) {
		cout << "\n Can't access block bigger than size. ";
		return 0;
	}

	if (i < 12) {
		int k = getDirectBlock(id, i);
		if (k == 0) {
			k = takeBlock();
			setDirectBlock(id, i, k);
		} 
		return k;
	}

	i -= 12;
	if (i < 1024) {
		int k = getSingleIndirectBlock(id);
		if (k == 0) {
			k = takeBlock();
			setSingleIndirectBlock(id, k);
		}

		int kk = BittoInt(k, i * 4, 4);
		if (kk == 0) {
			kk = takeBlock();
			assignInttoBit(k, i * 4, kk, 4);
		}
		return kk;
	}

	i -= 1024;
	int k = getDoubleIndirectBlock(id);
	if (k == 0) {
		k = takeBlock();
		setDoubleIndirectBlock(id, k);
	}

	int kk = BittoInt(k, (i / 1024) * 4, 4);
	if (kk == 0) {			
		kk = takeBlock();
		assignInttoBit(k, (i / 1024) * 4, kk, 4);
	}	

	int kkk = BittoInt(kk, (i % 1024) * 4, 4);
	if (kkk == 0) {
			kkk = takeBlock();
			assignInttoBit(k, (i % 1024) * 4, kkk, 4);
		}
	return kkk;
}

int createFile(string name, int owner, int parent, int size) {
	int id = takeBlock();
	setType(id, 3);

	setFileName(id, name);
	setFileOwner(id, owner);
	setFileParentFolder(id, parent);
	setFileSize(id, size);

	return  id;
}

void pasteFile(int id, int idx) {
	int size = getFileSize(id);
	for (int i = 0; i < size; ++i) {
		int x = findDataBlock(id, i);
		int y = findDataBlock(idx, i);
		assignBittoBit(y, 0, Block(x), 0, 4096);
	}
}

void deleteFile(int id) {
	for (int i = 0; i < 12; ++i) {
		int x = getDirectBlock(id, i);
		if (x != 0) freeBlock(x);
	}

	int x = getSingleIndirectBlock(id);
	if (x != 0) {
		for (int i = 0; i < 1024; ++i) {
			int y = BittoInt(x, i * 4, 4);
			if (y != 0) freeBlock(y); 
		}
		freeBlock(x);
	}

	x = getDoubleIndirectBlock(id);
	if (x != 0) {
		for (int i = 0; i < 1024; ++i) {
			int y = BittoInt(x, i * 4, 4);
			if (y != 0) {
				for (int j = 0; j < 1024; ++j) {
					int z = BittoInt(y, j * 4, 4);
					if (z != 0) freeBlock(z);
				}
				freeBlock(y);
			}
		}
		freeBlock(x);
	}

	freeBlock(id);
}




