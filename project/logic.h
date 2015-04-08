#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include "parser.h"
#include "Task.h"
#include "storage.h"
#include "undo.h"

using namespace std;

//Constants
const int FILE_NAME_ARG_NUMBER = 1;
const string ERROR_LIST_IS_EMPTY = "Empty";
const string DEFAULT_SAVE_FILENAME = "SaveFile";
const string INVALID_INDEX = "Invalid index entered";
const string MESSAGE_ITEM_ADDED_SUCCESSFULLY = "is added to file";
const string MESSAGE_ITEM_DELETED_SUCCESSFULLY = "Task is successfully deleted from file";
const string MESSAGE_ITEM_EDITED_SUCCESSFULLY = "Task is successfully edited";
const string MESSAGE_ITEMS_CLEARED_SUCCESSFULLY = "All content cleared from file";
const string MESSAGE_DATE_OVERDUE = "Date entered is already overdued";
const string MESSAGE_START_DATE_OVERDUE = "Starting date entered is already overdued";
const string MESSAGE_END_DATE_OVERDUE = "Ending date entered is already overdued";
const string MESSAGE_DATE_INVALID = "Input date is invalid";
const string MESSAGE_BOTH_DATE_INVALID = "Starting and Ending dates are invalid";
const string MESSAGE_START_DATE_INVALID = "Starting date IS invalid";
const string MESSAGE_END_DATE_INVALID = "Ending date is invalid";
const string MESSAGE_TIME_INVALID = "Input timing is invalid";
const string MESSAGE_START_TIME_INVALID = "Start timing is invalid";
const string MESSAGE_END_TIME_INVALID = "End timing is invalid";
const string MESSAGE_DUPLICATE_DEADLINE_TASK = "Deadline task exist already";
const string MESSAGE_TIME_SLOT_CLASH = "Time slots clash";
const string MESSAGE_SEARCH_FAILED = "There is no result found";
const string MESSAGE_INVALID_DISPLAY_COMMAND = "This is an invalid display command";
const string MESSAGE_DUPLICATE_FLOAT_TASK = "This task had been added before";
const string MESSAGE_AVAILABLE_COMMANDS = ">>>>>> add/edit/display/delete/clear/undo/search/default/exit <<<<<<";
const string MESSAGE_START_AND_END_TIME_ERROR = "Start time cannot be later than the end time";


//Global Variables


//Class has a vector containing all the entries in the to-do list
//Contains all functions facilitating add, delete, display, clear and save operations
//COntains functions that print the messages when user operations are executed, or fail to execute
class logic{
public:
	string displayAll(vector<task> &);
	
	void deleteItem(const int index, vector<task> &toDoList);
	void clearAll(vector<task> &toDoList);
	void editTask(int index, string description, vector<task> &toDoList);
	void markcompleted(int index, vector<task> &toDoList);
	void sorttext(vector<task> &toDoList);
	void sortdates(vector<task> &);
	void sorttime(vector<task> &);
	void sortEndTime(vector<task> &);

	void searchTask(vector<task> &, vector<task> &, string, string);
	bool isCheckSearchStringDigit(string);
	int convertNumStringToInt(string);

	void display(vector<task> &, vector<task> &, string, string);
	int getSystemDay();
	int getSystemMonth();
	int getSystemYear();

	void pushback(vector<task>& toDoList, vector<task>& tempVec, int index);

	bool isleapyear(unsigned short);
	bool isValidDate(unsigned short,unsigned short,unsigned short);
	bool isValidTime(int);
	bool checkIsDateOverdue(int, int, int, int);

	void printMessage(const string);
	void printMessage( string, const string);
	

	bool checkIfStartTimeIsEarlierThanEndTime(int,int,int,int,int,int,int,int);
	bool checkIsSameDate(int,int);
	bool checkIsSameMonth(int,int);
	bool checkIsSameYear(int,int);
};

