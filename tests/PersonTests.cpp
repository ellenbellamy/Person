#include "pch.h"
#include "../Person.h"
#include <ctime>

namespace PersonTesting {

	Person person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100");

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

		EXPECT_EQ("Anna Mary Smith 978296400 +98765432100", ss.str());
	}

	TEST(Person, Equality) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"));
	}

	TEST(Person, EqualityIgnoresPhone) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 01"));
	}

	TEST(Person, Inequality) {
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith_", "2001-01-01", "+98765432100"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary_", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna_", "Mary", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_NE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100"));
	}

	TEST(Person, LessByBirthday) {
		EXPECT_LT(  
			Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"));
	}

	TEST(Person, LessIgnoresPhone) {
		EXPECT_FALSE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100") 
			<
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432101"));
	}


	//TEST(Person, ThrowsExceptionOnWrongBirthdayFormat) {
	//	Person p = Person("Anna", "Mary", "Smith", "2001-02-31", "+98765432100");
	//	EXPECT_THROW( p /*= Person("Anna", "Mary", "Smith", "2001-02-29", "+98765432100")*/, WrongDateFormat);
	//}

	TEST(Person, ReadsItself) {

		std::stringstream ss;

		ss << person;
		
		Person p;
		ss >> p;

		EXPECT_EQ(person, p);
	}

}