#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>
#include "Task.h"
#include "logic.h"
#include "parser.h"
#include "undo.h"
#include "recurringTask.h"

using namespace std;

class defaultclass{
private:
	vector<task> floatVec;
	vector<task> deadlineVec;
	vector<task> timedVec;
	vector<task> todayTaskVec;
	vector<task> tomorTaskVec;
	
public:
	void defaultexecuteCommand(string, storage *, string &, string &, vector<task> &, vector<undo> &);
	bool checkfororiginalindex(string, defaultclass, vector<task> &, int &);
	void updatedefaultmemory(vector<task> &);
	
	void addRecurringTask(int,string,string,vector<task> &,storage *, vector<undo> &);
	void addFloatTask(string,vector<task> &,storage *, vector<undo> &);
	void addDeadlineTask(string,vector<task> &,storage *, vector<undo> &);
	void addTimedTask(string,vector<task> &,storage *, vector<undo> &);
	bool printErrorMsgForAddDeadlineTask(string,task  ,vector<task> &,storage *, int , int , int , int );
	bool printErrorMsgForAddTimedTask (string,task  ,vector<task> &,storage *, int , int , int , int, int, int, int, int);

	void deleteTask(string,string,vector<task> &,storage *,vector<undo> &, vector<task> &, defaultclass &);
	void displayTask(string, string,vector<task> &, vector<task> &);
	void clearTasks(string ,storage *,vector<task> &, vector<undo> &);
	void editTask(string, string, storage *, vector<task> &, vector<task> &, vector<undo> &, defaultclass &);

	void showDefaultTaskList(vector<task> &, defaultclass &);
	bool checkIfIsToday(int,int,int);
	bool checkIfIsTomorrow(int,int,int);
	void defaultFloatDisplay(defaultclass &);
	void displayTenFloatTask(defaultclass &);
	void displayAllFloatTasks(defaultclass &);
	void DisplayTaskFinishByToday(defaultclass &);
	void displayTenTasksDueToday(defaultclass &);
	void displayAllTasksDueToday(defaultclass &);
	void checkTypeOfTasksDueToday(defaultclass &,int);
	void DisplayTaskFinishByTmr(defaultclass &);
	void displayTenTasksDueTmr(defaultclass &);
	void displayAllTasksDueTmr(defaultclass &);
	void checkTypeOfTasksDueTmr(defaultclass &,int);

	void showHelpManual();
	void showHelpManualWelcomeMessage();
	void showHelpManualForAdd();
	void showHelpManualForEdit();
	void showHelpManualForDefaultEdit();
	void showHelpManualForDelete();
	void showHelpManualForDefaultDelete();
	void showHelpManualForDisplay();
	void colorCodingBlue();
	void colorCodingWhite();
	void colorCodingGreen();
};
