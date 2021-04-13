// doalab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <chrono>
using namespace std;
// node for the students
struct node {
	string studentname;
	node *next;
};
class Student {
private:
	node *top;
public:
	// Constructor
	Student() {
		top = NULL;
	}
	// Destructor
	~Student() {
		node* current = top;
		node* next;

		while (current != NULL)
		{
			next = current->next;
			delete current;
			current = next;
		}
		top = NULL;
	}
	// creates a new student node on the stack
	void createnode(string studentname) {
		node *temp = new node;
		// setting fields
		temp->studentname = studentname;
		temp->next = NULL;
		if (top == NULL) {
			top = temp;
		}
		else {
			temp->next = top;
			top = temp;

		}

	}
	// deletes a student from the top of the stack
	void pop() {
		if (top == NULL) {
			cout << "There is nothing to pop" << "\n";
		}
		else {
			cout << "Popped: " << top->studentname << "\n";
			node* temp = top;
			top = top->next;
			free(temp);
		}
	}
	// prints out all the students of the stack
	void display() {
		node *head;
		head = top;
		while (head != NULL) {
			if (head->next == NULL) {
				cout << " " << head->studentname;
			}
			else {
				cout << " " << head->studentname << ",";
			}
			head = head->next;

		}
	}
	//prints a modified display for the delete screen
	void deletedisplay() {
		node *head;
		head = top;
		int count = 1;
		while (head != NULL) {
			if (head->next == NULL) {
				cout << " " << head->studentname;
			}
			else {
				cout << " " << head->studentname << ",";
			}
			head = head->next;
			count++;

		}
		cout << endl;

	}
	//checks if studentname is in the stack 
	bool findstudent(string studentname) {
		node *head;
		node *temp;
		head = top;
		int pos = 0;
		while (head != NULL) {
			if (studentname == head->studentname) {
				cout << "found student" << endl;

				return true;
			}
			else {
				temp = head;
				head = head->next;
			}
		}
		return false;

	}
	// goes through the stack and deletes a student with given name
	void deletestudent(string studentname) {
		node* head = top;
		cout << studentname << "\n";

		if (findstudent(studentname) == false) {
			cout << "Student not found" << "\n";
			return;

		}
		else {
			while (!top == NULL) {
				head = top;
				if (head->studentname == studentname) {
					pop();
					break;
				}
				else {
					pop();
				}

			}

		}
	}

};
// node for courses
struct nodest {
	string coursename;
	Student st;
	nodest *next;
};

class Course {
private:
	nodest *head, *tail;
public:
	// Constructor 
	Course() {
		head = NULL;
		tail = NULL;
	}
	// Destructor 
	~Course() {
		nodest* current = head;
		nodest* next;

		while (current != NULL)
		{
			next = current->next;
			delete current;
			current = next;
		}
		head = NULL;
	}
	// creates a new node with the coursename and students
	void createnode(string coursename) {
		nodest *temp = new nodest;
		temp->coursename = coursename;
		temp->st;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	//loops through the course linked list and prints all the courses with student names
	void displaycourse() {
		nodest *temp;
		temp = head;
		int count = 1;
		while (temp != NULL)
		{
			cout << count << ". " << temp->coursename << ":";
			temp->st.display();
			count++;
			temp = temp->next;
			cout << endl;

		}
	}
	//loops through the course linked list and prints all the courses 
	void displaynames() {
		nodest *temp;
		temp = head;
		int counter = 1;
		while (temp != NULL)
		{
			cout << counter << ". " << "Course: " << temp->coursename << endl;
			temp = temp->next;
			counter++;
		}
	}
	//finds and prints all the student names associated with the course provided
	void finddisplay(int courseindex) {
		nodest *temp;
		temp = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		int pos = courseindex;

		if (pos >= 0) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++)
			{
				temp = temp->next;
				if (temp == NULL) {
					cout << "Course not found" << endl;
					return;
				}
			}
			// if it goes through the list and temp isn't nullptr 
			// it displays all the courses for that student
			temp->st.deletedisplay();

		}
		else {
			cout << "Good try but that's not going to work (Course not found)" << endl;
		}

	}
	// add student to course
	void addstudent(int courseindex, string studentname) {
		nodest *temp;
		temp = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the position of the student record from the courseindex parameter
		int pos = courseindex;

		if (pos >= 0) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++)
			{
				temp = temp->next;
				//if temp is null then it's safe to say that the course number doesn't exist
				if (temp == NULL) {
					cout << "course not found" << endl;
					return;
				}
			}
			//when temp is at the specified position in the linked list it adds the student
			temp->st.createnode(studentname);

		}
		//for when the user tries to break everything
		else {
			cout << "Good try but that's not going to work (course not found)" << endl;
		}
	}
	// deletes a single student
	void deletestudent(int courseindex, string studentname) {
		nodest *temp;
		temp = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the position of the student record from the courseindex parameter
		int pos = courseindex;

		if (pos >= 0) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++) {
				temp = temp->next;
				if (temp == NULL) {
					cout << "course not found" << endl;
					return;
				}
			}
			// when temp is at the right student in the linked list it deletes the student
			temp->st.deletestudent(studentname);

		}
		//for when the user tries to break everything
		else {
			cout << "Good try but that's not going to work (course not found)" << endl;
		}

	}
	// deletes the course from the linked list
	void deletecourse(int courseindex) {
		nodest *current;
		nodest *previous;
		current = head;
		previous = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the position of the student record from the courseindex parameter
		int pos = courseindex;

		if (pos > 1) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++) {
				previous = current;
				current = current->next;
				// if it iterates through the linked list but current is nullptr it stops
				if (current == NULL) {
					cout << "Course not found" << endl;
					return;
				}
			}
			//if it iterates through the list and current doesn't become nullptr
			//the previous next pointer becomes the current's
			previous->next = current->next;

		}
		else {
			//here it deletes the course
			head = head->next;
			delete current;

		}

	}

	//  checks if the database is empty or not
	bool emptydb() {
		nodest* temp;
		temp = head;
		if (temp == NULL) {
			return true;
		}
		else {
			return false;
		}
	}
};


int main()
{
	//initializing the class object
	Course c;
	//initializing the user inputs
	string input;
	int intinput;
	string studentname;
	string coursename;
	float credits;
	int grade;
	// test
	
	c.createnode("Intro to bullshiting");
	c.addstudent(1, "Steffan");
	c.addstudent(1, "Bert");

	while (true) {
		// menu
		cout << "1. Register course \n2. Add student \n3. Display all courses \n4. Delete student \n5. Delete course \n6. Quit" << endl;
		cin >> input;
		//register course
		if (input == "1") {
			// takes input and adds the course to the linked list
			cout << "Input course name: ";
			cin.ignore();
			getline(cin, coursename);
			c.createnode(coursename);
		}
		//add student
		else if (input == "2") {
			// error checking
			if (c.emptydb() == true) {
				cout << "No course records found" << endl;
				continue;
			}
			else {
				// prints all the courses
				c.displaynames();
				cout << "Input the course number you want to change: ";
				cin >> intinput;
				// takes input on the student name
				cout << "Input student name: ";
				cin.ignore();
				getline(cin, studentname);
				// adds the student
				c.addstudent(intinput, studentname);
			}
		}
		//display courses
		else if (input == "3") {
			// error checking
			if (c.emptydb() == true) {
				cout << "No courses found" << endl;
				continue;
			}
			else {
				// just prints out all the courses with their associated students 
				c.displaycourse();
			}
			
		}
		// deletes a single student from a course
		else if (input == "4") {
			// error checking
			if (c.emptydb() == true) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				//prints all course names 
				c.displaynames();
				cout << "Input the course number you want to change: ";
				//takes input for the course the user want to change
				cin >> intinput;
				//prints the specific courses students
				c.finddisplay(intinput);
				cout << "Who do you want to delete? ";
				// takes input on which student number the user wants to delete
				cin.ignore();
				getline(cin, studentname);
				// deletes the student
				c.deletestudent(intinput, studentname);
			}
		}
		// deletes course record
		else if (input == "5") {
			// error checking
			if (c.emptydb() == true) {
				cout << "No courses found" << endl;
				continue;
			}
			else {
				//prints all course names
				c.displaynames();
				cout << "Input which course number do you want to delete: ";
				cin >> intinput; 
				//takes input for course and deletes the course 
				c.deletecourse(intinput);
			}
		}
		//quit
		else if (input == "6") {
			break;
		}
		//secret benchmark option
		else if (input == "7") {
			// add course test
			auto start = std::chrono::high_resolution_clock::now();
			c.createnode("Intro to Quantum Immortality");
			auto finish = std::chrono::high_resolution_clock::now();
			chrono::duration<double> elapsed = finish - start;
			cout << "Elapsed add course: " << elapsed.count() << "s\n";

			//add student test
			start = std::chrono::high_resolution_clock::now();
			c.addstudent(2, "Steffe Jannson");
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed add student: " << elapsed.count() << "s\n";


			//remove student test
			start = std::chrono::high_resolution_clock::now();
			c.deletestudent(2, "Steffe Jannson");
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed remove student " << elapsed.count() << "s\n";
			//remove course test
			start = std::chrono::high_resolution_clock::now();
			c.deletecourse(2);
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed remove course: " << elapsed.count() << "s\n";

		}
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
