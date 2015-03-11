#include <iostream>
#include <vector>
#include <sstream>
#include "Calendar.h"
#include <fstream> 
#include <ctime>

using namespace std;

void getTextFileName(const int , char *[]);
void printWelcomeMessage();
void readToDoListFromTextFile(Calendar *);
void updateToDoList(Calendar *);
void executeCommand(const string, const string, Calendar *);
void getCommandAndDescription(string &, string &);
bool isValidCommand(const string, const string);
void trimString(string &);
int convertStringToIntegerIndex(const string);

int main(int argc, char *argv[]) {
	Calendar *toDoList = new Calendar;

	getTextFileName(argc, argv);
	printWelcomeMessage();
	readToDoListFromTextFile(toDoList);
	updateToDoList(toDoList);

	return 0;
}

void getTextFileName(const int argc, char *argv[]) {
	argc < 2 ? fileName=DEFAULT_SAVE_FILENAME : fileName=argv[FILE_NAME_ARG_NUMBER];
}

void printWelcomeMessage() {
	cout << endl << "Welcome to Happy Calendar! " << fileName << " is ready for use" << endl;
}

//Loads existing data from text file into program
void readToDoListFromTextFile(Calendar *toDoList) {
	fstream textFile;
	string input;
	input=toDoList->toString();
	Data datainput;
	string task;
	int date, month, year;
	double t_start, t_end;
	char t;

	textFile.open(fileName.c_str());

	//Remove the index of each line, eg: remove "1)" from "1) Some List Entry"
	//Adds the rest of the line to the to-do list after removing leading and following whitespaces
	while(textFile >> input) {
		getline(textFile,input);
		trimString(input);
		istringstream in(input);
		in>>task;
		in>>t_start;
		in>>t_end;
		in>>date;
		in>>t;
		in>>month;
		in>>t;
		in>>year;
		
		datainput.task=task;
		datainput.date=date;
		datainput.month=month;
		datainput.year=year;
		datainput.t_start=t_start;
		datainput.t_end=t_end;

		toDoList->readItem(datainput);
	}
	textFile.close();
}

void updateToDoList(Calendar *toDoList) {
	string command, description;
	
	while(command!="exit") {
		getCommandAndDescription(command, description);
		if(isValidCommand(command, description))
			executeCommand(command, description, toDoList);
	}
}

void executeCommand(const string command, const string description, Calendar *toDoList) {
	if(command=="add") {
		toDoList->addItem(description, fileName);
		toDoList->saveToSaveFile(fileName);
	}
	else if(command=="delete") {
		toDoList->deleteItem(convertStringToIntegerIndex(description), fileName);
		toDoList->saveToSaveFile(fileName);
	}
	else if(command=="display") {
		toDoList->displayAll(fileName);
	}
	else if(command=="clear") {
		toDoList->clearAll(fileName);
		toDoList->saveToSaveFile(fileName);
	}
	else if(command == "edit") {
		istringstream in(description);
		int index;
		in>>index;
		toDoList->editTask(index,fileName,description);
		toDoList->saveToSaveFile(fileName);
	}
	else if(command=="exit") {
		toDoList->saveToSaveFile(fileName);
	}
}

void getCommandAndDescription(string &command, string &description) {
	cout << endl << "command: ";
	cin >> command;
	getline(cin,description);
	trimString(description);
}

//Checks if the command entered is a recognised valid user command
//Checks if the description entered is valid for the command entered
//Prints error messages if either of the aforementioned conditions are not met
bool isValidCommand(const string command, const string description){
	if(command=="add") {
		if(description.size()==0) {
			Calendar::printMessage(ERROR_MISSING_DESCRIPTION);
			return false;
		}
		return true;
	}
	else if(command=="delete" ) {
		if(description.size()==0) {
			Calendar::printMessage(ERROR_MISSING_DESCRIPTION);
			return false;
		}

		unsigned int index=0;

		while(index<description.size()) {
			if(!isdigit(description[index])) {
				Calendar::printMessage(ERROR_INVALID_INDEX);
				return false;
			}
			index++;
		}
		return true;
	}
	else if(command=="display"||command=="clear"||command=="exit")
		return true;

	else if (command=="edit"){
		if(description.size()==0) {
			Calendar::printMessage(ERROR_MISSING_INDEX);
			return false;
	}   else return true;
	}
	Calendar::printMessage(ERROR_INVALID_COMMAND);

	return false;
}

//Remove leading and following whitespaces of a string
void trimString(string &description) {
	size_t lineStart=0, lineEnd=0;
	
	lineStart=description.find_first_not_of(DELIMITERS);
	lineEnd=description.find_last_not_of(DELIMITERS);
	
	if(lineStart==string::npos||lineEnd==string::npos)
		description="";
	else
		description=description.substr(lineStart,lineEnd-lineStart+1);
}

//Converts a number in string format to integer format
//Then converts the integer from base 1 to base 0, ie: 1,2,3,4,5... -> 0,1,2,3,4...
//String must not contain leading or following whitespaces, or function will fail
int convertStringToIntegerIndex(const string description) {
	unsigned int t_start = 0, t_end=description.size();
	int output=0;

	while(t_start!=t_end) {
		output*=10;
		output+=description[t_start]-'0';
		t_start++;
	}
	
	return output-1;
}
