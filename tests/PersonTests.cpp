#include "pch.h"
#include "../Person.h"

namespace PersonTesting {

	class PersonTests : public ::testing::Test
	{
	protected:
		Person person;

		void SetUp() {
			person = Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100");
		}
	};

	TEST_F(PersonTests, HasFirstName) {
		EXPECT_EQ(person.getFirstName(), "Anna");
	}

	TEST_F(PersonTests, HasLastName) {
		EXPECT_EQ(person.getLastName(), "Smith");
	}

	TEST_F(PersonTests, HasMiddleName) {
		EXPECT_EQ(person.getMiddleName(), "Mary");
	}

	TEST_F(PersonTests, WritesItself) {
		EXPECT_EQ("Anna Mary Smith 978296400 +98765432100", (std::stringstream() << person).str());
	}

	TEST_F(PersonTests, Equality) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"));
	}

	TEST_F(PersonTests, EqualityIgnoresPhone) {
		EXPECT_EQ(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+9 876 543 21 01"));
	}

	TEST_F(PersonTests, Inequality) {
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

	TEST_F(PersonTests, LessByBirthday) {
		EXPECT_LT(
			Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100"),
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100"));
	}

	TEST_F(PersonTests, LessIgnoresPhone) {
		EXPECT_FALSE(
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")
			<
			Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432101"));
	}


	//TEST(Person, ThrowsExceptionOnWrongBirthdayFormat) {
	//	Person p = Person("Anna", "Mary", "Smith", "2001-02-31", "+98765432100");
	//	EXPECT_THROW( p /*= Person("Anna", "Mary", "Smith", "2001-02-29", "+98765432100")*/, WrongDateFormat);
	//}

	TEST_F(PersonTests, ReadsItself) {
		Person p;
		std::stringstream() << person >> p;

		EXPECT_EQ(person, p);
	}

	TEST_F(PersonTests, Assignment) {
		Person p;
		p = person;
		EXPECT_EQ(person, p);
	}

	TEST_F(PersonTests, Copy) {
		Person p(person);
		EXPECT_EQ(person, p);
	}

	TEST_F(PersonTests, DaysUntilBirthday) {
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


	TEST_F(PersonTests, DaysUntilBirthdayFromToday) {
		person.setBirthday(time(NULL));
		EXPECT_EQ(person.daysUntilBirthday(), 0);

		person.setBirthday(time(NULL) + ( 1 * 60 * 60 * 24 ));
		EXPECT_EQ(person.daysUntilBirthday(), 1);

		person.setBirthday(time(NULL) - (1 * 60 * 60 * 24));
		EXPECT_EQ(person.daysUntilBirthday(), 365 - 1);
	}



	TEST_F(PersonTests, Check) {
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));

		EXPECT_FALSE(person.check(Person("Anna_", "Mary", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary_", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith_", "2001-01-01", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith", "2001-01-02", "+98765432100")));
		EXPECT_FALSE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432101")));

		EXPECT_TRUE(person.check(Person(nullopt, "Mary", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", nullopt, "Smith", "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", nullopt, "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", nullopt, "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", nullopt)));
		EXPECT_TRUE(person.check(Person(nullopt, "Mary", "Smith", "2001-01-01", nullopt)));
		EXPECT_TRUE(person.check(Person("Anna", "Mary", "Smith", "2001-01-01", "+98765432100")));
		EXPECT_TRUE(person.check(Person("Anna", nullopt, nullopt, nullopt, "+98765432100")));
		EXPECT_TRUE(person.check(Person(nullopt, nullopt, nullopt, nullopt, nullopt)));
	}

	Person readPersonFrom(stringstream);

	TEST_F(PersonTests, ReadsCondition) {
		EXPECT_EQ(readPersonFrom(stringstream("* Mary Smith 978296400 +98765432100")), Person(nullopt, "Mary", "Smith", "2001-01-01", "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna * Smith 978296400 +98765432100")), Person("Anna", nullopt, "Smith", "2001-01-01", "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna Mary * 978296400 +98765432100")), Person("Anna", "Mary", nullopt, "2001-01-01", "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna Mary Smith * +98765432100")), Person("Anna", "Mary", "Smith", nullopt, "+98765432100"));
		EXPECT_EQ(readPersonFrom(stringstream("Anna Mary Smith 978296400 *")), Person("Anna", "Mary", "Smith", "2001-01-01", nullopt));
	}



	Person readPersonFrom(stringstream ss) {
		Person p;
		ss >> p;
		return p;
	}
}