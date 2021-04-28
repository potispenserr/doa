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
	int tableSize = 15000;

public:

	HopScotchProbe() {
		for (int i = 0; i < tableSize; i++) {
			hashTable.push_back(hashNode(NULL, "", -1));
		}
	}

	void insert(int inKey, std::string inValue) {
		int hash = hashkey(inKey) % tableSize;
		int linearCounter = 1;
		int startHash = hash;

		// check if empty, add
		if (hashTable[hash].key == NULL)
		{
			hashTable[hash].key = inKey;
			hashTable[hash].value = inValue;
			hashTable[hash].originalSpot = startHash;
			hashTable[hash].hopSlot[0] = 1; // inserted in first slot from startHash

			std::cout << "Insertion succeeded!\n Hash element: " << hashTable[hash].key << " | " << hashTable[hash].value << std::endl;
		}

		// else, linearprobe until empti slått
		else {
			hash = hashkey(inKey + linearCounter) % tableSize;
			while (hashTable[hash].key != NULL && hash != startHash) {
				linearCounter++;
				hash = hashkey(inKey + linearCounter) % tableSize;
			}
			if (hash == startHash) {
				std::cout << "hash table is full.\n";
				return;
			}

			// found empty slot
			int emptySlot = hash;
			while (emptySlot - startHash >= hopLimit) {
				for (int i = 1; i < hopLimit; i++) {
					if (emptySlot - hashTable[hash - (hopLimit - i)].originalSpot < hopLimit) {
						hashTable[emptySlot].key = hashTable[hash - (hopLimit - i)].key;
						hashTable[emptySlot].value = hashTable[hash - (hopLimit - i)].value;
						hashTable[emptySlot].originalSpot = hashTable[hash - (hopLimit - i)].originalSpot;

						hashTable[hash - (hopLimit - i)].key = NULL;
						hashTable[hash - (hopLimit - i)].value = "";
						hashTable[hash - (hopLimit - i)].originalSpot = NULL;

						emptySlot = hash - (hopLimit - i);
						break; // check next square of 4 slots
					}
					else if (i == hopLimit - 1) {
						std::cout << "Insörkön fejld.\n";
						return; // :( allt var förgäves
					}
				}
			}

			// emptySlot - startHash < hopLimit :D
			hashTable[emptySlot].key = inKey;
			hashTable[emptySlot].value = inValue;
			hashTable[emptySlot].originalSpot = startHash;

			std::cout << "Insertion succeeded!\n Hash element: " << hashTable[emptySlot].key << " | " << hashTable[emptySlot].value << std::endl;
		}

		// if linear fails, attempt to throw out occupied slot and add

		// check if a slot is empty outside of hopLimit
		
		/*linearCounter = 0;
		hash = hashkey(inKey + hopLimit) % tableSize;
		for (int i = 0; i < hopLimit; i++) {
			if (hashTable[hash].key == NULL) {
				// there's space to throw out a key! :D

			}
			linearCounter++;
			hash = hashkey(inKey + hopLimit + linearCounter) % tableSize;
		}*/


		
	}

	void printDatabase() {
		std::cout << "arrayIndex \t hashIndex \t key \t value \n";
		for (int i = 0; i < hashTable.size(); i++) {
			std::cout << i << " \t \t " << hashTable[i].hashIndex << " \t \t " << hashTable[i].key << "\t " << hashTable[i].value << "\n";
			std::cout << "---------------------------------------------------------------------------" << "\n";

		}
	}

	int hashkey(int key) {
		return key % (tableSize + 2000);
	}
};



int main()
{
	HopScotchProbe hop = HopScotchProbe();

	std::string strinput;
	srand(time(0));
	int intinput;
	while (true) {
		std::cout << "1. Insert  \n2. Print database \n3. Benchmark hopscotch hashing max random load\n";
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
		// will fail since load factor is 0.99, and hopscotch is not made for that shit
		if (strinput == "3") {
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


		}


	}
}