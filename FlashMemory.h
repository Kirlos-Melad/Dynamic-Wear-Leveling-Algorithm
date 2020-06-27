#ifndef FLASHMEMORY_H_
#define FLASHMEMORY_H_

#include <bits/stdc++.h>

using namespace std;

struct Block{
	int size, index;
	int operationCounter;
	bool isFree;
	Block(int size, int index) : size(size), index(index), operationCounter(0), isFree(true){
	}
};

struct File{
	string fileName;
	float size;
	vector<int>const blockIndex;
	File(string fileName, float size, vector<int> blockIndex) : fileName(fileName), size(size), blockIndex(blockIndex){
	}
};

class FlashMemory {
	vector<Block> storage;
	map<string, File> file;
	int const size;
	float freeSpace;
	void sortBlocks();
public:
	FlashMemory(int numberOfBlocks, int sizeOfEach);
	bool Add(string fileName, float size);
	bool Delete(string fileName);
	float calculateAverageOperationNumber();
	~FlashMemory();
};

#endif /* FLASHMEMORY_H_ */
