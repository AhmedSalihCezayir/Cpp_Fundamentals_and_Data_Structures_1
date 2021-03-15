//Ahmed Salih Cezayir 21802918 Sec03
#include "Book.h"

Book::Book(int nId, string nTitle, int nYear) {
	id = nId;
	title = nTitle;
	year = nYear;
	status = true;
}

Book::Book() {
	id = 0;
	title = "";
	year = 0;
	status = true;
}

void Book::setId(int nId) {
	id = nId;
}

void Book::setTitle(string nTitle) {
	title = nTitle;
}

void Book::setYear(int nYear) {
	year = nYear;
}

void Book::changeStatus(bool nStatus) {
	status = nStatus;
}

int Book::getId() {
	return id;
}

string Book::getTitle() {
	return title;
}

int Book::getYear() {
	return year;
}

bool Book::getStatus() {
	return status;
}

Book& Book::operator=(const Book& right) {
	if (&right != this) {
		id = right.id;
		title = right.title;
		year = right.year;
		status = right.status;
	}
	return *this;
}