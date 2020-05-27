#include "pch.h"
#include "../Person.h"

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
		EXPECT_EQ("Anna Mary Smith 978296400 +98765432100", (std::stringstream() << person).str());
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
		Person p;
		std::stringstream() << person >> p;

		EXPECT_EQ(person, p);
	}

	TEST(Person, Assignment) {
		Person p;
		p = person;
		EXPECT_EQ(person, p);
	}

	TEST(Person, Copy) {
		Person p(person);
		EXPECT_EQ(person, p);
	}

	TEST(Person, DaysUntilBirthday) {
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2001-01-01")), 0);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2000-12-31")), 1);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2000-12-30")), 2);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2000-01-02")), 365);

		EXPECT_EQ(person.daysUntilBirthday(convertTime(readDate("2000-12-31") + 1)), 1);
		EXPECT_EQ(person.daysUntilBirthday(convertTime(readDate("2000-12-31") + 24 * 60 * 60)), 0);

		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2002-01-01")), 0);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2001-12-31")), 1);

		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-01-01")), 0);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-12-31")), 1);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-12-30")), 2);
		EXPECT_EQ(person.daysUntilBirthday(readDateTm("2020-01-02")), 365);
	}

	TEST(Person, Check) {
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));

		EXPECT_FALSE(person.check(Person("Anna_", "Mary", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary_", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith_", "2001-01-01", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432101")));

		EXPECT_TRUE(person.check(Person({}, "Mary", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", {}, "Smith", "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", {}, "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", {}, "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", {})));
		EXPECT_TRUE(person.check(Person({}, "Mary", "Smith", "2001-01-01", {})));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", {}, {}, {}, "+98765432100")));
		EXPECT_TRUE(person.check(Person({}, {}, {}, {}, {})));
	}


	Person readPersonFrom(stringstream ss) {
		Person p;
		ss >> p;
		return p;
	}

	TEST(Person, ReadsCondition) {
		EXPECT_EQ(readPersonFrom(stringstream("* Mary Smith 978296400 +98765432100")), Person({}, "Mary", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna * Smith 978296400 +98765432100")), Person("Anna", {}, "Smith", "2001-01-01", "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna Mary * 978296400 +98765432100")), Person("Anna", "Mary", {}, "2001-01-01", "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna Mary Smith * +98765432100")), Person("Anna", "Mary", "Smith", {}, "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna Mary Smith 978296400 *")), Person("Anna", "Mary", "Smith", "2001-01-01", {}));
	}


}