#include "FlashMemory.h"

FlashMemory::FlashMemory(int numberOfBlocks, int sizeOfEach) : size(numberOfBlocks * sizeOfEach) {
	for (int i = 0; i < numberOfBlocks; i++) {
		storage.push_back(Block(sizeOfEach, i));
	}
	freeSpace = size;
}

void FlashMemory::sortBlocks() {
	//sort the storage according to number of operation per block
	sort(storage.begin(), storage.end(), [](Block &first, Block &second) {
		if (first.operationCounter == second.operationCounter) {
			return (first.index < second.index);
		}

		return (first.operationCounter < second.operationCounter);
	});
}

bool FlashMemory::Add(string fileName, float sz) {
	if (file.find(fileName) != file.end()) {
		cout << "File exist\n";
		return false;
	}
	else if (freeSpace < sz) {
		cout << "File is too large\n";
		return false;
	}

	float saveSz = sz;
	vector<int> blockIndex;
	int i = 0;
	while (sz > 0) {
		if (!storage[i].isFree) {
			i++;
			continue;
		}

		//set the index of the block in the file
		blockIndex.push_back(storage[i].index);
		//increment the operations on the block
		storage[i].operationCounter++;
		//set the block to be unavailable
		storage[i].isFree = false;
		//set the total free space of the storage
		freeSpace -= storage[0].size;

		sz -= storage[0].size;
		i++;
	}

	//create file in the storage
	file.insert(make_pair(fileName, File(fileName, saveSz, blockIndex)));
	sortBlocks();

	return true;
}

bool FlashMemory::Delete(string fileName) {
	map<string, File>::iterator it = file.find(fileName);
	if (it == file.end()) {
		cout << "File doesn't exist\n";
		return false;
	}

	for (int i = 0; i < (int) it->second.blockIndex.size(); i++) {
		int index = it->second.blockIndex[i];

		for (int j = (int) storage.size() - 1; j >= 0; j--) {
			if (index == storage[j].index) {
				storage[j].isFree = true;
				freeSpace += storage[0].size;
				//storage[j].operationCounter++;
				break;
			}
		}
	}

	file.erase(it);
	//sortBlocks();

	return true;
}

float FlashMemory::calculateAverageOperationNumber() {
	float avg = 0;
	for (int i = 0; i < (int) storage.size(); i++) {
		avg += storage[i].operationCounter;
	}
	return avg / (int) storage.size();
}

FlashMemory::~FlashMemory() {
}

