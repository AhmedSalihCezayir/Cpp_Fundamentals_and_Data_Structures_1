//Ahmed Salih Cezayir 21802918 Sec03
#ifndef _STUDENT_H
#define _STUDENT_H

#include "Book.h"
#include <string>
using namespace std;

class Student {
public:
	Student(int id, string name);
	Student();
	~Student();

	void setName(string name);
	void setStudentId(int studentId);
	void setSize(int nSize);

	string getName() const;
	int getStudentId() const;
	int getSize() const;

	void borrowBook(const int bookId, const string title, const int year);
	void returnBorrowedBook(const int bookId);
	void showStudentInfo() const;
	int showBookId(int index) const;
	void deleteFirstItem();
	bool isEmpty();

	Student& operator=(const Student& right);

private:
	struct BookNode {
		Book book;
		BookNode* next;
	};

	BookNode* head;
	BookNode* tail;
	int size;

	string name;
	int studentId;
};

#endif
