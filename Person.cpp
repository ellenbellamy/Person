#include "Person.h"

#include <iostream>
#include <sstream>

#include <compare>

#include <ctime>
#include <iomanip>


Person::Person() {
	lastName = "";
	firstName = "";
	middleName = "";
	birthday = -1;
	phone = "";
}

Person::Person(
	const string& firstNameString,
	const string& middleNameString,
	const string& lastNameString,
	const string& birthdayString,
	const string& phoneString) {
	firstName = firstNameString;
	lastName = lastNameString;
	middleName = middleNameString;
	birthday = readDate(birthdayString);
	phone = phoneString;
}

Person::Person(const Person& aPerson) {
	firstName = aPerson.firstName;
	lastName = aPerson.lastName;
	middleName = aPerson.middleName;

	birthday = aPerson.birthday;

	phone = aPerson.phone;
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

time_t Person::getBirthday() const
{
	return birthday;
}


bool Person::operator==(const Person& another) const {
	return
		lastName == another.lastName
		&& firstName == another.firstName
		&& middleName == another.middleName
		&& birthday == another.birthday;
}

bool operator<(const Person& a, const Person& another) {
	if (a.lastName < another.lastName) return true;
	if (a.lastName > another.lastName) return false;

	if (a.firstName < another.firstName) return true;
	if (a.firstName > another.firstName) return false;

	if (a.middleName < another.middleName) return true;
	if (a.middleName > another.middleName) return false;

	return a.birthday > another.birthday;
}

const unsigned char delimiter = ' ';

ostream& operator<<(ostream& out, const Person& person)
{
	return out
		<< person.firstName << delimiter
		<< person.middleName << delimiter
		<< person.lastName << delimiter
		<< person.birthday << delimiter
		<< person.phone;
}

istream& operator>>(istream& in, Person& person)
{
	//string buffer; 
	//in >> buffer;

	//istringstream iss(buffer);

	in >> person.firstName //>> skip
		>> person.middleName //>> skip
		>> person.lastName //>> skip
		>> person.birthday //>> skip
		>> person.phone;

	return in;
}

Person& Person::operator=(const Person& aPerson) {
	firstName = aPerson.firstName;
	lastName = aPerson.lastName;
	middleName = aPerson.middleName;
	birthday = aPerson.birthday;
	phone = aPerson.phone;
	return *this;
}

int Person::daysUntilBirthday(const time_t& dateAndTime) {
	time_t dateOnly = dateAndTime - dateAndTime % (60L * 60 * 24);

	//tm * tm = localtime(&dateOnly);

	return difftime(birthday, dateOnly) / (60L * 60 * 24);
}

time_t readDate(const string& dateString) {
	struct tm date = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	istringstream ss = istringstream(dateString);
	ss >> get_time(&date, "%Y-%m-%d");

	if (ss.fail()) {
		throw WrongDateFormat();
	}

	time_t t = mktime(&date);
	return t;
}
