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

//These are function prototypes in ui.cpp
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

//print the welcome message
//precondition : none
//postcondition : welcome message is printed for one time
void printWelcomeLine() {
	cout <<  "Welcome to Happy Calendar! " << fileName << " is ready for use";
}

//print the happy faces
//precondition : none
//postcondition : happy faces printed for one time
void printHappyFaces() {
	cout << ">>(^_^)>>                                                         << (^_^)<<";
}

//print the cut-off line to make the display looks neater
//precondition : none
//postcondition : cut-off line is printed for one time
void printCutOffLine() {
	cout << "*******************************************************************************";
}

//print a new line
//precondition : none
//postcondition : new line is printed once
void printNewLine() {
	cout << endl;
}

//change the outputs below to the desired color
//precondition : none
//postcondition : change the outputs below color to blue
void colorCodingBlue() {
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

//change the outputs below to the desired color
//precondition : none
//postcondition : change the outputs below color to default white
void colorCodingWhite() {
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//change the outputs below to the desired color
//precondition : none
//postcondition : change the outputs below color to green
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

//print the amount of white spaces required
//precondition : get the number of white spaces needed
//postcondition : print the required white spaces
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
	undo currentundomemory;
	while(command!="exit"){
		assert(command.length() != 0);
		assert(description.length() != 0);
		defaultfunction.defaultexecuteCommand(fileName,store,command, description, toDoList, undomemory, currentundomemory);
	};
}
