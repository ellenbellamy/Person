#pragma once

#include <string>
using namespace std;

class Person
{
public:

	Person(const string& firstNameString, const string& middleNameString, const string& lastNameString);

	friend ostream& operator<<(ostream& out, const Person& person);

private:
	string firstName;
	string middleName;
	string lastName;
};

