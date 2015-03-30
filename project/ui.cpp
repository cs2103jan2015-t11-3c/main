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


string getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readinput(vector<task> &toDoList);
void showDefaultTaskList(vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector<task> &timedVec);


int main(int argc, char *argv[]) {
	vector<task> toDoList;
	logic function;
	storage *store=new storage;

	getTextFileName(argc, argv);
	//store->readToDoListFromTextFile(getTextFileName(argc, argv));
	//store->readToDoListFromTextFile("SaveFile");
	toDoList=store->readToDoListFromTextFile("SaveFile");	
	printWelcomeMessage();
	readinput(toDoList);
	store->saveToSaveFile("SaveFile",toDoList);
	return 0;
}

string getTextFileName(const int argc, char *argv[]) {
	argc < 2 ? fileName=DEFAULT_SAVE_FILENAME : fileName=argv[FILE_NAME_ARG_NUMBER];
	std::cout << "hahah";
	return fileName;
}

void printWelcomeMessage() {
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "**********************************************************************" << endl;
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout <<  "Welcome to Happy Calendar! " << fileName << " is ready for use" << endl;
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "**********************************************************************" << endl;
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "Current Singapore Local Time: ";
    std::cout << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday
         << endl;
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << "**********************************************************************" << endl;
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void readinput(vector<task> &toDoList){
	string command, description;
	vector<undo> undomemory;
	defaultclass defaultmemory, defaultfunction;
	undo currentundomemory, undofunction;
	searchclass searchfunction;
	
	undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
	defaultfunction.showDefaultTaskList(toDoList);

	cout << endl << "command: ";
	cin >> command;
	getline(cin,description);

	while(command!="exit"){
		if(command == "search"||command == "display")
			searchfunction.searchexecuteCommand(command, description, toDoList, undomemory, currentundomemory);
		else
			 defaultfunction.defaultexecuteCommand(command, description, toDoList, undomemory, currentundomemory);
	};
}
