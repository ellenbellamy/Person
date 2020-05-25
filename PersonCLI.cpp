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

	string command;
	istringstream commandStream = istringstream(commandString);
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

	if (command == "sort") {
		persons.sort();
		return "Sorted";
	}

	return "ERROR: Unknown command: " + commandString + "\n";
}
