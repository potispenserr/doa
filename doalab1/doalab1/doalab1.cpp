// doalab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
//defines the node with coursename, credits, grade and next pointer as fields

struct node
{
	string coursename;

	node *next;
};
class Course {
private:
	// head and tail for the node struct
	node *head, *tail;
public:
	//constructor
	Course() {
		head = NULL;
		tail = NULL;
	}
	// destructor for the Course class
	// just deletes all the elements in the linked list
	~Course() {
		node* current = head;
		node* next;

		while (current != NULL)
		{
			next = current->next;
			delete current;
			current = next;
		}
		head = NULL;
	}
	// creates a new course node
	void createnode(string coursename, float credits, int grade) {
		node *temp = new node;
		// sets the fields in the node
		temp->coursename = coursename;
		temp->credits = credits;
		temp->next = NULL;
		//checks if the linked list is empty 
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		// if it isn't it sets the tail as the new node
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	// prints out all the courses in the nodes
	void display() {
		node *temp;
		// sets the temp pointer to head
		temp = head;
		// starts the count variable with the value 1
		int count = 1;
		// loops through the linked list while printing out all the courses
		while (temp != NULL)
		{
			//starts printing the course number and course name
			cout << "\t" << count << ". " << "Course: " << temp->coursename << endl;
			cout << "\t" << "Credit: " << temp->credits << endl;
			cout << endl;
			temp = temp->next;
			//increments the counter
			count++;
			
		}
	}
	// returns the index for a given course
	int findcourse(string coursename) {
		// creates a pointer and assigns it to head
		node *temp;
		temp = head;
		int pos = 0;
		//traverses the linked list until it finds the course incrementing pos every iteration
		while (temp != NULL) {	
			if (coursename == temp->coursename) {
				break;
			}
			else {
				pos++;
				temp = temp->next;
			}	
		}
		// returns pos as the index for the course
		return pos;
	}

	void deletecourse(int courseindex) {
		node *current;
		node *previous;
		current = head;
		previous = head;

		// checks if head is null
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		//gets courseindex from the user and subtracts 1 to get the index
		int pos = courseindex - 1;
		
		if (pos >= 1) {
			//traverses down the linked list
			for (int i = 1; i <= pos; i++)
			{
				previous = current;
				current = current->next;
				if (current == NULL) {
					cout << "Course not found" << endl;
					return;
				}
			}
			if (current == NULL) {
				cout << "Course not found" << endl;
				return;
			}

			else {
				previous->next = current->next;
			}
			
		}
		else {
			// deletes the course
			head = head->next;
			delete current;
			
		}
		
	}

	// just checks if head is empy and if it is the database is empty
	bool emptydb() {
		node* temp;
		temp = head;
		if (temp == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Student {
private:
	// the studentname for each object
	string studentname;
public:
	//constructors
	Student() {
		studentname = "";
	}
	Student(string s) {
		studentname = s;
	}
	Course c;
	//get and set
	string  getname() { return studentname; }
	void setname(string s) { studentname = s; }

};
// only prints the names registered
void printnames( vector<Student>& students) {
	for (int i = 0; i < students.size(); i++) {
		cout << i+1 << ": " << students[i].getname() << endl;
	}
}

//prints the name and courses for every student
void printnamecourse(vector<Student>& students) {
	for (int i = 0; i < students.size(); i++) {
		cout << i + 1 << ": " << students[i].getname() << endl;
		students[i].c.display();
	}
}

// gets input from the user to specify which student
// i put it as a function to avoid copy-pasting it everywhere
int getstudentindex(vector<Student>& students) {
	int intinput;
	cout << "Input which student number you want to change: ";
	cin >> intinput;
	return intinput - 1;

}

void addstudent(string &studentname, vector<Student> &students, int &vecsize) {
	vecsize++;
	//resizes the vector with it's size + 1
	students.resize(vecsize);
	//sets the new student object name to the user input
	//vecsize - 1 is the index for the new object 
	students[vecsize - 1] = Student();
	students[vecsize - 1].setname(studentname);

}

int main()
{
	//Initializing vector array of type Student class
	vector<Student> students;
	//Initializing userinputs
	string input;
	int intinput;
	string studentname;
	string coursename;
	float credits;
	int grade;
	//initializing size of vector and studentindex here instead of later
	int vecsize = 1;
	int studentindex;

	students.resize(1);

	

	while (true) {
		cout << "1. Add student \n2. Register course \n3. Display all students \n4. Delete course \n5. Delete student record \n6. Quit" << endl;
		cin >> input;
		//Adding students
		if (input == "1") {
			cout << "Input student name: ";
			cin >> input;
			//increases the vecsize variable by 1
			
		}
		else if (input == "2") {
			//error checking
			if (vecsize == 0) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				//prints out all the names 
				printnames(students);
				//gets the index for the specific student from getstudentindex with students vector as a reference
				studentindex = getstudentindex(students);
				//input for the course name, credit and grade
				cout << "Input course name: ";
				cin.ignore();
				getline(cin, coursename);
				cout << "Input course credit: ";
				cin >> credits;
				//creates a new course node with the details provided
				students[studentindex].c.createnode(coursename, credits, grade);
			}
		}
		else if (input == "3") {
			//error checking
			if (vecsize == 0) {
				cout << "No student records found" << endl;
				continue;
			}
			// just prints out the students with their associated courses
			else {
				printnamecourse(students);
			}
		}
		else if (input == "4") {
			//error checking
			if (vecsize == 0) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				//more error checking
				printnames(students);
				//gets the student index
				studentindex = getstudentindex(students);
				if (students[studentindex].c.emptydb() == true) {
					cout << "No courses registered" << endl;
					continue;
				}
				else {
					//prints out all the specific student's courses
					students[studentindex].c.display();
					cout << "What course number do you want to delete? ";
					cin >> intinput;
					//the courses are numbered and stored in order so the user only has to input the number
					students[studentindex].c.deletecourse(intinput);
				}
			}
		}
		else if (input == "5") {
			// error checking
			if (vecsize == 0) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				//prints all the students 
				printnames(students);
				cout << "Input which student number you want to delete: ";
				cin >> intinput;
				// decrements the userinput by 1 to get the index for the student
				intinput--;
				//calls the destructor for the student specified
				
			}

		}
		// quits
		else if (input == "6") {
			break;
		}
		else if (input == "7") {
			//clocks the time
			auto start = chrono::high_resolution_clock::now();
			students[0].setname("borjex");
			auto finish = chrono::high_resolution_clock::now();
			chrono::duration<double> elapsed = finish - start;
			cout << "Elapsed add: " << elapsed.count() << "s\n";


			start = std::chrono::high_resolution_clock::now();
			students[0].c.createnode("how to be fast as fuck boi", 10.3f, 3);
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed add course: " << elapsed.count() << "s\n";

			start = std::chrono::high_resolution_clock::now();
			students[0].c.deletecourse(0);
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed remove course: " << elapsed.count() << "s\n";

			start = std::chrono::high_resolution_clock::now();
			// decrements the vector size by 1 
			vecsize--;
			// removes the student specified from the vector with the index provided
			students.erase(students.begin() + 0);
			finish = chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed remove student " << elapsed.count() << "s\n";

		}
		 //if the user didn't type in something valid
		else {
			cout << "Invalid input" << endl;
		}
	}

    
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
