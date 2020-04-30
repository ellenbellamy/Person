#include "pch.h"
#include "../Person.h"
#include <ctime>

namespace PersonTesting {

	Person person("Anna", "Mary", "Smith");
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

	//TEST(Person, ReadsItself) {
	//	EXPECT_EQ()
	//}

	TEST(Person, Dates) {
		struct std::tm birthday_tm = { 0, 0, 0, 27, 1, 101 };
		std::time_t birthday = std::mktime(&birthday_tm);

		struct std::tm date_tm = { 0, 0, 0, 26, 1, 101 };
		std::time_t date = std::mktime(&date_tm);


		EXPECT_EQ(std::difftime(birthday, date), 1 * 24 * 60 * 60);

	}
}