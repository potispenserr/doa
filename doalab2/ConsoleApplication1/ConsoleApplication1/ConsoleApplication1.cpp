// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
class hashNode {
public:
	int key;
	std::string value;
	int hashIndex;

	hashNode(int keyInit, std::string valueInit, int hashIndexInit) {
		key = keyInit;
		value = valueInit;
		hashIndex = hashIndexInit;

	}

};

class LinearProb {
private:
	std::vector<hashNode> hashTable;
	int hashfunction;

public:


	LinearProb(int hashfunctionInit) {
		for (int i = 0; i < 10000; i++) {
			hashTable.push_back(hashNode(NULL, "", -1));
			//hashTable.push_back(hashNode(i, "plenty of hash" + i));
			hashfunction = hashfunctionInit;
		}

	}
	void insert(int inKey, std::string inValue) {
		int hash = hashkey(inKey) % hashTable.size();
		int starthash = hash;
		int counter = 1;
		if (hashTable[hash].key == NULL || hashTable[hash].key == -1) {
			hashTable[hash].key = inKey;
			hashTable[hash].value = inValue;
			hashTable[hash].hashIndex = starthash;
		}
		else {
			
			hash = (hashkey(inKey) + counter) % hashTable.size();
			while (hash != starthash) {
				if (hashTable[hash].key == NULL || hashTable[hash].key == -1) {

					hashTable[hash].key = inKey;
					hashTable[hash].value = inValue;
					hashTable[hash].hashIndex = starthash;
					break;
				}
				counter++;
				hash = (hashkey(inKey) + counter) % hashTable.size();


			}
		}
		


		
		

	}
	void printDatabase() {
		std::cout << "arrayIndex \t hashIndex \t key \t value \n";
		for (int i = 0; i < hashTable.size(); i++) {
			std::cout << i << " \t \t " << hashTable[i].hashIndex << " \t \t " << hashTable[i].key << "\t " << hashTable[i].value << "\n";
			std::cout << "---------------------------------------------------------------------------" << "\n";

		}
	}
	void changeHash(int newHash) {
		hashfunction = newHash;
	}

	int hashkey(int key) {
		return key % hashfunction;
	}
	

};

int main()
{
	LinearProb lin(12000);
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
			lin.insert(intinput, strinput);

		}
		if (strinput == "2") {
			lin.printDatabase();

		}
		if (strinput == "4") {
			for (int i = 0; i < 9999; i++) {
				if (i == 0) {
					lin.insert((rand()), "fun times");
				}
				else {
					lin.insert(i, "fun times");
				}
				
			}

			auto start = std::chrono::high_resolution_clock::now();
			lin.insert(rand(), "not so fun times");
			auto finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << "Elapsed add max load factor: " << elapsed.count() << "s\n";
			

		}


	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
