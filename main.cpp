#include <bits/stdc++.h>
#include "FlashMemory.h"

using namespace std;

int main() {
	//create a flash memory with 20 blocks of 2kb size each
	FlashMemory flashMemory(20, 2);
	int testCases, opNum;
	string operation;

	cout << "Enter number of test cases: ";
	cin >> testCases;
	for (int j = 0; j < testCases; j++) {
		cout << "Enter number of operations: ";
		cin >> opNum;
		for (int i = 0; i < opNum; i++) {
			cout << "Enter [Add] or [Delete] to add or delete file respectively: ";
			cin >> operation;
			if (operation == "Add") {
				string name;
				float size;

				cout << "Please, enter file name: ";
				cin >> name;

				cout << "Please, enter file size: ";
				cin >> size;

				if (flashMemory.Add(name, size)) {
					cout << "File added successfully\n";
				}
				else {
					cout << "Failed to add the file\n";
				}
			}
			else if (operation == "Delete") {
				string name;

				cout << "Please, enter file name: ";
				cin >> name;

				if (flashMemory.Delete(name)) {
					cout << "File removed successfully\n";
				}
				else {
					cout << "Failed to remove the file\n";
				}
			}
		}
		cout << "The average number of write operations per block: " << flashMemory.calculateAverageOperationNumber();
	}

	return 0;
}
