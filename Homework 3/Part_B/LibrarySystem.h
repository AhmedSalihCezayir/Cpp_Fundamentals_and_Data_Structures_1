//Ahmed Salih Cezayir 21802918 Sec03
#ifndef _LIBRARYSYSTEM_H
#define _LIBRARYSYSTEM_H

#include "Student.h"
#include <string>
using namespace std;

class LibrarySystem {
public:
	LibrarySystem();
	~LibrarySystem();

	void addBook(const int bookId, const string bookName, const int bookYear);
	void deleteBook(const int bookId);

	void addStudent(const int studentId, const string studentName);
	void deleteStudent(const int studentId);

	void checkoutBook(const int bookId, const int studentId);
	void returnBook(const int bookId);

	void showAllBooks();
	void showBook(const int bookId) const;
	void showStudent(const int studentId) const;

	bool isExistBook(const int bookId) const;
	bool isExistStudent(const int studentId) const;

	void returnAllBooks(const int studentId);

private:
	struct Node {
		Student student;
		Node* next;
	};

	struct BookNode {
		Book book;
		BookNode* next;
		int currentTakerId;
	};

	Node* headStudent;
	Node* tailStudent;
	int sizeStudent;

	BookNode* headBook;
	BookNode* tailBook;
	int sizeBook;
};
#endif
