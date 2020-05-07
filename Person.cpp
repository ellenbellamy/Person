#include "Person.h"

#include <iostream>
#include <sstream>

#include <compare>

#include <ctime>
#include <iomanip>

std::time_t readDate(const string&);

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

	//struct std::tm birthday_tm = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	//(istringstream(birthdayString)) >> std::get_time(&birthday_tm, "%Y-%m-%d");
	//birthday = mktime(&birthday_tm);
	birthday = readDate(birthdayString);

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


//constexpr bool _Less(const tuple<_Other...>& _Right) const {
//	return _Myfirst._Val < _Right._Myfirst._Val
//		|| (!(_Right._Myfirst._Val < _Myfirst._Val) && _Mybase::_Less(_Right._Get_rest()));
//}

//std::strong_ordering Person::operator<=>(const Person& that) const {
//	auto cmp1 = birthday <=> that.birthday;
//	tuple s("abc");
//
//	if (std::strong_ordering cmp = lastName <=> that.lastName; cmp != 0) {
//		return cmp; 
//	}
//	if (auto cmp = firstName <=> that.firstName; cmp != 0) {
//		return cmp;
//	}
//	return tax_id <=> that.tax_id;
//}


ostream& operator<<(ostream& out, const Person& person)
{
	out << person.firstName << " " << person.middleName << " " << person.lastName;
	return out;
}


std::time_t readDate(const string& dateString) {
	struct std::tm date = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	istringstream ss = istringstream(dateString);
	ss >> std::get_time(&date, "%Y-%m-%d");

	if (ss.fail()) {
		throw WrongDateFormat();
	}

	time_t t = mktime(&date);
	return t;
}
