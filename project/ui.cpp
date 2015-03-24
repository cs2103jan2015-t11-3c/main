#include <iostream>
#include <vector>
#include <sstream>
#include "logic.h"
#include "parser.h"
#include <fstream> 
#include <ctime>

using namespace std;

string getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readinput(vector<task> &);


int main(int argc, char *argv[]) {
	vector<task> toDoList;
	logic function;

	getTextFileName(argc, argv);
	function.readToDoListFromTextFile(getTextFileName(argc, argv), toDoList);
	printWelcomeMessage();
	readinput(toDoList);

	return 0;
}

string getTextFileName(const int argc, char *argv[]) {
	argc < 2 ? fileName=DEFAULT_SAVE_FILENAME : fileName=argv[FILE_NAME_ARG_NUMBER];
	return fileName;
}

void printWelcomeMessage() {
	cout << endl << "Welcome to Happy Calendar! " << fileName << " is ready for use" << endl;
}

void readinput(vector<task> &toDoList){
	string command, description;
	logic function;

	while(command!="exit"){
		cout << endl << "command: ";
		cin >> command;
		getline(cin,description);
		function.executeCommand(command, description, toDoList);
	};
}
