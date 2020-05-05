#include "Person.h"

#include <iostream>
#include <sstream>

#include <compare>

#include <ctime>
#include <iomanip>


Person::Person(
	const string& firstNameString,
	const string& middleNameString,
	const string& lastNameString,
	const string& birthdayString,
	const string& phoneString)
{
	firstName = firstNameString;
	lastName = lastNameString;
	middleName = middleNameString;

	struct std::tm birthday_tm = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	(istringstream(birthdayString)) >> std::get_time(&birthday_tm, "%Y-%m-%d");
	birthday = mktime(&birthday_tm);

	phone = phoneString;
}

string Person::getFirstName() const {
	return firstName;
}

string Person::getLastName() const {
	return lastName;
}

string Person::getMiddleName() const {
	return middleName;
}

//bool Person::operator==(const Person&) const {
//	return
//		lastNa
//}

ostream& operator<<(ostream& out, const Person& person)
{
	out << person.firstName << " " << person.middleName << " " << person.lastName;
	return out;
}


std::time_t readDate(const string& dateString) {
	struct std::tm date = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	(istringstream(dateString)) >> std::get_time(&date, "%Y-%m-%d");

	//if()

	return mktime(&date);
}
