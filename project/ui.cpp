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
#include <assert.h>

string fileName = "";


string getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readinput(vector<task> &,storage * );
void showDefaultTaskList(vector<task> &, vector<task> &, vector<task> &, vector<task> &);
void printSpace(int);
void showLocalTime();
void colorCodingBlue();
void colorCodingWhite();
void colorCodingGreen();
void printNewLine();
void printCutOffLine();
void printHappyFaces();
void printWelcomeLine();
void defaultExecution(string ,storage *,string ,vector<task> &,vector<undo> );

//@author A0113745J
int main(int argc, char *argv[]) {
	vector<task> toDoList;
	logic function;
	storage *store=storage::getInstance();
	
	toDoList = store->readToDoListFromTextFile(getTextFileName(argc, argv));
	printWelcomeMessage();
	readinput(toDoList,store);     

	return 0;
}

//get the text file name for the *.txt file which contains the updated tasks
//precondition : *.txt file is created by user
//postcondition : show user the desired file is loaded succesfully and is ready to use
string getTextFileName(const int argc, char *argv[]) {
	argc < 2 ? fileName=DEFAULT_SAVE_FILENAME : fileName=argv[FILE_NAME_ARG_NUMBER];
	std::cout << fileName << "loaded succesfully" << endl;
	return fileName;
}

//print the welcome message to user, which includes the local singapore time. 
//This is only shown once every time the user runs the software
//precondition : none
//postcondition : show welcome message to user
void printWelcomeMessage() {
	int pos=(int)((80-53)/2);
	colorCodingBlue();
	printCutOffLine();
	printNewLine();
	printHappyFaces();
	colorCodingWhite();
	printNewLine();
	printSpace(pos);
	colorCodingGreen();
	printWelcomeLine();
	printNewLine();
	colorCodingBlue();
	printNewLine();
	printCutOffLine();
	printNewLine();
	showLocalTime();
	colorCodingBlue();
	printNewLine();
	printCutOffLine();
	printNewLine();
	colorCodingWhite();
}

void printWelcomeLine() {
	cout <<  "Welcome to Happy Calendar! " << fileName << " is ready for use";
}

void printHappyFaces() {
	cout << ">>(^_^)>>                                                         << (^_^)<<";
}

void printCutOffLine() {
	cout << "*******************************************************************************";
}

void printNewLine() {
	cout << endl;
}

void colorCodingBlue() {
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void colorCodingWhite() {
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void colorCodingGreen() {
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

//print the local singapore time in the formate of year-month-date
//precondition : none
//postcondition : current local singapore time is shown to user
void showLocalTime() {
	time_t t = time(0);
    struct tm * now = localtime( & t );

	colorCodingWhite();

	int pos=(int)((80-39)/2);
	printSpace(pos);

	cout << "Current Singapore Local Time: ";
    cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' <<  now->tm_mday;

	printNewLine();
}

void printSpace(int pos) {
	for(int i = 0; i < pos; i++) {
			cout<<" ";
	}
}

//read the user's input command
//precondition : user need to key in the correct command word
//postcondition : user's input is read in
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

//execute the different type of user input and pass to defaultexecuteCommand function in default.h to process
//precondition : get the command input by the user
//postcondition : the command is processed
void defaultExecution(string command,storage *store,string description,vector<task> &toDoList,vector<undo> undomemory) {
	defaultclass defaultfunction;
	while(command!="exit"){
		assert(command.length() != 0);
		assert(description.length() != 0);
		defaultfunction.defaultexecuteCommand(fileName,store,command, description, toDoList, undomemory);
	};
}
