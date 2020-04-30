#pragma once

#include <string>
using namespace std;

class Person
{
public:

	Person(const string& firstNameString, const string& middleNameString, const string& lastNameString);

	string getFirstName();

	string getLastName();

	string getMiddleName();

	friend ostream& operator<<(ostream& out, const Person& person);

private:
	string firstName;
	string middleName;
	string lastName;
};

