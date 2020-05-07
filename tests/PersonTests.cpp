#include "pch.h"
#include "../Person.h"
#include <ctime>

namespace PersonTesting {

	Person person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00");

	TEST(Person, HasFirstName) {
		EXPECT_EQ(person.getFirstName(), "Anna");
	}

	TEST(Person, HasLastName) {
		EXPECT_EQ(person.getLastName(), "Smith");
	}

	TEST(Person, HasMiddleName) {
		EXPECT_EQ(person.getMiddleName(), "Mary");
	}

	TEST(Person, WritesItself) {
		std::stringstream ss;

		ss << person;

		EXPECT_EQ("Anna Mary Smith", ss.str());
	}

	TEST(Person, Equality) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"));
	}

	TEST(Person, EqualityIgnoresPhone) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 01"));
	}

	TEST(Person, Inequality) {
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"),
			Person("Anna", "Mary", "Smith_", "2001-01-01", "+9 876 543 21 00"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"),
			Person("Anna", "Mary_", "Smith", "2001-01-01", "+9 876 543 21 00"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"),
			Person("Anna_", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"),
			Person("Anna", "Mary", "Smith", "2001-01-02", "+9 876 543 21 00"));
	}

	TEST(Person, LessByBirthday) {
		EXPECT_LT(
			new Person("Anna", "Mary", "Smith", "2001-01-02", "+9 876 543 21 00"),
			new Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 00"));
	}

	//TEST(Person, ThrowsExceptionOnWrongBirthdayFormat) {
	//	Person p = Person("Anna", "Mary", "Smith", "2001-02-31", "+9 876 543 21 00");
	//	EXPECT_THROW( p /*= Person("Anna", "Mary", "Smith", "2001-02-29", "+9 876 543 21 00")*/, WrongDateFormat);
	//}

	//TEST(Person, ReadsItself) {
	//	EXPECT_EQ()
	//}

	TEST(Person, Dates) {
		struct std::tm birthday_tm = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		(std::istringstream("2001-02-27")) >> std::get_time(&birthday_tm, "%Y-%m-%d");
		std::time_t birthday = std::mktime(&birthday_tm);

		struct std::tm date_tm = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		*new std::istringstream("2001-02-26") >> std::get_time(&date_tm, "%Y-%m-%d");
		std::time_t date = std::mktime(&date_tm);


		EXPECT_EQ(std::difftime(birthday, date), 1 * 24 * 60 * 60);
	}
}