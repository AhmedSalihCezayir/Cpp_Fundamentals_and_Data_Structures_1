//Ahmed Salih Cezayir 21802918 Sec03
#include "SimpleStudent.h"

Student::Student(int id, string n) {
	name = n;
	studentId = id;
}

Student::Student() {
	studentId = 0;
	name = "";
}

void Student::setSimpleName(string n) {
	name = n;
}

void Student::setSimpleStudentId(int id) {
	studentId = id;
}

string Student::getSimpleName() {
	return name;
}

int Student::getSimpleStudentId() {
	return studentId;
}

Student& Student::operator=(const Student& right) {
	if (&right != this) {
		studentId = right.studentId;
		name = right.name;
	}
	return *this;
}

