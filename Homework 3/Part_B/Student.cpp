//Ahmed Salih Cezayir 21802918 Sec03
#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(int id, string n) {
	name = n;
	studentId = id;
	head = NULL;
	tail = NULL;
	size = 0;
}

Student::Student() {
	studentId = 0;
	name = "";
	head = NULL;
	tail = NULL;
	size = 0;
}

Student::~Student() {
	while (!isEmpty()) {
		deleteFirstItem();
	}
}

void Student::setName(string n) {
	name = n;
}

void Student::setStudentId(int id) {
	studentId = id;
}

void Student::setSize(int nSize) {
	size = nSize;
}

string Student::getName() const{
	return name;
}

int Student::getStudentId() const{
	return studentId;
}

int Student::getSize() const {
	return size;
}

void Student::borrowBook(const int bookId, const string title, const int year) {
	Book b(bookId, title, year);
	b.changeStatus(false);
	BookNode* newPtr = new BookNode;

	newPtr->book = b;
	newPtr->next = NULL;

	if (size == 0) {
		head = newPtr;
		tail = newPtr;
	}
	else {
		tail->next = newPtr;
		tail = newPtr;
	}
	size++;
}

void Student::returnBorrowedBook(const int bookId) {
	if (size == 1) {
		head->book.changeStatus(true);
		head = NULL;
		size--;
	}
	else if ((head->book).getId() == bookId) {
		head->book.changeStatus(true);
		BookNode* tmp = head;
		head = head->next;
		delete tmp;
		size--;
	}
	else {
		BookNode* curr = head;
		for (int i = 1; i < size; i++) {
			if (((curr->next)->book).getId() == bookId) {
				if (i == size - 1) { //deleting the last item of the list
					tail->book.changeStatus(true);
					delete tail;
					curr->next = NULL;
					tail = curr;
				}
				else {
					BookNode* tmp;
					tmp = curr->next;
					curr->next = tmp->next;
					tmp->book.changeStatus(true);
					delete tmp;
				}
				break;
			}
			curr = curr->next;
		}
		size--;
	}
}

void Student::showStudentInfo() const {
	BookNode* curr = head;
	cout << "Student id: " << getStudentId() << " student name: " << getName() << endl;
	if (size == 0) {
		cout << "Student " << getStudentId() << " has no books" << endl;
	}
	else {
		cout << "Student " << getStudentId() << " has checked out the following books:" << endl;
		cout << "Book id\tBook name\t\tYear" << endl;
		while (curr != NULL) {
			cout << curr->book.getId() << "\t";
			cout << curr->book.getTitle() << "\t";
			if (curr->book.getTitle().length() < 6) {
				cout << "\t";
			}
			if (curr->book.getTitle().length() < 12) {
				cout << "\t";
			}
			cout << curr->book.getYear() << "\t" << endl;
			curr = curr->next;
		}
	}
}

int Student::showBookId(int index) const {
	BookNode* curr = head;
	for (int i = 1; i < index; i++) {
		curr = curr->next;
	}
	return curr->book.getId();
}

void Student::deleteFirstItem() {
	BookNode* tmp = head;
	head = tmp->next;
	delete tmp;
	size--;
}

bool Student::isEmpty() {
	return size == 0;
}

Student& Student::operator=(const Student& right) {
	if (&right != this) {
		studentId = right.studentId;
		name = right.name;
		head = right.head;
		tail = right.tail;
		size = right.size;
	}
	return *this;
}


