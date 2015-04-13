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
const string MESSAGE_AVAILABLE_COMMANDS = ">>>>>> help/add/edit/display/delete/clear/undo/search/default/exit <<<<<<";
const string MESSAGE_START_AND_END_TIME_ERROR = "Start time cannot be later than the end time";
const string MESSAGE_INVALID_COMMAND = "Command entered is invalid, please try again";
const string UNDO_FAIL = "Undo has reached it's end";


//message for helper manual-add
const string HLEPER_MESSAGE_TITLE_ADD = ">>>>>>>>>> add <<<<<<<<<<";
const string HELPER_MESSAGE_ADD_FLOAT_TASK = "add [task]";
const string HELPER_MESSAGE_ADD_DEADLINE_TASK = "add [task] /by [time] on [date]";
const string HELPER_MESSAGE_ADD_TIMED_TASK = "add [task] /from [time] on [date] to [time] on [date]";
const string HELPER_MESSAGE_ADD_RECUR_DEADLINE_TASK = "add [period] [daily] /by [time] on [date]";
const string HELPER_MESSAGE_ADD_RECUR_TIMED_TASK = "add [period] [daily] /from [time] on [date] to [time] on [date]";

//message for helper manual-edit after display/search
const string HLEPER_MESSAGE_TITLE_EDIT = ">>>>>>>>>> edit after search/display <<<<<<<<<<";
const string HELPER_MESSAGE_EDIT_TASK_NAME = "edit [index] -name [new task]";
const string HELPER_MESSAGE_EDIT_DEADLINE_TASK_TIME = "edit [index] -due [new time]";
const string HELPER_MESSAGE_EDIT_TIMED_TASK_TIME = "edit [index] -start/end [new time]";

//messsage for helper manual-edit in default page
const string HLEPER_MESSAGE_TITLE_EDIT_DEFAULT = ">>>>>>>>>> edit in default page <<<<<<<<<<";
const string DEFAULT_HELPER_MESSAGE_EDIT_TASK_NAME = "edit [float/today/tomorrow] [index] -name [new task]";
const string DEFAULT_HELPER_MESSAGE_EDIT_DEADLINE_TASK_TIME = "edit [float/today/tomorrow] [index] -due [new]";
const string DEFAULT_HELPER_MESSAGE_EDIT_TIMED_TASK_TIME = "edit [float/today/tomorrow] [index] -start/end [new]";

//message for helper manual-display
const string HLEPER_MESSAGE_TITLE_DISPLAY = ">>>>>>>>>> display task <<<<<<<<<<";
const string HELPER_MESSAGE_DISPLAY_TYPES = "display [today/tomorrow/tmr/float/deadline/timed/not done/done/all]";

//message for helper manual-delete after display/search
const string HLEPER_MESSAGE_TITLE_DELETE = ">>>>>>>>>> delete after search/dislay <<<<<<<<<<";
const string HELPER_MESSAGE_DELETE = "delete [index]";

//message for helper manual-delete in default page
const string HLEPER_MESSAGE_TITLE_DELETE_DEFAULT = ">>>>>>>>>> delete in default page <<<<<<<<<<";
const string DEFAULT_HELPER_MESSAGE_DELETE = "delete [float/today/tomorrow] [index]";

//message for helper manual-clear
const string HLEPER_MESSAGE_TITLE_CLEAR = ">>>>>>>>>> clear <<<<<<<<<<";
const string HELPER_MESSAGE_CLEAR = "This command clears all the contents";

//message for helper manual-undo
const string HLEPER_MESSAGE_TITLE_UNDO = ">>>>>>>>>> undo <<<<<<<<<<";
const string HELPER_MESSAGE_UNDO = "This command is able to undo more than once";

//message for helper manual-search
const string HLEPER_MESSAGE_TITLE_SEARCH = ">>>>>>>>>> search <<<<<<<<<<";
const string HELPER_MESSAGE_SEARCH = "search [key word]";

//message for helper manual-default
const string HLEPER_MESSAGE_TITLE_DEFAULT = ">>>>>>>>>> default <<<<<<<<<<";
const string HELPER_MESSAGE_DEFAULT = "This command shows the default page";

//message for helper manual-exit 
const string HLEPER_MESSAGE_TITLE_EXIT = ">>>>>>>>>> exit <<<<<<<<<<";
const string HELPER_MESSAGE_EXIT = "This command ends the program";

//message for welcome to helper manual
const string HLEPER_MESSAGE_WELCOME = "===============WELCOME TO THE USER MANUAL FOR HAPPY CALENDAR===============";













//Class has a vector containing all the entries in the to-do list
//Contains all functions facilitating add, delete, display, clear and save operations
//COntains functions that print the messages when user operations are executed, or fail to execute
class logic {
public:
	string displayAll(vector<task> &);
	void separateFloatAndOthers(vector<task> &, vector<task> &, vector<task> &);
	string printFloatTasks(vector<task> &, int &);
	void sortOthers(vector<task> &, vector<task> &);
	string printOthers(vector<task> &, int &);

	bool editTask(int , string , vector<task> &);
	bool editFloatClass(vector<task> &, string, int);
	bool editDeadlineClass(vector<task> &, string, int);
	bool editTimedClass(vector<task> &, string, int);
	bool printErrorMsgForEditDeadlineTask(int e_date, int e_month, int e_year, int e_time);
	bool printErrorMsgForEditTimedTask(int e_date, int e_month, int e_year, int e_time, int s_date,int s_month, int s_year, int s_time);

	void deleteItem(const int , vector<task> &);
	void clearAll(vector<task> &);
	void markCompleted(int , vector<task> &);
	void markNotCompleted(int, vector<task> &);
	void sortText(vector<task> &);
	void sortDates(vector<task> &);
	void sortEndTime(vector<task> &);

	void searchTask(vector<task> &, vector<task> &, string);
	void searchWord(vector<task> &, string , vector<task> &);
	void searchDigit(vector<task> &, string , vector<task> &);

	void pushback(vector<task>& , vector<task>& , int );

	void printMessage(const string);
	void printMessage( string, const string);

	//check whether start time is earlier than end time
	//precondition: input s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time
	//postcondition: return false if end time is earlier than start time
	bool checkIfStartTimeIsEarlierThanEndTime(int,int,int,int,int,int,int,int);
	bool checkIsSameDate(int,int);
	bool checkIsSameMonth(int,int);
	bool checkIsSameYear(int,int);
	
	void displayToday(vector<task> &, vector<task> &,int);
	void displayTomorrow(vector<task> &, vector<task> &,int);
	void displayNotDone(int ,vector<task> &,vector<task> &);
	void displayDone(int ,vector<task> &,vector<task> &);
	void displayFloat(int ,vector<task> &,vector<task> &);
	void displayDeadline(int ,vector<task> &,vector<task> &);
	void displayTimed(int ,vector<task> &,vector<task> &);
	void displayEverything(int ,vector<task> &,vector<task> &);
	void display(vector<task> &, vector<task> &, string, string);
};

