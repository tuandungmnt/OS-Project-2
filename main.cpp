#include <bits/stdc++.h>
#include "user.h"
using namespace std;

int pws; 
int copyfolder, copyfile;
// Các khối dữ liệu có kích thước 4KB = 2^15bit
// Bộ nhớ có kích thước 128MB tương đương 2^15 khối dữ liệu
// Các biến được khai báo cục bộ là các thành phần chạy trong bộ nhớ chính	

void level3(string link, int file) {
	while (true) {
		cout << "\n " << link << ": ";
		string s;
		cin >> s;

		if (s == "close") {
			return;
		}

		if (s == "setsize") {
			int x;
			cin >> x;
			if (getFileSize(file) != 0) {
				cout << "\n FileSize already set \n";
				continue;
			} 
			setFileSize(file, x);
			continue;
		}

		if (s == "getsize") {
			cout << "\n " << getFileSize(file) << "\n";
			continue;
		}

		if (s == "setblock") {
			int i;
			string s1;
			cin >> i;
			cin >> s1;

			int id = findDataBlock(file, i);
			if (id == 0) continue;

			bit b = StringtoBit(s1);
			assignBittoBit(id, 0, b, 0,4096);
			continue;
		}

		if (s == "getblock") {
			int i;
			cin >> i;

			int id = findDataBlock(file, i);
			if (id == 0) continue;

			cout << "\n "; 
			printBlockString(id);
			continue;
		}

		if (s == "getblockhex") {
			int i;
			cin >> i;

			int id = findDataBlock(file, i);
			if (id == 0) continue;

			cout << "\n ";
			printBlockHex(id);
			continue;
		}		

		if (s == "getblockbit") {
			int i;
			cin >> i;

			int id = findDataBlock(file, i);
			if (id == 0) continue;

			cout << "\n ";
			printBlockBit(id);
			continue;
		}

		if (s == "freeblocklist") {
			int i;
			cin >> i;
			int x = 1;
			cout << "\n ";
			while (i--) {
				x = BittoInt(x, 0, 4);
				cout << x << " ";
			}
			cout << "\n";
			continue;
		}
		cout << "\n No match command";
	}
}

void level2(string link, int folder) {
	while (true) {
		cout << "\n " << link << ": "; 
		string s;
		cin >> s;
		if (s == "writelist") {
			writeList(folder);
			continue;
		}

		if (s == "close") {
			return;
		}

		if (s == "open") {
			string s1;
			cin >> s1;

			int id = checkFolderName(folder, s1);
			if (id == 0) {
				cout << "\n Folder doesn't exist\n";
				continue;
			}
			level2(link+s1+"/",id);
			continue;
		}

		if (s == "copy") {
			string s1;
			cin >> s1;

			int id = checkFolderName(folder, s1);
			if (id == 0) {
				cout << "\n Folder doesn't exist\n";
				continue;
			}
			copyfolder = id;
			continue;
		}

		if (s == "paste") {
			if (copyfolder == 0) {
				cout << "\n Nothing copying \n";
				continue;
			}
			int x = folder;
			bool check = false;
			while (getType(x) == 2) {
				if (x == copyfile) {
					check = true;
					break;
				}
				x = getFolderParentFolder(x);
			}
			if (check) {
				cout << "\n Can't copy folder to its subfolder. \n";
				continue;
			}
			int z = createFolder(getFolderName(copyfolder), getFolderOwner(folder), folder);
			pasteFolder(copyfolder, z);
			continue;
		}

		if (s == "create") {
			string s1;
			cin >> s1;

			createFolder(s1, getFolderOwner(folder), folder);
			continue;
		}

		if (s == "delete") {
			string s1;
			cin >> s1;

			int id = checkFolderName(folder, s1);
			if (id == 0) {
				cout << "\n Folder doesn't exist \n";
				continue;
			}

			removeFolderList(folder, id);
			deleteFolder(id);
			continue;
		}

		if (s == "rename") {
			string s1, s2;
			cin >> s1;
			cin >> s2;

			int id = checkFolderName(folder, s1);
			if (id == 0) {
				cout << "\n Folder doesn't exist. \n";
				continue;
			}

			int idx = checkFolderName(folder, s2);
			if (idx != 0) {
				cout << "\n New Foldername already exist \n";
				continue;
			}

			setFolderName(id, s2);
			continue;
		}

		if (s == "openf") {
			string s1;
			cin >> s1;

			int id = checkFileName(folder, s1);
			if (id == 0) {
				cout << "\n File doesn't exist \n";
				continue;
			}
			level3(link+s1+"/",id);
			continue;
		}

		if (s == "copyf") {
			string s1;
			cin >> s1;

			int id = checkFileName(folder, s1);
			if (id == 0) {
				cout << "\n File doesn't exist \n";
				continue;
			}
			copyfile = id;
			continue;
		}

		if (s == "pastef") {
			if (copyfile == 0) {
				cout << "\n Nothing copying \n";
				continue;
			}

			int id = checkFileName(folder, getFileName(copyfile));
			if (id != 0) {
				cout << "\n This Filenam already exist. \n";
				continue;
			}
			int z = createFile(getFileName(copyfile), getFolderOwner(folder), folder, getFileSize(copyfile));
			if (id != 0) addFileList(folder, id);
			pasteFile(copyfile, z);
			continue;
		}

		if (s == "createf") {
			string s1;
			cin >> s1;

			int id = checkFileName(folder, s1);
			if (id != 0) {
				cout << "\n This Filenam already exist. \n";
				continue;
			}
			id = createFile(s1, getFolderOwner(folder), folder, 0);
			if (id != 0) addFileList(folder, id);

			continue;
		}

		if (s == "deletef") {
			string s1;
			cin >> s1;

			int id = checkFileName(folder, s1);
			if (id == 0) {
				cout << "\n File doesn't exist \n";
				continue;
			}

			removeFileList(folder, id);
			deleteFile(id);
			continue;
		}

		if (s == "renamef") {
			string s1, s2;
			cin >> s1;
			cin >> s2;

			int id = checkFileName(folder, s1);
			if (id == 0) {
				cout << "\n File doesn't exist \n";
				continue;
			}

			int idx = checkFileName(folder, s2);
			if (idx != 0) {
				cout << "\n New Filename already exist \n";
				continue;
			}

			setFileName(id, s2);
			continue;
		}

		if (s == "freeblocklist") {
			int i;
			cin >> i;
			int x = 1;
			cout << "\n ";
			while (i--) {
				x = BittoInt(x, 0, 4);
				cout << x << " ";
			}
			cout << "\n";
			continue;
		}

		cout << "\n No match command";
	}
}

void level1(int user) {
	while (true) {
		cout << "\n publicws or privatews: ";
		string s;
		cin >> s;
		if (s == "logout") {
			copyfolder = copyfile = 0;
			return;
		}
		if (s == "publicws") {
			level2("PublicWorkspace/",pws);
			continue;	
		}
		if (s == "privatews") {
			level2("PrivateWorkspace/",getRootFolder(user));
			continue;
		}
	}
}	

void level0() {
	while (true) {
		cout << "\n createUser or login: ";
		string s;
		cin >> s;
		if (s == "login") {
			level1(login());
			continue;
		}
		
		if (s == "createUser") {
			level1(createUser());
			continue;
		}
	
		if (s == "exit") return;
	}
}

int main() { 
	setBlock(0);
	for (int i = 1; i < 32768; ++i) { 
		setBlock(i);
		assignInttoBit(i, 0, (i+1)%32768, 4);
	}

	pws = createFolder("publicws",0,0);	

	level0();
}
