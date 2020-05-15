#include "Person.h"

#include <iostream>
#include <sstream>

#include <compare>

#include <ctime>
#include <iomanip>



Person::Person() {
	lastName = "";
	firstName = std::nullopt;
	middleName = "";
	birthdayTm = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	birthday = 0;
	phone = "";
}

Person::Person(
	const optional<string>& firstNameStringOrNull,
	const optional<string>& middleNameStringOrNull,
	const optional<string>& lastNameStringOrNull,
	const optional<string>& birthdayStringOrNull,
	const optional<string>& phoneStringOrNull) {
	firstName = firstNameStringOrNull;
	lastName = lastNameStringOrNull.has_value() ? lastNameStringOrNull.value() : NULL;
	middleName = middleNameStringOrNull.has_value() ? middleNameStringOrNull.value() : NULL;
	if (birthdayStringOrNull.has_value()) {
		birthdayTm = readDateTm(birthdayStringOrNull.value());
		birthday = mktime(&birthdayTm);
	}
	phone = phoneStringOrNull.has_value() ? phoneStringOrNull.value() : NULL;
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
	return firstName.has_value() ? firstName.value() : "";
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
		<< person.getFirstName() << delimiter
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
	string fn; 

	in >> fn //>> skip
		>> person.middleName //>> skip
		>> person.lastName //>> skip
		>> person.birthday //>> skip
		>> person.phone;

	person.firstName = fn;

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
	time_t dateOnly = dateAndTime - dateAndTime % (60 * 60 * 24);

	struct tm nextBirthdayTm = birthdayTm;

	nextBirthdayTm.tm_year = tm.tm_year;
	time_t nextBirthday = mktime(&nextBirthdayTm);

	if (nextBirthday < dateOnly) {
		nextBirthdayTm.tm_year += 1;
		nextBirthday = mktime(&nextBirthdayTm);
	}

	return difftime(nextBirthday, dateOnly) / ((double)60 * 60 * 24);
}

bool Person::check(const Person& condition) const {
	return
		lastName == condition.lastName
		&& condition.firstName.has_value() ? condition.firstName.value() == firstName.value() : true
		&& middleName == condition.middleName
		&& birthday == condition.birthday
		&& phone == condition.phone;
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
