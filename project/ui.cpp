//main

#include "logic.h"
#include "Task.h"
#include "undo.h"
#include "default.h"
#include "storage.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <ctime>
#include <windows.h>

string fileName = "";

string getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readinput(vector<task> &,storage * );
void showDefaultTaskList(vector<task> &, vector<task> &, vector<task> &, vector<task> &);
void printSpace(int);
void defaultExecution(string ,storage *,string ,vector<task> &,vector<undo> );

int main(int argc, char *argv[]) {
	vector<task> toDoList;
	logic function;
	storage *store=storage::getInstance();
	
	toDoList = store->readToDoListFromTextFile(getTextFileName(argc, argv));
	printWelcomeMessage();
	readinput(toDoList,store);     

	return 0;
}

string getTextFileName(const int argc, char *argv[]) {
	argc < 2 ? fileName=DEFAULT_SAVE_FILENAME : fileName=argv[FILE_NAME_ARG_NUMBER];
	std::cout << fileName << "loaded succesfully" << endl;
	return fileName;
}

void printWelcomeMessage() {
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "*******************************************************************************" << endl;
	cout<<">>(^_^)>>                                                            << (^_^)<<";
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << endl;
	int pos2=(int)((80-53)/2);
	printSpace(pos2);
	
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout <<  "Welcome to Happy Calendar! " << fileName << " is ready for use" << endl;
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << endl <<  "********************************************************************************" << endl;
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	int pos=(int)((80-39)/2);
	printSpace(pos);
	std::cout << "Current Singapore Local Time: ";
    std::cout << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << endl << "********************************************************************************" << endl;
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void printSpace(int pos) {
	for(int i=0;i<pos;i++) {
			cout<<" ";
	}
}

void readinput(vector<task> &toDoList, storage *store){
	string command, description;
	vector<undo> undomemory;
	defaultclass defaultmemory, defaultfunction;
	undo undofunction;
	logic function;
	
	undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
	defaultfunction.showDefaultTaskList(toDoList, defaultmemory);

	function.printMessage(MESSAGE_AVAILABLE_COMMANDS);
	cout << "command: ";
	cin >> command;
	getline(cin,description);

	defaultExecution(command,store,description,toDoList,undomemory);
}

void defaultExecution(string command,storage *store,string description,vector<task> &toDoList,vector<undo> undomemory) {
	defaultclass defaultfunction;
	undo currentundomemory;
	while(command!="exit"){
		defaultfunction.defaultexecuteCommand(fileName,store,command, description, 
			toDoList, undomemory, currentundomemory);
	};
}
