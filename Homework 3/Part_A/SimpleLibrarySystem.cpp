//Ahmed Salih Cezayir 21802918 Sec03
#include "SimpleLibrarySystem.h" 
#include <iostream>
using namespace std;

LibrarySystem::LibrarySystem() {
	size = 0;
	head = NULL;
	tail = NULL;
}

LibrarySystem::~LibrarySystem() {
	while (!isEmpty()) {
		deleteFirstItem();
	}
}

void LibrarySystem::addStudent(const int studentId, const string studentName) {
	if (studentId <= 0) {
		cout << "Student id must be positive unique integer" << endl;
	}
	else if (isExist(studentId)) {
		cout << "Student " << studentId << " already exists" << endl;
	}
	else {
		Student s(studentId, studentName);
		Node* newPtr = new Node;
		newPtr->student = s;
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
		cout << "Student " << studentId << " has been added" << endl;
	}
}

void LibrarySystem::deleteStudent(const int studentId) {
	if (!isExist(studentId)) {
		cout << "Student " << studentId << " does not exist" << endl;
	}
	//If there is only one item and we want to delete that
	else if (size == 1) {
		delete head;
		head = NULL;
		size--;
		cout << "Student " << studentId << " has been deleted" << endl;
	}
	//Check whether first student is the one we are looking for
	else if ((head->student).getSimpleStudentId() == studentId) {
		Node* tmp = head;
		head = head->next;
		delete tmp;
		size--;
		cout << "Student " << studentId << " has been deleted" << endl;
	}
	else {
		Node* curr = head;
		for (int i = 1; i < size; i++) {
			if (((curr->next)->student).getSimpleStudentId() == studentId) {
				if (i == size - 1) { //deleting the last item of the list
					delete tail;
					curr->next = NULL;
					tail = curr;
				}
				else {
					Node* tmp;
					tmp = curr->next;
					curr->next = tmp->next;
					delete tmp;
				}
				break;
			}
			curr = curr->next;
		}
		size--;
		cout << "Student " << studentId << " has been deleted" << endl;
	}
}

//THIS METHOD IS ONLY FOR THE DESTRUCTOR. DO NOT USE IT IN OTHER PARTS!  
void LibrarySystem::deleteFirstItem() {
	Node* tmp = head;
	head = head->next;
	delete tmp;
	size--;
}

void LibrarySystem::showStudent(const int studentId) const {
	if (!isExist(studentId)) {
		cout << "Student " << studentId << " does not exist" << endl;
	}
	else {
		Node* curr = head;
		while (curr != NULL) {
			if ((curr->student).getSimpleStudentId() == studentId) {
				cout << "Student id: " << studentId << " student name: " << (curr->student).getSimpleName() << endl;
				break;
			}
			curr = curr->next;
		}
	}
}

bool LibrarySystem::isEmpty() const {
	return size == 0;
}

bool LibrarySystem::isExist(const int id) const {
	if (size == 0)
		return false;
	else {
		Node* cur = head;
		while (cur != NULL) {
			if ((cur->student).getSimpleStudentId() == id)
				return true;
			else
				cur = cur->next;
		}
		return false;
	}
}

int LibrarySystem::getLength() const {
	return size;
}