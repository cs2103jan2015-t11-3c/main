#include "default.h"
#include <iostream>
#include <sstream>
#include <fstream> 
#include <algorithm>
#include <windows.h>
#include <ctime>


//execute different types of command entered by user
//i.e. add TASK /by 1000 today
//command includes: add,edit,display,delete,clear,undo,search,default and exit
//error message will be shown to user if command entered is invalid
//success message will be shown to user if user input is successfully processed
//precondition : user enter the command and its relating description
//postcondition : command of different types is processed
//@author A0113745J
void defaultclass::defaultexecuteCommand(string fileName,storage *store, string &command,string &description, vector<task> &toDoList, vector<undo> &undomemory) {
	string text;
	parser parse;
    logic function;
	undo undofunction;
	storage *stor=store;
	vector<task> tempVec;
	defaultclass defaultmemory;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time, originindex;

	defaultmemory.updatedefaultmemory(toDoList);
	assert(description.length() != 0);
	while(command != "exit"){
		parse.trimString(description);
		if(parse.isValidCommand(command, description)) {
			if(command == "add" || command =="+"||command == "a") {
				string recurringCommandWord;
				int end, recurPeriod;
				
				end = parse.getEndPosition(description);
				recurPeriod = parse.getRecurPeriod(description);//5
				if(recurPeriod != 0) {
					description = description.substr(end+1);
				} else {
					description = description;
				}
				recurringCommandWord = parse.getRecurruingCommandWord(description);

				if(recurringCommandWord == "daily" ||recurringCommandWord == "weekly" ||recurringCommandWord == "monthly" ||recurringCommandWord == "yearly") {
					addRecurringTask(recurPeriod,recurringCommandWord,description, toDoList,store,undomemory);
				} else {
					if(parse.checktype(description) == "float") {
						addFloatTask(description,toDoList,store,undomemory);
					} else if(parse.checktype(description) == "deadline") {
						addDeadlineTask(description,toDoList,store,undomemory);
					} else if(parse.checktype(description) == "timed") {
						addTimedTask(description,toDoList,store,undomemory);
					} 
				}
				showDefaultTaskList(toDoList, defaultmemory);
				store->saveToSaveFile(fileName,toDoList);
			} else if(command=="delete"||command=="-"||command=="remove") {
				deleteTask( fileName,description,toDoList,store,undomemory, tempVec, defaultmemory);
			} else if(command=="display") {
				displayTask(fileName,description,toDoList, tempVec);
			} else if(command=="clear") {
				clearTasks(fileName,store,toDoList,undomemory);
			} else if(command == "edit"||command =="change"||command =="modify") {
				editTask(fileName, description, store, toDoList, tempVec, undomemory, defaultmemory);
			} else if(command=="exit") {
				store->saveToSaveFile(fileName,toDoList);
				return;
			} else if(command == "done") {
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
				function.markCompleted(originindex, toDoList);
				showDefaultTaskList(toDoList, defaultmemory);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				}
			} else if(command == "notdone"){
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
				function.markNotCompleted(originindex, toDoList);
				showDefaultTaskList(toDoList, defaultmemory);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				}
			}else if(command == "undo") {
				if (system("CLS")) system("clear");
				if(undomemory.size() - 1 == 0)
					function.printMessage(UNDO_FAIL);
				else{
				toDoList = undomemory[undomemory.size()-2].returnmemory();
				undomemory.pop_back();
				showDefaultTaskList(toDoList, defaultmemory);
				store->saveToSaveFile(fileName,toDoList);
				}
			} else if(command == "search") {
				if (system("CLS")) system("clear");
				function.searchTask(toDoList, tempVec,description);
			} else if(command == "default") {
				if (system("CLS")) system("clear");
				showDefaultTaskList(toDoList, defaultmemory);
			} else if(command == "changeDirectory") {		
				store->changeDirectory( description,fileName,toDoList);	
			} else if(command == "changeFilename") {		
				store->changeFileName(description,toDoList);			
			} else if (command == "help") {
				showHelpManual();
			} else {
				function.printMessage(MESSAGE_INVALID_COMMAND);
			}
		}
		function.printMessage(MESSAGE_AVAILABLE_COMMANDS);
		cout <<  "command: ";
		cin >> command;
		getline(cin,description);
	}
}

void defaultclass::showHelpManual() {
	cout << "help manual" << endl;
}

//check the original index of the task for float task, task due today and task due tomorrow in the float vector, today's task vector 
//and tomorrow's task vector
//on default page, tasks are shown in consecutive indices, i.e. 1,2,3,4...., 
//instead of float task(1,2,3...), task due today(1,2,3...), task due tomorrow(1,2,3...)
//therefore there is a need to check for each task's original index when execute commands such ad edit <index> and delete <index>
//precondition : nont
//postcondition : return the original index of a task
bool defaultclass::checkfororiginalindex(string description, defaultclass defaultmemory, vector<task> &tempVec, int &originindex){
	string temp;
	parser parse;
	logic function;
	int index, size;

	assert(description.length() != 0);
	istringstream in(description);
	in>> temp;
	in>> index;
	index = index -1;

	if(temp == "float"||temp == "flt"){
		size = defaultmemory.floatVec.size();

		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		} else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}else
		originindex = defaultmemory.floatVec[index].returntempnum();
	} else if(temp == "today"||temp == "tdy"){ 
		   size = defaultmemory.todayTaskVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		} else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}else
		originindex = defaultmemory.todayTaskVec[index].returntempnum();
	} else if(temp == "tomorrow"|| temp =="tmrw"){
		size = defaultmemory.tomorTaskVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		} else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}else
		originindex = defaultmemory.tomorTaskVec[index].returntempnum();
	} else {
		istringstream intemp(description);
		intemp >> index;
		index = index - 1;

		size = tempVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		} else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}else
		originindex = tempVec[index].returntempnum();
	}
	return true;
}

void defaultclass::updatedefaultmemory(vector<task> &toDoList){
	vector<task> floatVec_;
	task temp;
	int index, i = 0, j = 0, k = 0;

	for(index = 0; index != toDoList.size(); ++index) {
		if((checkIfIsToday(toDoList[index].returnenddate(),toDoList[index].returnendmonth(),toDoList[index].returnendyear()))&&(toDoList[index].returnstatus() == false)){
			   todayTaskVec.push_back(toDoList[index]);
			   todayTaskVec[i].inserttempnum(index);
			   i++;
		} else if((checkIfIsTomorrow(toDoList[index].returnenddate(),toDoList[index].returnendmonth(),toDoList[index].returnendyear()))&&(toDoList[index].returnstatus() == false)) {
			   tomorTaskVec.push_back(toDoList[index]);
			   tomorTaskVec[j].inserttempnum(index);
			   j++;
		} else if((toDoList[index].returntype() =="float")&&(toDoList[index].returnstatus() == false)){
			floatVec_.push_back(toDoList[index]);
			floatVec_[k].inserttempnum(index);
			k++;
		}
	}
	floatVec = floatVec_;
}

//Add the recurring task entered by the user to the vector toDoList by categorise them into deadline and timed tasks
//precondition : user key in a recurring task of type deadline or timed task
//postcondition : recurring task is added to the toDoList
void defaultclass::addRecurringTask(int recurPeriod,string recurringCommandWord, string description, vector<task> & toDoList,storage *store , vector<undo> &undomemory) {
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time, end;
	parser parse;
	string text;
	storage *stor = store;
	logic function;
	undo undofunction;

	assert(description.length() != 0);

	end = parse.getEndPosition(description);

	description = description.substr(end+1);

	if(parse.checktype(description) == "deadline") {
	    parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
	    recurringTask recurTask(text,0,e_time);
		task datainput(text);
		if(printErrorMsgForAddDeadlineTask( text,  datainput, toDoList, store, e_date,  e_month,  e_year,  e_time)) {
		} else {
			function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	        recurTask.AddRecurring(recurPeriod,recurringCommandWord,e_date,e_month,e_year,0,0,0,"deadline",toDoList);
			undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		}
	} else {
	    parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
	    recurringTask recurTask(text,s_time,e_time);
		task datainput(text);
		if(printErrorMsgForAddTimedTask( text, datainput,toDoList, store,  e_date, e_month,  e_year,  e_time,  s_date, s_month,  s_year,  s_time)) {
		} else {
			function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	        recurTask.AddRecurring(recurPeriod,recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,"timed",toDoList);
			undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		}
	}
}

void defaultclass::addFloatTask(string description,vector<task> &toDoList,storage *store , vector<undo> &undomemory) {
	storage *stor = store;
	logic function;
	undo undofunction;
	assert(description.length() != 0);
	task datainput(description);
	datainput.addFloatItem();

	if (system("CLS")) system("clear");
	if(!store->isFloatDuplicated(datainput, toDoList)) {
		toDoList.push_back(datainput);
		function.printMessage(description, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
	} else {
		function.printMessage(MESSAGE_DUPLICATE_FLOAT_TASK);
	}
}

void defaultclass::addDeadlineTask(string description,vector<task> &toDoList,storage *store, vector<undo> &undomemory) {
	string text;
	parser parse;
	storage *stor = store;
	logic function;
	undo undofunction;
	int e_date, e_month, e_year, e_time;

	assert(description.length() != 0);
	parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
	task datainput(text);
	datainput.addDeadlineItem(e_date, e_month, e_year, e_time);

	if(printErrorMsgForAddDeadlineTask( text,datainput,toDoList, store, e_date,  e_month,  e_year,  e_time)) {
	} else {
		toDoList.push_back(datainput);
		function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
	}
}

void defaultclass::addTimedTask(string description,vector<task> &toDoList,storage *store, vector<undo> &undomemory) {
	string text;
	parser parse;
	logic function;
	undo undofunction;
	storage *stor = store;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	assert(description.length() != 0);
	parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
	task datainput(text);
	datainput.addTimedItem(s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);

	if(printErrorMsgForAddTimedTask(text,datainput, toDoList, store,e_date,  e_month,  e_year, e_time,  s_date, s_month, s_year,  s_time)) {
	} else {
		toDoList.push_back(datainput);
		function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
	}
}

void defaultclass::deleteTask(string fileName,string description, vector<task> &toDoList, storage *store, vector<undo> &undomemory, vector<task> &tempVec, defaultclass &defaultmemory) {
	int originindex;
    logic function;
	undo undofunction;
	storage *stor=store;
	assert(description.length() != 0);
	if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
		function.deleteItem(originindex, toDoList);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		showDefaultTaskList(toDoList, defaultmemory);
		store->saveToSaveFile(fileName,toDoList);
	}
}


void defaultclass::displayTask(string fileName,string description, vector<task> &toDoList, vector<task> &tempVec) {
	logic function;
	assert(description.length() != 0);
	tempVec.clear();
	if (system("CLS")) system("clear");
    function.display(toDoList, tempVec, fileName, description);
}

void defaultclass::clearTasks(string fileName,storage *store,vector<task> &toDoList, vector<undo> &undomemory) {
	logic function;
	undo undofunction;
	storage *stor=store;

	function.clearAll(toDoList);
    undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
    store->saveToSaveFile(fileName,toDoList);
}

void defaultclass::editTask(string fileName, string description, storage *store, vector<task> &toDoList, vector<task> &tempVec, vector<undo> &undomemory, defaultclass &defaultmemory){
	int originindex;
	logic function;
	undo undofunction;
	if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)) {
		if(function.editTask(originindex ,description, toDoList)){
			undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
			store->saveToSaveFile(fileName,toDoList);
			if (system("CLS")) system("clear");
			function.printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
			showDefaultTaskList(toDoList, defaultmemory);
		}
	}
}

//Three types of tasks are shown every time the user key in the command "default"
//floating tasks, tasks for today and tasks for tomorrow
//Floating tasks are sorted based on alphabetical order
//today and tomorrow task are sorted based on the ending time
//precondition : default command is entered
//postcondition : float task, task to be done today and tomorrow are shown
void defaultclass::showDefaultTaskList(vector<task> &toDoList, defaultclass &defaultmemory) {
	int index, i;
	logic function;
	time_t t = time(0);  
    struct tm * now = localtime(& t);

	defaultmemory.floatVec.clear();
	defaultmemory.todayTaskVec.clear();
	defaultmemory.tomorTaskVec.clear();
	defaultmemory.updatedefaultmemory(toDoList);

	function.sortText(defaultmemory.floatVec);
	cout << endl << "[Floating]" << "===================================================================="<< endl << endl;
	defaultFloatDisplay(defaultmemory);

	cout << endl << "[Today: " <<  now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << "]" 
		<< "============================================================" << endl << endl;
	function.sortEndTime(defaultmemory.todayTaskVec);
	DisplayTaskFinishByToday(defaultmemory);
	

    cout << endl << "[Tomorrow: " <<  now->tm_mday +1 << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << "]" << "===========================================================" << endl;
	function.sortEndTime(defaultmemory.tomorTaskVec);
	DisplayTaskFinishByTmr(defaultmemory);
	
	cout <<endl;
}

//Display floating task in the default page
//If there exits more than 10 float tasks, only the sorted first 10 tasks will be displayed in default page
//precondition : none
//postcondition : floating task displayed in alphabetical order
void defaultclass::defaultFloatDisplay(defaultclass &defaultmemory) {
	if(defaultmemory.floatVec.size() > 10) {
		displayTenFloatTask(defaultmemory);
	} else {
		displayAllFloatTasks(defaultmemory);
	}
}

void defaultclass::displayTenFloatTask(defaultclass &defaultmemory) {
	for(int index = 0; index < 10; ++index) {
			cout << defaultmemory.floatVec[index].displayFloat(index) << endl;
		}
}

void defaultclass::displayAllFloatTasks(defaultclass &defaultmemory) {
	for(int index = 0; index != defaultmemory.floatVec.size(); ++index) {
			cout << defaultmemory.floatVec[index].displayFloat(index) << endl;
		}
}

//Display task to be finished by today in the default page
//If there exits more than 10 tasks due today, only the sorted first 10 tasks will be displayed in default page
//precondition : none
//postcondition : today's tasks are displayed according to the end timing
void defaultclass::DisplayTaskFinishByToday(defaultclass &defaultmemory) {
	if(defaultmemory.todayTaskVec.size() > 10) {
		displayTenTasksDueToday(defaultmemory);
	} else {
		displayAllTasksDueToday(defaultmemory);
	}
}

void defaultclass::displayTenTasksDueToday(defaultclass &defaultmemory) {
	for(int i = 0; i < 10; ++i){
		checkTypeOfTasksDueToday(defaultmemory,i);
	}
}

void defaultclass::displayAllTasksDueToday(defaultclass &defaultmemory) {
	for(int i = 0; i != defaultmemory.todayTaskVec.size(); ++i){
		checkTypeOfTasksDueToday(defaultmemory,i);
	}
}

void defaultclass::checkTypeOfTasksDueToday(defaultclass &defaultmemory, int i) {
	if(defaultmemory.todayTaskVec[i].returntype() == "deadline") {
			cout << defaultmemory.todayTaskVec[i].displayDefaultTasks(i) << endl;
		} else if(defaultmemory.todayTaskVec[i].returntype() == "timed") {
			if((defaultmemory.todayTaskVec[i].returnenddate() != defaultmemory.todayTaskVec[i].returnstartdate())||
				(defaultmemory.todayTaskVec[i].returnendmonth() != defaultmemory.todayTaskVec[i].returnstartmonth())) {
				cout << defaultmemory.todayTaskVec[i].displayDefaultTasksOver2days(i) << endl;
			} else {
				cout <<  defaultmemory.todayTaskVec[i].displayDefaultTasksWithTwoTimes(i) << endl;
			}
		}
}


//Display task to be finished by tomorow in the default page
//If there exits more than 10 tasks due tomorrow, only the sorted first 10 tasks will be displayed in default page
//precondition : none
//postcondition : tomorrow's tasks are displayed according to the end timing
void defaultclass::DisplayTaskFinishByTmr(defaultclass &defaultmemory) {
	if(defaultmemory.tomorTaskVec.size() > 10) {
		displayTenTasksDueTmr(defaultmemory);
	} else {
		displayAllTasksDueTmr(defaultmemory);
	}
}

void defaultclass::displayTenTasksDueTmr(defaultclass &defaultmemory) {
	for(int i = 0; i < 10; ++i) {
		checkTypeOfTasksDueTmr(defaultmemory,i);
	}
}

void defaultclass::displayAllTasksDueTmr(defaultclass &defaultmemory) {
	for(int i = 0; i != defaultmemory.tomorTaskVec.size(); ++i) {
		checkTypeOfTasksDueTmr(defaultmemory,i);
	}
}

void defaultclass::checkTypeOfTasksDueTmr(defaultclass &defaultmemory,int i) {
	if(defaultmemory.tomorTaskVec[i].returntype() == "deadline") {
			cout << defaultmemory.tomorTaskVec[i].displayDefaultTasks(i) << endl;
	} else if(defaultmemory.tomorTaskVec[i].returntype() == "timed") {
			if((defaultmemory.tomorTaskVec[i].returnenddate() != defaultmemory.tomorTaskVec[i].returnstartdate())||
				(defaultmemory.tomorTaskVec[i].returnendmonth() != defaultmemory.tomorTaskVec[i].returnstartmonth())) {
				cout << defaultmemory.tomorTaskVec[i].displayDefaultTasksOver2days(i) << endl;
			} else {
				cout <<  defaultmemory.tomorTaskVec[i].displayDefaultTasksWithTwoTimes(i) << endl;
			}
	}
}

bool defaultclass::checkIfIsToday(int e_day,int e_month,int e_year) {
	parser parse;
	if(e_day == parse.getSystemDay() && e_month == parse.getSystemMonth() && e_year == parse.getSystemYear()) {
		return true;
	} else {
		return false;
	}
}

bool defaultclass::checkIfIsTomorrow(int e_day,int e_month,int e_year) {
	parser parse;
	if(e_day == (parse.getSystemDay()+1) && e_month == parse.getSystemMonth() && e_year == parse.getSystemYear()) {
		return true;
	} else {
		return false;
	}
}


//If the deadline task entered by the user has errors, false will be returned
//The errors include: task inputed is already existed; date entered is already overdued;
//The time entered is not within 24 hours; date entered does not exist(i.e. 30/2/2015)
//precondition : task take in is a deadline task
//postcondition : return true if no errors found, false otherwise
bool defaultclass::printErrorMsgForAddDeadlineTask(string text, task datainput, vector<task> &toDoList, storage *store, int e_date, int e_month, int e_year, int e_time) {
	
    logic function;
	parser parse;
	storage *stor = store;
	if (system("CLS")) system("clear");
	if(store->isDeadlineDuplicated(datainput, toDoList)) {
		function.printMessage(MESSAGE_DUPLICATE_DEADLINE_TASK);
	} else if(!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time) && !parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_DATE_OVERDUE);
		cout << "and";
		function.printMessage(MESSAGE_TIME_INVALID);
	} else if(!parse.isValidDate(e_date,e_month,e_year) && !parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_DATE_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_TIME_INVALID);
	} else if (!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
			function.printMessage(MESSAGE_DATE_OVERDUE);
	} else if(!parse.isValidDate(e_date,e_month,e_year)) {
			function.printMessage(MESSAGE_DATE_INVALID);
	} else if (!parse.isValidTime(e_time)) {
			function.printMessage(MESSAGE_TIME_INVALID);
	} else{
		return false;
	}
}

//If the timed task entered by the user has errors, false will be returned
//The errors include: task inputed is already existed; start or end date entered is already overdued;
//start or end timing entered is not within 24 hours; start or end date entered does not exist(i.e. 30/2/2015)
//Start time is later than the end time if task happends on the same day.
//precondition : task take in is a deadline task
//postcondition : return true if no errors found, false otherwise
bool defaultclass::printErrorMsgForAddTimedTask(string text,task datainput, vector<task> &toDoList,storage *store, int e_date, int e_month, int e_year, int e_time, int s_date,int s_month, int s_year, int s_time) {
    logic function;
	parser parse;
	storage *stor = store;
	bool result = true;
	if (system("CLS")) system("clear");
	if (function.checkIfStartTimeIsEarlierThanEndTime(s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time)) {
		function.printMessage(MESSAGE_START_AND_END_TIME_ERROR);
	} else if (store->isTimeClashed(datainput, toDoList)) {
		function.printMessage(MESSAGE_TIME_SLOT_CLASH);
	} else if(!parse.checkIsDateOverdue(s_date,s_month,s_year,s_time) && !parse.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
	} else if(!parse.isValidTime(s_time) && !parse.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_START_DATE_INVALID);
	} else if(!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time) && !parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if(!parse.isValidTime(e_time) && !parse.isValidDate(e_date,e_month,e_year)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_INVALID);
	} else if(!parse.isValidDate(e_date,e_month,e_year)&&!parse.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_BOTH_DATE_INVALID);
	} else if(!parse.isValidTime(e_time) && !parse.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_TIME_INVALID);
	} else if(!parse.checkIsDateOverdue(s_date,s_month,s_year,s_time) && !parse.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if(!parse.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
	} else if(!parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
	} else if (!parse.checkIsDateOverdue(s_date,s_month,s_year,s_time)) {
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
	} else if (!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if (!parse.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_START_DATE_INVALID);
	} else if(!parse.isValidDate(e_date,e_month,e_year)) {
		function.printMessage(MESSAGE_END_DATE_INVALID);
	} else{
		return false;
	}
}


