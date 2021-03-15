//Ahmed Salih Cezayir 21802918 Sec03
#ifndef _SIMPLELIBRARYSYSTEM_H
#define _SIMPLELIBRARYSYSTEM_H

#include "SimpleStudent.h"
#include <string>
using namespace std;

class LibrarySystem {
public:
	LibrarySystem();
	~LibrarySystem();

	void addStudent(const int studentId, const string studentName);
	void deleteStudent(const int studentId);
	void showStudent(const int studentId) const;
	void deleteFirstItem();

	bool isEmpty() const;
	bool isExist(const int id) const;

	int getLength() const;


private:
	struct Node {
		Student student;
		Node* next;
	};

	Node* head;
	Node* tail;
	int size;
};

#endif