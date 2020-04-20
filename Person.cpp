#include <iostream>
#include "Person.h"

Person::Person(const string& firstNameString, const string& middleNameString, const string& lastNameString)
{
	firstName = firstNameString;
	lastName = lastNameString;
	middleName = middleNameString;
}

ostream& operator<<(ostream& out, const Person& person)
{
	out << person.firstName << " " << person.middleName << " " << person.lastName << std::endl;
	return out;
}

