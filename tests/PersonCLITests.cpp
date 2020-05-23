#include "pch.h"

#include "../PersonCLI.h"

#include <fstream>
#include <stdio.h>

class PersonCLITests : public ::testing::Test
{
protected:
	PersonCLI cli;

	const char* const personsFileName = "persons.list";

	void SetUp() {
		std::ofstream o(personsFileName);

		PersonList personList({
				Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("444", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("333", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("555", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("222", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("777", "Mary", "Smith", "2001-01-01", "+98765432100"),
				Person("222", "Mary", "Smith", "2001-01-01", "+98765432100")
			});

		o << personList << std::endl;
	}

	void TearDown() {
		remove(personsFileName);
	}


	ostringstream executeCommandsFrom(istream& input) {
		ostringstream output;
		cli.start(input, output);
		return output;
	}

};



TEST_F(PersonCLITests, Help) {
	EXPECT_EQ(
		executeCommandsFrom(istringstream("help\n")).str(),
		"    help				--- ������� �� ����� ������ ������\n"
		"    clear				--- �������� ������\n"
		"    load <filename>	--- �������� ������ �� �����\n"
		"    save <filename>	--- ��������� ������ � �����\n"
		"    add				--- �������� ������� (��������� � ����� �����, ������������ � \n"
		"    sort				--- �������������\n"
		"    find <�������>		--- ������� �� ����� ��������, ��������������� ��������\n"
		"    delete <�������>	--- ������� ��������, ��������������� ��������\n"
		"    exit				--- ��������� ������ � �����\n"
		"    birthday			--- ������� �� ����� �����, � ������� ��������� ��\n"
	);
}

TEST_F(PersonCLITests, UnknownCommand) {
	EXPECT_EQ(
		executeCommandsFrom(istringstream("abracadabra\n")).str(),
		"ERROR: Unknown command: abracadabra\n"
	);
}

TEST_F(PersonCLITests, Exit) {
	EXPECT_EQ(
		executeCommandsFrom(istringstream("exit\n")).str(),
		"Finished\n"
	);
}

TEST_F(PersonCLITests, CommandSquence) {
	EXPECT_EQ(
		executeCommandsFrom(istringstream(
			"help\n"
			"abracadabra\n"
			"exit\n"
		)).str(),
		"    help				--- ������� �� ����� ������ ������\n"
		"    clear				--- �������� ������\n"
		"    load <filename>	--- �������� ������ �� �����\n"
		"    save <filename>	--- ��������� ������ � �����\n"
		"    add				--- �������� ������� (��������� � ����� �����, ������������ � \n"
		"    sort				--- �������������\n"
		"    find <�������>		--- ������� �� ����� ��������, ��������������� ��������\n"
		"    delete <�������>	--- ������� ��������, ��������������� ��������\n"
		"    exit				--- ��������� ������ � �����\n"
		"    birthday			--- ������� �� ����� �����, � ������� ��������� ��\n"

		"ERROR: Unknown command: abracadabra\n"

		"Finished\n"
	);
}


TEST_F(PersonCLITests, Load) {
	EXPECT_EQ(
		executeCommandsFrom(istringstream("abracadabra\n")).str(),
		"ERROR: Unknown command: abracadabra\n"
	);
}

TEST_F(PersonCLITests, PersonsIsEmptyByDefault) {
	ASSERT_TRUE(cli.getPersons().isEmpty());
}


TEST_F(PersonCLITests, Clear) {
	cli.getPersons().add(Person("111", "Mary", "Smith", "2001-01-01", "+98765432100"));
	ASSERT_FALSE(cli.getPersons().isEmpty());

	executeCommandsFrom(istringstream("clear\n"));
	ASSERT_FALSE(cli.getPersons().isEmpty());
}




/*

		���������� � ������� main ������������� ��������� ������, ����������� ������� :
		- help --- ������� �� ����� ������ ������
		- clear --- �������� ������
		- load <filename> --- �������� ������ �� �����
		- save <filename> --- ��������� ������ � �����
		- add(��������� � ����� �����, ������������ � ">") --- �������� �������
		- sort --- �������������
		- find <�������> --- ������� �� ����� ��������, ��������������� ��������
		- delete <�������> --- ������� ��������, ��������������� ��������
		- exit --- ��������� ������ � �����.
		- birthday --- ������� �� ����� �����, � ������� ��������� ��

*/

