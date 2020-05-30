#include "PersonCLI.h"
#include <fstream>
#include <sstream>

void PersonCLI::start(istream& input, ostream& output) {
	string line;
	while (getline(input, line)) {
		output << process(line);
	}
}

PersonList& PersonCLI::getPersons() {
	return persons;
}

void PersonCLI::setPersons(const PersonList& p) {
	persons = p;
}

string PersonCLI::process(const string& commandString) {

	istringstream commandStream = istringstream(commandString);


	if (adding) {
		if (commandStream.rdbuf()->in_avail() == 0) {
			adding = false;
			return "Added";
		}

		Person person;
		commandStream >> person;
		persons.add(person);
		return ">";
	}

	string command;
	commandStream >> command;

	if (command == "help") {
		return
			"    help				--- ������� �� ����� ������ ������\n"
			"    clear				--- �������� ������\n"
			"    load <filename>	--- �������� ������ �� �����\n"
			"    save <filename>	--- ��������� ������ � �����\n"
			"    add				--- �������� ������� (��������� � ����� �����, ������������ � \n"
			"    sort				--- �������������\n"
			"    find <�������>		--- ������� �� ����� ��������, ��������������� ��������\n"
			"    delete <�������>	--- ������� ��������, ��������������� ��������\n"
			"    exit				--- ��������� ������ � �����\n"
			"    birthday			--- ������� �� ����� �����, � ������� ��������� ��\n";
	}

	if (command == "exit") {
		return "Finished\n";
	}

	if (command == "load") {
		string fileName;
		commandStream >> fileName;
		ifstream f(fileName);
		f >> persons;
		return "Read from: " + fileName;
	}

	if (command == "save") {
		string fileName;
		commandStream >> fileName;
		ofstream f(fileName);
		f << persons;
		return "Write to: " + fileName;
	}

	if (command == "add") {
		adding = true;
		return ">";
	}

	if (command == "sort") {
		persons.sort();
		return "Sorted";
	}

	if (command == "find") {
		ostringstream response;
		response << "Found:\n";

		Person condition;
		commandStream >> condition;

		list<Person> found = persons.select(condition);
		for (Person p : found) {
			response << p << "\n";
		}

		return response.str();
	}

	if (command == "delete") {
		Person condition;
		commandStream >> condition;

		persons.remove(condition);

		return "Deleted\n";
	}

	if (command == "birthday") {
		ostringstream response;
		response << "Next celebrant: ";

		response << get<0>(persons.nextCelebrant());

		response << "\n";
		return response.str();
	}


	

	return "ERROR: Unknown command: " + commandString + "\n";
}
