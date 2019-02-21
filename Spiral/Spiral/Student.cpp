#include "stdafx.h"
#include "Student.h"


Student::Student()
{
}

void Student::Run()
{
	cout << "Student Run" << endl;
}

void Student::Run(int a)
{
	cout << "Student Run" << a << endl;
}

Student::~Student()
{
}
