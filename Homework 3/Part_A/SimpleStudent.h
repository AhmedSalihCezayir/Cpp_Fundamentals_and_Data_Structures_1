//Ahmed Salih Cezayir 21802918 Sec03
#ifndef _SIMPLESTUDENT_H
#define _SIMPLESTUDENT_H

#include <string>
using namespace std;

class Student {
public:
	Student(int id, string name);
	Student();

	void setSimpleName(string name);
	void setSimpleStudentId(int studentId);

	string getSimpleName();
	int getSimpleStudentId();

	Student& operator=(const Student& right);

private:
	string name;
	int studentId;
};

#endif
