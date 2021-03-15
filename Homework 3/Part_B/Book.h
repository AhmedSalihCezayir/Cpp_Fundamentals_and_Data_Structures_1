//Ahmed Salih Cezayir 21802918 Sec03
#ifndef _BOOK_H
#define _BOOK_H

#include <string>
using namespace std;

class Book {
public:
	Book(int id, string title, int year);
	Book();

	void setId(int newId);
	void setTitle(string newTitle);
	void setYear(int newYear);
	void changeStatus(bool status);

	int getId();
	string getTitle();
	int getYear();
	bool getStatus();

	Book& operator=(const Book& right);

private:
	int id;
	string title;
	int year;
	bool status;
};

#endif

