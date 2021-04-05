// doalab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
// node for the courses
struct node {
	string coursename;
	node *next;
};
class Course {
private:
	node *head, *tail;
public:
	// Constructor
	Course() {
		head = NULL;
		tail = NULL;
	}
	// Destructor
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
		// setting fields
		temp->coursename = coursename;
		temp->next = NULL;
		// if head is null this is the first element so point the tail to null
		if (head == NULL) {
			head = temp;
			tail = temp;
			temp = NULL;
		}
		// otherwise set the tail to this element
		else {
			tail->next = temp;
			tail = temp;
		}
	}
	// prints out all the courses of the linked list
	void display() {
		node *temp;
		temp = head;
		int count = 1;
		while (temp != NULL) {
			cout << "\t" << count << ". " << "Course: " << temp->coursename << endl;
			cout << endl;
			temp = temp->next;
			count++;

		}
	}
	//test 
	int findcourse(string coursename) {
		node *temp;
		temp = head;
		int pos = 0;
		while (temp != NULL) {
			if (coursename == temp->coursename) {
				cout << "found course" << endl;
				break;
			}
			else {
				pos++;
				temp = temp->next;
			}
		}
		return pos;
	}
	// deletes a course with given index
	void deletecourse(int courseindex) {
		node *current;
		node *previous;
		current = head;
		previous = head;
		// error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the pos from the parameter courseindex
		int pos = courseindex;
		//iterates through the linked list until it hits the position specified
		if (pos > 1) {
			for (int i = 1; i < pos; i++)
			{
				previous = current;
				current = current->next;
				if (current == NULL) {
					cout << "Course not found" << endl;
					return;
				}
			}
				previous->next = current->next;

		}
		else {
			// deletes the course
			head = head->next;
			delete current;

		}

	}
};
// node for students
struct nodest {
	string studentname;
	Course c;
	nodest *next;
};

class Student {
private:
	nodest *head, *tail;
public:
	// Constructor 
	Student() {
		head = NULL;
		tail = NULL;
	}
	// Destructor 
	~Student() {
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
	// includes the Course class
	Course c;
	// creates a new node with the studentname and courses
	void createnode(string studentname) {
		nodest *temp = new nodest;
		temp->studentname = studentname;
		temp->c;
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
	//loops through the student linked list and prints all the student names with courses
	void displaycourse() {
		nodest *temp;
		temp = head;
		int count = 1;
		while (temp != NULL)
		{
			cout << count << ". " << temp->studentname << endl;
			temp->c.display();
			count++;
			temp = temp->next;

		}
	}
	//loops through the student linked list and prints all the student names 
	void displaynames() {
		nodest *temp;
		temp = head;
		int counter = 1;
		while (temp != NULL)
		{
			cout << counter << ". " << "Student: " << temp->studentname << endl;
			temp = temp->next;
			counter++;
		}
	}
	//finds and prints all the courses associated with the student name provided
	void finddisplay(int studentindex) {
		nodest *temp;
		temp = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the position of the student record from the findstudent method
		int pos = studentindex;

		if (pos >= 0) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++)
			{
				temp = temp->next;
				if (temp == NULL) {
					cout << "Student not found" << endl;
					return;
				}
			}
			// if it goes through the list and temp isn't nullptr 
			// it displays all the courses for that student
			temp->c.display();

		}
		else {
			cout << "Good try but that's not going to work (Student not found)" << endl;
		}

	}
	void addcourse(int studentindex, string coursename) {
		nodest *temp;
		temp = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the position of the student record from the studentindex parameter
		int pos = studentindex;

		if (pos >= 0) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++)
			{
				temp = temp->next;
				//if temp is null then it's safe to say that the student number doesn't exist
				if (temp == NULL) {
					cout << "Student not found" << endl;
					return;
				}
			}
			//when temp is at the specified position in the linked list it adds the course
			temp->c.createnode(coursename);

		}
		//for when the user tries to break everything
		else {
			cout << "Good try but that's not going to work (Student not found)" << endl;
		}
	}
	// deletes a single course
	void deletecourse(int studentindex, int courseindex) {
		nodest *temp;
		temp = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the position of the student record from the studentindex parameter
		int pos = studentindex;

		if (pos >= 0) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++) {
				temp = temp->next;
				if (temp == NULL) {
					cout << "Student not found" << endl;
					return;
				}
			}
			// when temp is at the right student in the linked list it deletes the course
			temp->c.deletecourse(courseindex);

		}
		//for when the user tries to break everything
		else {
			cout << "Good try but that's not going to work (Student not found)" << endl;
		}

	}
	// deletes the student record from the linked list
	void deletestudent(int studentindex) {
		nodest *current;
		nodest *previous;
		current = head;
		previous = head;
		//error checking
		if (head == NULL) {
			cout << "Database is empty" << endl;
			return;
		}
		// gets the position of the student record from the studentindex parameter
		int pos = studentindex;

		if (pos > 1) {
			//iterates through the linked list until it hits the position specified
			for (int i = 1; i < pos; i++) {
				previous = current;
				current = current->next;
				// if it iterates through the linked list but current is nullptr it stops
				if (current == NULL) {
					cout << "Student not found" << endl;
					return;
				}
			}
			//if it iterates through the list and current doesn't become nullptr
			//the previous next pointer becomes the current's
				previous->next = current->next;

		}
		else {
			//here it deletes the student record
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
	Student s;
	//initializing the user inputs
	string input;
	int intinput;
	string studentname;
	string coursename;
	float credits;
	int grade;
	// test
	
	//s.createnode("borje");
	/*s.createnode("borj");
	s.createnode("bor");;
	s.createnode("b");
	s.createnode("bq");
	s.createnode("bw");
	s.createnode("borjeq");
	s.createnode("borjew");
	s.createnode("borjee");
	s.createnode("borjer");*/
	/*
	s.addcourse(1, "snusa som satan", 140.2, 740);
	s.addcourse(10, "lägga 740n i bredställ", 240.2, 740);
	s.addcourse(10, "Att citera Linus Torvalds angående C++", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angående C+", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angående C", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angående ", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angående", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angåend", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angåen", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angåe", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds angå", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds ang", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds an", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds a", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds ", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvalds", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torvald", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torval", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torva", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Torv", 10.2f, 4);
	s.addcourse(10, "Att citera Linus Tor", 10.2f, 4);
	s.addcourse(10, "Att citera Linus To", 10.2f, 4);
	*/
	while (true) {
		// menu
		cout << "1. Add student \n2. Register course \n3. Display all students \n4. Delete course \n5. Delete student record \n6. Quit" << endl;
		cin >> input;
		//add student
		if (input == "1") {
			// takes input and adds the student to the linked list
			cout << "Input student name: ";
			cin >> input;
			s.createnode(input);
		}
		//register course
		else if (input == "2") {
			// error checking
			if (s.emptydb() == true) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				// prints all the student names
				s.displaynames();
				cout << "Input the student number you want to change: ";
				cin >> intinput;
				// takes input on the course name credit and grade
				cout << "Input course name: ";
				cin.ignore();
				getline(cin, coursename);
				// adds the course
				s.addcourse(intinput, coursename);
			}
		}
		//display students
		else if (input == "3") {
			// error checking
			if (s.emptydb() == true) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				// just prints out all the students with their associated courses 
				s.displaycourse();
			}
			
		}
		// deletes a single course from a student record
		else if (input == "4") {
			// error checking
			if (s.emptydb() == true) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				//prints all student names 
				s.displaynames();
				cout << "Input the student number you want to change: ";
				//takes input for the student the user want to change
				cin >> intinput;
				//prints the specific students courses
				s.finddisplay(intinput);
				cout << "What course number do you want to delete? ";
				// takes input on which course number the user wants to delete
				cin >> intinput;
				// deletes the course
				s.deletecourse(intinput, intinput);
			}
		}
		// deletes student record
		else if (input == "5") {
			// error checking
			if (s.emptydb() == true) {
				cout << "No student records found" << endl;
				continue;
			}
			else {
				//prints all student names
				s.displaynames();
				cout << "Input which student number do you want to delete: ";
				cin >> intinput; 
				//takes input for student and deletes the student 
				s.deletestudent(intinput);
			}
		}
		//quits
		else if (input == "6") {
			break;
		}
		else if (input == "7") {
			// timers
			auto start = std::chrono::high_resolution_clock::now();
			s.createnode("borjex");
			auto finish = std::chrono::high_resolution_clock::now();
			chrono::duration<double> elapsed = finish - start;
			cout << "Elapsed add: " << elapsed.count() << "s\n";

			start = std::chrono::high_resolution_clock::now();
			//s.addcourse(1, "how to be fast as fuck boi", 10.3f, 3);
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed add course: " << elapsed.count() << "s\n";

			start = std::chrono::high_resolution_clock::now();
			s.deletecourse(1, 1);
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed remove course: " << elapsed.count() << "s\n";

			start = std::chrono::high_resolution_clock::now();
			s.deletestudent(1);
			finish = std::chrono::high_resolution_clock::now();
			elapsed = finish - start;
			cout << "Elapsed remove student " << elapsed.count() << "s\n";

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
