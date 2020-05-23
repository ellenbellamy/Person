#include "PersonCLI.h"

#include <sstream>

void PersonCLI::start(istream& input, ostream& output) {
	string line;
	while (getline(input, line)) {
		output << process(line);
	}
}

PersonList PersonCLI::getPersons() {
	return persons;
}


string PersonCLI::process(const string& commandString) {
	if (commandString == "help") {
		return
			"    help				--- вывести на экран список команд\n"
			"    clear				--- очистить список\n"
			"    load <filename>	--- добавить список из файла\n"
			"    save <filename>	--- сохранить список в файле\n"
			"    add				--- добавить элемент (переходит в режим ввода, начинающийс€ с \n"
			"    sort				--- отсортировать\n"
			"    find <услови€>		--- вывести на экран элементы, удовлетвор€ющие услови€м\n"
			"    delete <услови€>	--- удалить элементы, удовлетвор€ющие услови€м\n"
			"    exit				--- завершить работу и выйти\n"
			"    birthday			--- вывести на экран людей, у которых ближайший ƒ–\n";
	}
	if (commandString == "exit") {
		return "Finished\n";
	}

	return "ERROR: Unknown command: " + commandString + "\n";
}
