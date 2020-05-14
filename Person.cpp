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
	birthdayTm = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	birthday = 0;
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
	birthdayTm = readDateTm(birthdayString);
	birthday = mktime(&birthdayTm);
	phone = phoneString;
}

Person::Person(const Person& aPerson) {
	firstName = aPerson.firstName;
	lastName = aPerson.lastName;
	middleName = aPerson.middleName;

	birthday = aPerson.birthday;
	birthdayTm = aPerson.birthdayTm;  // Copy???

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

time_t Person::getBirthday() const {
	return birthday;
}

tm Person::getBirthdayTm() const {
	return birthdayTm;
}

bool Person::operator==(const Person& another) const {
	return
		lastName == another.lastName
		&& firstName == another.firstName
		&& middleName == another.middleName
		&& birthday == another.birthday;
}

bool operator<(const Person& left, const Person& right) {
	if (left.lastName < right.lastName) return true;
	if (left.lastName > right.lastName) return false;

	if (left.firstName < right.firstName) return true;
	if (left.firstName > right.firstName) return false;

	if (left.middleName < right.middleName) return true;
	if (left.middleName > right.middleName) return false;

	return left.birthday > right.birthday;
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

	person.birthdayTm = convertTime(person.birthday);

	return in;
}

Person& Person::operator=(const Person& aPerson) {
	firstName = aPerson.firstName;
	lastName = aPerson.lastName;
	middleName = aPerson.middleName;
	birthday = aPerson.birthday;
	birthdayTm = aPerson.birthdayTm;
	phone = aPerson.phone;
	return *this;
}

int Person::daysUntilBirthday(tm& tm) const {
	time_t dateAndTime = mktime(&tm);

	time_t dateOnly = dateAndTime - dateAndTime % (60L * 60 * 24);

	//tm * tm = localtime(&dateOnly);

	return difftime(birthday, dateOnly) / (60L * 60 * 24);
}

tm readDateTm(const string& dateString) {
	struct tm date = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	istringstream ss = istringstream(dateString);
	ss >> get_time(&date, "%Y-%m-%d");

	if (ss.fail()) {
		throw WrongDateFormat();
	}

	return date;
}

time_t readDate(const string& dateString) {
	return  mktime(&readDateTm(dateString));
}

tm convertTime(time_t t) {
	tm tm;
	localtime_s(&tm, &t);
	return tm;
}
