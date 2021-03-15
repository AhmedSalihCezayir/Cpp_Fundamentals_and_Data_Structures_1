//Ahmed Salih Cezayir 21802918 Sec03
#include "LibrarySystem.h"
#include <iostream>
using namespace std;

LibrarySystem::LibrarySystem() {
	headBook = NULL;
	tailBook = NULL;
	headStudent = NULL;
	tailStudent = NULL;
	sizeBook = 0;
	sizeStudent = 0;
}

LibrarySystem::~LibrarySystem() {
	// Delete the linked list for the students
	while (sizeStudent != 0) {
		Node* tmp = headStudent;
		headStudent = tmp->next;
		delete tmp;
		sizeStudent--;
	}
	
	// Delete the linked list for the books
	while (sizeBook != 0) {
		BookNode* tmp = headBook;
		headBook = tmp->next;
		delete tmp;
		sizeBook--;
	}
}

// Method for adding a book to book linked list
void LibrarySystem::addBook(const int bookId, const string bookName, const int year) {
	// Check the book id. If it is negative or already exists print an error message
	if (bookId <= 0) {
		cout << "Book id must be positive unique integer" << endl;
	}
	else if (isExistBook(bookId)) {
		cout << "Book " << bookId << " already exists" << endl;
	}
	else {
		// If the bookId is ok create a book object and bookNode
		Book b(bookId, bookName, year);
		BookNode* newPtr = new BookNode;
		newPtr->book = b;
		newPtr->next = NULL;
		newPtr->currentTakerId = 0;

		// If this is the first item headBook will point to this node
		if (sizeBook == 0) {
			headBook = newPtr;
			tailBook = newPtr;
		}
		else {
			// If this is not the first node, add it to the end and ensure that tail points to this node
			tailBook->next = newPtr;
			tailBook = newPtr;
		}
		sizeBook++;
		cout << "Book " << bookId << " has been added" << endl;
	}
}

// Delete a book from the book linked list
void LibrarySystem::deleteBook(const int bookId) {
	int currentTakerId;
	bool status = true;

	// Check if the book already exists or not
	if (!isExistBook(bookId)) {
		cout << "Book " << bookId << " does not exist" << endl;
	}
	//If there is only one item and we want to delete that
	else if (sizeBook == 1) {
		currentTakerId = headBook->currentTakerId;
		status = headBook->book.getStatus();

		delete headBook;
		headBook = NULL;
		sizeBook--;

		if (status)
			cout << "Book " << bookId << " has not been checked out " << endl;
		else
			cout << "Book " << bookId << " has been returned " << endl;
		cout << "Book " << bookId << " has been deleted" << endl;
	}
	//Check whether first book is the one we are looking for
	else if ((headBook->book).getId() == bookId) {
		// Get the current student that holds this book
		currentTakerId = headBook->currentTakerId;
		BookNode* tmp = headBook;

		headBook = headBook->next;
		// Get the status of this book (Whether is it available or not)
		status = tmp->book.getStatus();
		delete tmp;
		sizeBook--;

		// Status == True => Book is available (not taken)
		if (status)
			cout << "Book " << bookId << " has not been checked out " << endl;
		else
			cout << "Book " << bookId << " has been returned " << endl;
		cout << "Book " << bookId << " has been deleted" << endl;
	}
	else {
		// Create a bookNode pointer to looping
		BookNode* curr = headBook;
		// Start looping in the books linked list
		for (int i = 1; i < sizeBook; i++) {
			// If the current book has the if that we want to delete
			if (((curr->next)->book).getId() == bookId) {
				// If the item is at the end of the linked list update the tail pointer
				if (i == sizeBook - 1) { 
					currentTakerId = tailBook->currentTakerId;
					status = tailBook->book.getStatus();
					delete tailBook;

					curr->next = NULL;
					tailBook = curr;
				}
				else {
					BookNode* tmp;
					tmp = curr->next;
					curr->next = tmp->next;
					currentTakerId = tmp->currentTakerId;
					status = tmp->book.getStatus();
					delete tmp;	
				}
				break;
			}
			curr = curr->next;
		}
		sizeBook--;
		if (status)
			cout << "Book " << bookId << " has not been checked out " << endl;
		else
			cout << "Book " << bookId << " has been returned " << endl;
		cout << "Book " << bookId << " has been deleted" << endl;
	}

	// If the book is taken make sure the student returns it (because this book does not exist anymore)
	if (status == false) {
		Node* curr2 = headStudent;
		// Loop through the students list and find the student who borrowed this book
		while (curr2 != NULL) {
			if (curr2->student.getStudentId() == currentTakerId) {
				curr2->student.returnBorrowedBook(bookId);
				break;
			}
			else {
				curr2 = curr2->next;
			}
		}
	}
}

// Method for adding a student to the student linked list
void LibrarySystem::addStudent(const int studentId, const string studentName) {
	// Check the student id. If it is negative or already exists print an error message
	if (studentId <= 0) {
		cout << "Student id must be positive unique integer" << endl;
	}
	else if (isExistStudent(studentId)) {
		cout << "Student " << studentId << " already exists" << endl;
	}
	else {
		// Create the student object
		Student s(studentId, studentName);
		Node* newPtr = new Node;
		newPtr->student = s;
		newPtr->next = NULL;

		// If the list is empty and this is the first element of it
		if (sizeStudent == 0) {
			headStudent = newPtr;
			tailStudent = newPtr;
		}
		else {
			tailStudent->next = newPtr;
			tailStudent = newPtr;
		}
		sizeStudent++;
		cout << "Student " << studentId << " has been added" << endl;
	}
}

// Method for deleting a student from the student linked list
void LibrarySystem::deleteStudent(const int studentId) {
	// If the student id exists
	if (isExistStudent(studentId)) {
		// This array only holds the bookIds that are gonna be returned. It does not have any other purpose.
		int ids[100];

		// Create a Node pointer for looping the student list 
		Node* curr;
		curr = headStudent;
		int size;
		int id;
		while (curr != NULL) {
			if (curr->student.getStudentId() == studentId) {
				size = curr->student.getSize();
				for (int i = 1; i < size+1; i++) {
					ids[i] = curr->student.showBookId(i);
				}
				break;
			}
			else {
				curr = curr->next;
			}
		}

		for (int i = 1; i < size+1; i++) {
			returnBook(ids[i]);
		}
	}

	if (!isExistStudent(studentId)) {
		cout << "Student " << studentId << " does not exist" << endl;
	}
	//If there is only one item and we want to delete that
	else if (sizeStudent == 1) {
		delete headStudent;
		headStudent = NULL;
		sizeStudent--;
		cout << "Student " << studentId << " has been deleted" << endl;
	}
	//Check whether first student is the one we are looking for
	else if ((headStudent->student).getStudentId() == studentId) {
		Node* tmp = headStudent;
		headStudent = headStudent->next;
		delete tmp;
		sizeStudent--;
		cout << "Student " << studentId << " has been deleted" << endl;
	}
	else {
		Node* curr = headStudent;
		for (int i = 1; i < sizeStudent; i++) {
			if (((curr->next)->student).getStudentId() == studentId) {
				if (i == sizeStudent - 1) { //deleting the last item of the list	
					delete tailStudent;
					curr->next = NULL;
					tailStudent = curr;
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
		sizeStudent--;
		cout << "Student " << studentId << " has been deleted" << endl;
	}
}

// A method for borrowing a book. It changes the book's status and lastTakerId
void LibrarySystem::checkoutBook(const int bookId, const int studentId) {
	if (!isExistBook(bookId)) {
		cout << "Book " << bookId << " does not exist for checkout" << endl;
	}
	else if (!isExistStudent(studentId)) {
		cout << "Student " << studentId << " does not exist for checkout" << endl;
	}
	else {
		string title;
		int year;
		BookNode* curr = headBook;

		//Find the book's title and year. Then change the book's status to false (not available)
		while (curr != NULL) {
			if (curr->book.getId() == bookId) {
				if (curr->book.getStatus() == false) {
					cout << "Book " << bookId << " has been already checked out by another student" << endl;
				}
				else {
					title = curr->book.getTitle();
					year = curr->book.getYear();
					curr->currentTakerId = studentId;

					//Change student list
					Node* curr2 = headStudent;
					while (curr2 != NULL) {
						if (curr2->student.getStudentId() == studentId) {
							curr2->student.borrowBook(bookId, title, year);
							curr->book.changeStatus(false);

							cout << "Book " << bookId << " has been checked out by student " << studentId << endl;
							break;
						}
						else {
							curr2 = curr2->next;
						}
					}
				}
				break;
			}
			else {
				curr = curr->next;
			}
		}
	}
}

void LibrarySystem::returnBook(int bookId) {
	if (!isExistBook(bookId)) {
		cout << "Book " << bookId << " has not been checked out" << endl;
	}
	else {
		string title;
		int year;
		int studentId;
		BookNode* curr = headBook;

		//Find the book from book list
		while (curr != NULL) {
			if (curr->book.getId() == bookId) {
				if (curr->book.getStatus() == true) {
					cout << "Book " << bookId << " has not been checked out" << endl;
					break;
				}
				else {
					// Get the current student that holds this book
					studentId = curr->currentTakerId;
					Node* curr2 = headStudent;
					while (curr2 != NULL) {
						if (curr2->student.getStudentId() == studentId) {
							curr2->student.returnBorrowedBook(bookId);
							curr->currentTakerId = 0;
							curr->book.changeStatus(true);

							cout << "Book " << bookId << " has been returned" << endl;
							break;
						}
						else {
							curr2 = curr2->next;
						}
					}
				}
				break;
			}
			else {
				curr = curr->next;
			}
		}
	}
}

void LibrarySystem::showAllBooks() {
	cout << "Book id\tBook name\t\tYear\tStatus" << endl;

	BookNode* curr = headBook;
	while (curr != NULL) {
		cout << curr->book.getId() << "\t";
		cout << curr->book.getTitle() << "\t";

		//If book title is short add another tab to make the table readible
		if (curr->book.getTitle().length() < 6) {
			cout << "\t";
		}
		if (curr->book.getTitle().length() < 12) {
			cout << "\t";
		}
		cout << curr->book.getYear() << "\t";
		if (curr->book.getStatus() == true) {
			cout << "Not checked out" << endl;
		}
		else {
			cout << "Checked out by student " << curr->currentTakerId << endl;
		}
		curr = curr->next;
	}
}

bool LibrarySystem::isExistBook(const int bookId) const {
	if (sizeBook == 0) {
		return false;
	}
	else {
		BookNode* curr = headBook;
		while (curr != NULL) {
			if ((curr->book).getId() == bookId)
				return true;
			else
				curr = curr->next;
		}
		return false;
	}
}

bool LibrarySystem::isExistStudent(const int studentId) const {
	if (sizeStudent == 0) {
		return false;
	}
	else {
		Node* curr = headStudent;
		while (curr != NULL) {
			if (curr->student.getStudentId() == studentId)
				return true;
			else
				curr = curr->next;
		}
		return false;
	}
}

void LibrarySystem::showBook(const int bookId) const {
	if (!isExistBook(bookId)) {
		cout << "Book " << bookId << " does not exist" << endl;
	}
	else {
		string title;
		int year;
		int currentTakerId;

		BookNode* curr = headBook;
		while (curr != NULL) {
			if (curr->book.getId() == bookId) {
				title = curr->book.getTitle();
				year = curr->book.getYear();
				currentTakerId = curr->currentTakerId;
				break;
			}
			else {
				curr = curr->next;
			}
		}
		cout << bookId << "\t";
		cout << title << "\t";
		if (title.length() < 6) {
			cout << "\t";
		}
		cout << year << "\t";
		if (currentTakerId == 0) {
			cout << "Not checked out" << endl;
		}
		else {
			cout << "Checked out by student " << currentTakerId;
		}
	}
}

void LibrarySystem::showStudent(const int studentId) const {
	if (!isExistStudent(studentId)) {
		cout << "Student " << studentId << " does not exist" << endl;
	}
	else {
		Node* curr = headStudent;
		while (curr != NULL) {
			if (curr->student.getStudentId() == studentId) {
				curr->student.showStudentInfo();
				break;
			}
			else {
				curr = curr->next;
			}
		}
	}
}