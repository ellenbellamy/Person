#include <iostream>
#include "Person.h"

Person::Person(const string& firstNameString, const string& middleNameString, const string& lastNameString)
{
	firstName = firstNameString;
	lastName = lastNameString;
	middleName = middleNameString;
}

string Person::getFirstName() {
	return firstName;
}

string Person::getLastName() {
	return lastName;
}

string Person::getMiddleName() {
	return middleName;
}

ostream& operator<<(ostream& out, const Person& person)
{
	out << person.firstName << " " << person.middleName << " " << person.lastName;
	return out;
}

