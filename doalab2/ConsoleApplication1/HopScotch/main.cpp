#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>



class hashNode {
public:
	int key;
	std::string value;
	int originalSpot;
	int hashIndex;
	int hopSlot[4] = { 0, 0, 0, 0 };



	hashNode(int keyInit, std::string valueInit, int hashIndexInit) {
		key = keyInit;
		value = valueInit;
		hashIndex = hashIndexInit;
	}

};

class HopScotchProbe {
private:
	std::vector<hashNode> hashTable;
	int hopLimit = 4;
	int tableSize = 10000;

public:

	HopScotchProbe() {
		for (int i = 0; i < tableSize; i++) {
			hashTable.push_back(hashNode(NULL, "", -1));
		}
	}

	void insert(int inKey, std::string inValue) {
		int hash = hashkey(inKey) % tableSize;
		int linearCounter = 1;
		int startHash = hashkey(inKey) % tableSize;

		// check if empty, add
		if (hashTable[hash].key == NULL)
		{
			hashTable[hash].key = inKey;
			hashTable[hash].value = inValue;
			hashTable[hash].originalSpot = startHash;
			hashTable[hash].hopSlot[0] = 1; // inserted in first slot from startHash
		}

		// else, linearprobe until hopLimit
		else {
			hash = hashkey(inKey + linearCounter) % tableSize;
			for (int i = 0; i < hopLimit; i++) {
				if (hashTable[hash].key == NULL) {
					hashTable[hash].key = inKey;
					hashTable[hash].value = inValue;
					hashTable[hash].hopSlot[linearCounter - 1] = 1; // -1 since linearCounter starts at 1
					return;
				}
				linearCounter++;
				hash = hashkey(inKey + linearCounter) % tableSize;
			}
		}

		// if linear fails, attempt to throw out occupied slot and add

		// check if a slot is empty outside of hopLimit
		
		linearCounter = 0;
		hash = hashkey(inKey + hopLimit) % tableSize;
		for (int i = 0; i < hopLimit; i++) {
			if (hashTable[hash].key == NULL) {
				// there's space to throw out a key! :D

			}
			linearCounter++;
			hash = hashkey(inKey + hopLimit + linearCounter) % tableSize;
		}







		//there's no more to do here. Go home. 
		std::cout << "Insert failed.\n";
	}

	void printDatabase() {
		std::cout << "arrayIndex \t hashIndex \t key \t value \n";
		for (int i = 0; i < hashTable.size(); i++) {
			std::cout << i << " \t \t " << hashTable[i].hashIndex << " \t \t " << hashTable[i].key << "\t " << hashTable[i].value << "\n";
			std::cout << "---------------------------------------------------------------------------" << "\n";

		}
	}
};

int hashkey(int key) {
	return key % 12000;
}

int main()
{
	HopScotchProbe hop = HopScotchProbe();

	std::string strinput;
	srand(time(0));
	int intinput;
	while (true) {
		std::cout << "1. Insert  \n2. Print database \n3. Benchmark LinearProbe max random load\n";
		std::getline(std::cin, strinput);
		if (strinput == "1") {
			std::cout << "Input key:";
			std::cin >> intinput;
			std::cout << "Input value: ";
			std::cin.ignore();
			std::getline(std::cin, strinput);
			hop.insert(intinput, strinput);

		}
		if (strinput == "2") {
			hop.printDatabase();

		}
		/*if (strinput == "4") {
			for (int i = 0; i < 9999; i++) {
				if (i == 0) {
					hop.insert((rand()), "fun times");
				}
				else {
					hop.insert(i, "fun times");
				}

			}

			auto start = std::chrono::high_resolution_clock::now();
			hop.insert(rand(), "not so fun times");
			auto finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << "Elapsed add max load factor: " << elapsed.count() << "s\n";


		}*/


	}
}