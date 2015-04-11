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
const string MESSAGE_INVALID_COMMAND = "Command entered is invalid, please try again";


//Global Variables


//Class has a vector containing all the entries in the to-do list
//Contains all functions facilitating add, delete, display, clear and save operations
//COntains functions that print the messages when user operations are executed, or fail to execute
class logic {
public:
	//display temporary vector
	//pre: temporary vector
	//post: list of tasks
	string displayAll(vector<task> &);
	void separateFloatAndOthers(vector<task> &, vector<task> &, vector<task> &);
	string printFloatTasks(vector<task> &, int);
	void sortOthers(vector<task> &, vector<task> &);
	string printOthers(vector<task> &, int);

	//delete task from toDoList
	//Pre: take in index and vector
	//post: none
	void deleteItem(const int , vector<task> &);

	//clear all the task from toDolist
	//Pre: take in vector
	//post: none
	void clearAll(vector<task> &);

	//edit existing task, name, dates, times
	//Pre: index of task, string that include command and changes to be made, vector
	//post: none
	void editTask(int , string , vector<task> &);
	void editFloatClass(vector<task> &, string, int);
	void editDeadlineClass(vector<task> &, string, int);
	void editTimedClass(vector<task> &, string, int);

	//mark task as completed
	//Pre: index of task, vector
	//Post: none
	void markcompleted(int , vector<task> &);

	//sort vector alphabetically
	//pre: vector
	//post: none
	void sorttext(vector<task> &);

	//sort vector by dates
	//Pre: vector
	//Post: none
	void sortdates(vector<task> &);

	//Sort vector by endtime
	//Pre:: vector
	//Post:: none
	void sortEndTime(vector<task> &);


	//search for keyword or number within the vector
	//Pre: main vector, temporary vector, keyword
	//Post: none
	void searchTask(vector<task> &, vector<task> &, string);

	//Check whether there is any integer in the keyword
	//Pre: keyword
	//Post: return false if integer if found, else return true
	bool isCheckSearchStringDigit(string);

	//covert string digit to integer digit
	//pre: string digit
	//post: int digit
	int convertNumStringToInt(string);

	//search for tasks with keyword
	//pre: main vector, keyword, temporary vector
	//post: none
	void searchWord(vector<task> &, string , vector<task> &);

	//search for tasks with name, dates, time with the particular digit
	//pre: main vector, keyword, temporary vector
	//post: none
	void searchDigit(vector<task> &, string , vector<task> &);

	//function to work on the display, 
	//pre: main vector, temporary vector, filename, command
	//post: none
	void display(vector<task> &, vector<task> &, string, string);

	//pushback task to a temporary vector that includes it's index on the main vector
	//pre: main vector, temporary vector, index
	//post: none
	void pushback(vector<task>& , vector<task>& , int );

	//check if it's leap year
	//pre: input year
	//post: return true if it's leap year
	bool isleapyear(unsigned short);

	//check whether date is valid
	//pre: input date, month, year
	//post: return true if date is valid
	bool isValidDate(unsigned short,unsigned short,unsigned short);

	//check whether input time is valid
	//pre: input time
	//post: return true if time is valid
	bool isValidTime(int);

	//check whether input date is overdue
	//pre: input date, month, year, time
	//post: return true if date is not overdue
	bool checkIsDateOverdue(int, int, int, int);


	void printMessage(const string);
	void printMessage( string, const string);
	
	//check whether start time is earlier than end time
	//pre: input s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time
	//post: return false if end time is earlier than start time
	bool checkIfStartTimeIsEarlierThanEndTime(int,int,int,int,int,int,int,int);
	bool checkIsSameDate(int,int);
	bool checkIsSameMonth(int,int);
	bool checkIsSameYear(int,int);
	
	//to display tasks that are due today/tomorrow, not done, three different types of tasks, all
	//pre: main vector, temporary vector, vector size
	//post: none
	void displayToday(vector<task> &, vector<task> &,int);
	void displayTomorrow(vector<task> &, vector<task> &,int);
	void displayNotDone(int ,vector<task> &,vector<task> &);
	void displayDone(int ,vector<task> &,vector<task> &);
	void displayFloat(int ,vector<task> &,vector<task> &);
	void displayDeadline(int ,vector<task> &,vector<task> &);
	void displayTimed(int ,vector<task> &,vector<task> &);
	void displayEverything(int ,vector<task> &,vector<task> &);
};

