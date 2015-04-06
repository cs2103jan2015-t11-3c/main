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

const string DEFAULT_SAVE_FILENAME = "SaveFile";
const int FILE_NAME_ARG_NUMBER = 1;
const string MESSAGE_ITEM_ADDED_SUCCESSFULLY = "is added to file";
const string MESSAGE_ITEM_DELETED_SUCCESSFULLY = "successfully deleted from file";
const string MESSAGE_ITEM_EDITED_SUCCESSFULLY = "successfully edited";
const string MESSAGE_ITEMS_CLEARED_SUCCESSFULLY = "all content deleted from file";
const string ERROR_LIST_IS_EMPTY = "Empty";
const string INVALID_INDEX = "invalid index";
const string MESSAGE_DATE_OVERDUE = "Date entered is already overdued";
const string MESSAGE_START_DATE_OVERDUE = "Starting date entered is already overdued";
const string MESSAGE_END_DATE_OVERDUE = "Ending date entered is already overdued";
const string MESSAGE_DATE_INVALID = "input date is invalid";
const string MESSAGE_BOTH_DATE_INVALID = "Starting and Ending dates are invalid";
const string MESSAGE_START_DATE_INVALID = "Starting date IS invalid";
const string MESSAGE_END_DATE_INVALID = "Ending date is invalid";

const string MESSAGE_TIME_INVALID = "input timing is invalid";
const string MESSAGE_START_TIME_INVALID = "Start timing is invalid";
const string MESSAGE_END_TIME_INVALID = "End timing is invalid";

const string MESSAGE_DUPLICATE_DEADLINE_TASK = "deadline task exist already";

const string MESSAGE_TIME_SLOT_CLASH = "Time slots clash";

const string MESSAGE_SEARCH_FAILED = "There is no result found";

const string MESSAGE_INVALID_DISPLAY_COMMAND = "This is an invalid display command";

const string MESSAGE_DUPLICATE_FLOAT_TASK = "This task had been added before";



//Global Variables
static string fileName = "";

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
	
};

