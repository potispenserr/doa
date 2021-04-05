// doalab1 part 2 palindrome.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <chrono>

using namespace std;

void ispalindromestack(stack<char> s, string &str) {
	int i;
	string reversed;
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	reversed = str;
	// push into stack
	for (i = 0; i < reversed.size()/2; i++) {
		s.push(reversed[i]);
	}
	// pop from stack
	/*for (i = 0; i < reversed.size(); i++) {
		reversed[i] = s.top();
		s.pop();
	}*/
	//check if both are the same
	if (reversed == str) {
		cout << "That is a palindrome";
	}
	else {
		cout << "That isn't a palindrome";
	}
}

void ispalindromequeue(queue<char> q, string &str) {
	int i;
	bool ispalindrome = true;
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	// push to stack and queue
	string reversed;
	reversed.resize(str.size());

	for (i = 0; i < str.size(); i++) {
		q.push(tolower(str[i]));
		//(str.size() - 1) - i)
		
	}

	for (int i = str.size() - 1; i >= 0; i--) {
		reversed[i] = tolower(str[i]);
 	}
	for (i = 0; i < str.size(); i++) {
		// compare first element in queue with the first(reversed) element in the string
		if (q.front() == reversed[i]) {
			q.pop();
			continue;
		}
		// break and set ispalindrome as false if the characters doesn't match up
		else {
			ispalindrome = false;
			break;
		}
	}
	//prints out if the string is a palindrome or not
	if (ispalindrome == true) {
		cout << "That is a palindrome";
	}
	else {
		cout << "That isn't a palindrome";
	}


}
//test function removes the cout to tell if its a palidrome or not
void testpalindromestack(stack<char> &s, string &str) {
	int i;
	string reversed;
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	reversed = str;
	// push into stack
	for (i = 0; i < reversed.size(); i++) {
		s.push(reversed[i]);
	}
	// pop from stack
	for (i = 0; i < reversed.size(); i++) {
		reversed[i] = s.top();
		s.pop();
	}
}
// test function #2
// be careful with pass-by-reference
void testpalindromequeue(stack<char> &s, queue<char> &q, string &str) {
	int i;
	bool ispalindrome = true;
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	// push to stack and queue
	for (i = 0; i < str.size(); i++) {
		s.push(str[i]);
		q.push(str[i]);
	}
	for (i = 0; i < str.size(); i++) {
		// compare first element in queue with the first(reversed) element in the stack
		if (q.front() == s.top()) {
			q.pop();
			s.pop();
			continue;
		}
		// break and set ispalindrome as false if the characters doesn't match up
		else {
			ispalindrome = false;
			break;
		}
	}
	//deletes the stack and queue if it's not already empty
	while (!q.empty() && !s.empty()) {
		q.pop();
		s.pop();
	}

}

int main()
{
	stack<char> s;
	queue<char> q;
	string input;
	string choice;
	int iterations = 0;
	int wordsize = 0;
	int totalstack = 0;
	int totalqueue = 0;
	int r;
	char c;
	srand(time(NULL));
	auto start = std::chrono::high_resolution_clock::now();
	auto finish = std::chrono::high_resolution_clock::now();
	

	while (true) {
		int iterations = 0;
		int wordsize = 0;
		int totalstack = 0;
		int totalqueue = 0;
		cout << "1. Test if one word is a palindrome \n2. Test if many words are palindromes ";
		cin >> choice;
		if (choice == "1") {
			cout << "Input a word to test: ";
			cin.ignore();
			getline(cin, input);

			start = std::chrono::high_resolution_clock::now();
			ispalindromequeue(q, input);
			finish = std::chrono::high_resolution_clock::now();
			auto elapsedtimequeue = chrono::duration_cast<chrono::microseconds>(finish - start).count();
			cout << " in " << elapsedtimequeue << "ms" << " with queue only" << endl;

			start = chrono::high_resolution_clock::now();
			ispalindromestack(s, input);
			finish = chrono::high_resolution_clock::now();
			auto elapsedtimestack = chrono::duration_cast<chrono::microseconds>(finish - start).count();
			cout << " in " << elapsedtimestack << "ms" << " with stack only" << endl;
		}
		else if (choice == "2") {
			cout << "Input how many iterations you want to run: ";
			cin >> iterations;
			cout << "Input how long you want the words to be: ";
			cin >> wordsize;
			for (int i = 0; i < iterations; i++) {
				input = "";
				for (int j = 0; j < wordsize; j++) {
					r = rand() % 26;
					input += 'a' + r;
				}
				//cout << "Tested word: " << input << endl;
				start = chrono::high_resolution_clock::now();
				testpalindromestack(s, input);
				finish = chrono::high_resolution_clock::now();
				auto elapsedstack = chrono::duration_cast<chrono::microseconds>(finish - start).count();
				//cout << "Elapsed stack only: " << elapsedstack << " microsseconds" << endl;
				totalstack = totalstack + elapsedstack;

				start = chrono::high_resolution_clock::now();
				testpalindromequeue(s, q, input);
				finish = chrono::high_resolution_clock::now();
				auto elapsedqueue = chrono::duration_cast<chrono::microseconds>(finish - start).count();
				//cout << "Elapsed queue and stack: " << elapsedqueue << " microsseconds" << endl;
				totalqueue = totalqueue + elapsedqueue;

			}
			cout << "Average execution time with stack only: " << totalstack / iterations << "ms" << " with " << iterations << " iterations" << endl;
			cout << "Average execution time with queue: " << totalqueue / iterations << "ms" << " with " << iterations << " iterations" << endl;

		}
		else if (choice == "3") {
			cout << "Size of queue: " << q.size() << endl;
			cout << "Size of stack: " << s.size() << endl;
		}

		
		/*char * reversed = new char[input.length() + 1];
		strcpy_s(reversed, input.length() + 1, input.c_str());
		int len = strlen(reversed);*/

		/*auto start = std::chrono::high_resolution_clock::now();
		ispalindromequeue(s, q, input);
		auto finish = std::chrono::high_resolution_clock::now();
		chrono::duration<double> elapsedqueue = finish - start;
		cout << " in " << elapsedqueue.count() << "s" << " with stack and queue" <<  endl;
		start = chrono::high_resolution_clock::now();
		ispalindromestack(s, input);
		finish = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsedstack = finish - start;
		cout << " in " << elapsedstack.count() << "s" << " with stack only" << endl;*/

		//cout << "Elapsed: " << elapsed << endl;
		

	}



	//cout << "\n\nAfter reversing string is : " << reversed << "\n\n";
	//system("pause");
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
