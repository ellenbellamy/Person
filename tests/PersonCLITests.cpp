#include "pch.h"

#include "../PersonCLI.h"

#include <fstream>


class PersonCLITests : public ::testing::Test
{
protected:
	PersonCLI cli;

	//void TearDown() {
	//	persons.clear();
	//}
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




/*
string readUserInput(std::istream& input)
{
	string command;
	cout << ":";
	input >> command;
	return command;
}

TEST(Some, Test) {
	//// in production code pass std::cin
	//std::cout << "readUserInput from std::cin: " << readUserInput(std::cin) << std::endl;

	//// in testing pass some mock data from the file (or whatever)
	//std::cout << "readUserInput from ifs: " << readUserInput(ifs) << std::endl;

	cout << "Processed command: " << readUserInput(ss) << std::endl;
}
*/

//TEST_F(PersonCLITests, AddingElement) {
//	persons.add(Person());
//
//	EXPECT_FALSE(persons.isEmpty());
//}

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

