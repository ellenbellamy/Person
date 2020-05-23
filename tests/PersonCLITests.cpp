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
		"    help				--- вывести на экран список команд\n"
		"    clear				--- очистить список\n"
		"    load <filename>	--- добавить список из файла\n"
		"    save <filename>	--- сохранить список в файле\n"
		"    add				--- добавить элемент (переходит в режим ввода, начинающийс€ с \n"
		"    sort				--- отсортировать\n"
		"    find <услови€>		--- вывести на экран элементы, удовлетвор€ющие услови€м\n"
		"    delete <услови€>	--- удалить элементы, удовлетвор€ющие услови€м\n"
		"    exit				--- завершить работу и выйти\n"
		"    birthday			--- вывести на экран людей, у которых ближайший ƒ–\n"
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
		"    help				--- вывести на экран список команд\n"
		"    clear				--- очистить список\n"
		"    load <filename>	--- добавить список из файла\n"
		"    save <filename>	--- сохранить список в файле\n"
		"    add				--- добавить элемент (переходит в режим ввода, начинающийс€ с \n"
		"    sort				--- отсортировать\n"
		"    find <услови€>		--- вывести на экран элементы, удовлетвор€ющие услови€м\n"
		"    delete <услови€>	--- удалить элементы, удовлетвор€ющие услови€м\n"
		"    exit				--- завершить работу и выйти\n"
		"    birthday			--- вывести на экран людей, у которых ближайший ƒ–\n"

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

		ќпределить в функции main интерпретатор командной строки, реализующий команды :
		- help --- вывести на экран список команд
		- clear --- очистить список
		- load <filename> --- добавить список из файла
		- save <filename> --- сохранить список в файле
		- add(переходит в режим ввода, начинающийс€ с ">") --- добавить элемент
		- sort --- отсортировать
		- find <услови€> --- вывести на экран элементы, удовлетвор€ющие услови€м
		- delete <услови€> --- удалить элементы, удовлетвор€ющие услови€м
		- exit --- завершить работу и выйти.
		- birthday --- вывести на экран людей, у которых ближайший ƒ–

*/

