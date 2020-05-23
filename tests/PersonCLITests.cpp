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
		//remove(personsFileName);
	}
};


TEST_F(PersonCLITests, Help) {

	stringstream
		input,
		output;

	input << "help\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
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

	stringstream
		input,
		output;

	input << "abracadabra\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
		"ERROR: Unknown command: abracadabra\n"
	);
}

TEST_F(PersonCLITests, Exit) {

	stringstream
		input,
		output;

	input << "exit\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
		"Finished\n"
	);
}


TEST_F(PersonCLITests, CommandSquence) {

	stringstream
		input,
		output;

	input
		<< "help\n"
		<< "abracadabra\n"
		<< "exit\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
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

	stringstream
		input,
		output;

	input << "abracadabra\n";

	cli.start(input, output);

	EXPECT_EQ(
		output.str(),
		"ERROR: Unknown command: abracadabra\n"
	);
}

TEST_F(PersonCLITests, PersonsIsEmptyByDefault) {
	ASSERT_TRUE(cli.getPersons().isEmpty());
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

