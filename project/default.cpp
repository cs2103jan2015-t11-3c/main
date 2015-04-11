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
void defaultclass::defaultexecuteCommand(string fileName,storage *store, string &command,string &description, vector<task> &toDoList, vector<undo> &undomemory,undo &currentundomemory) {
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
			if(command == "add" || command =="+") {
				string recurringCommandWord;
				int end, recurPeriod;
				
				end = getEndPosition(description);
				recurPeriod = getRecurPeriod(description);//5
				if(recurPeriod != 0) {
					description = description.substr(end+1);
				} else {
					description = description;
				}
				recurringCommandWord = getRecurruingCommandWord(description);

				if(recurringCommandWord == "daily" ||recurringCommandWord == "weekly" ||recurringCommandWord == "monthly" ||recurringCommandWord == "yearly") {
					addRecurringTask(recurPeriod,recurringCommandWord,description, toDoList,store);
				} else {
					if(parse.checktype(description) == "float") {
						addFloatTask(description,toDoList,store);
					} else if(parse.checktype(description) == "deadline") {
						addDeadlineTask(description,toDoList,store);
					} else if(parse.checktype(description) == "timed") {
						addTimedTask(description,toDoList,store);
					} 
				}
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				showDefaultTaskList(toDoList, defaultmemory);
				store->saveToSaveFile(fileName,toDoList);
			} else if(command=="delete"||command=="-"||command=="remove") {
				deleteTask( fileName,description,toDoList,store,undomemory, tempVec, defaultmemory);
			} else if(command=="display") {
				displayTask(fileName,description,toDoList, tempVec);
			} else if(command=="clear") {
				clearTasks(fileName,store,toDoList,undomemory);
			} else if(command == "edit") {
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)) {
					function.editTask(originindex ,description, toDoList);
					undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
					if (system("CLS")) system("clear");
					showDefaultTaskList(toDoList, defaultmemory);
					store->saveToSaveFile(fileName,toDoList);
				}
			} else if(command=="exit") {
				store->saveToSaveFile(fileName,toDoList);
				return;
			} else if(command == "done") {
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
				function.markcompleted(originindex, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				}
			} else if(command == "undo") {
				currentundomemory = undomemory[undomemory.size()-2];
				toDoList = currentundomemory.returnmemory();
				undomemory.pop_back();
				if (system("CLS")) system("clear");
				showDefaultTaskList(toDoList, defaultmemory);
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


//Determine the recurring period the user want to do a recurring task
//precondition : user enter a recurring task
//postcondition : return the recurring period, if not specified by user, default period is zero
int defaultclass::getRecurPeriod(string description) {
	assert(description.length() != 0);
	int start = getStartPosition(description);
	int end = getEndPosition(description);

	string recurPeriod = description.substr(start, end - start);

	for(int i = 0; i < recurPeriod.size(); ++i) {
		if(!isdigit(recurPeriod[i])) {
			return 0;
		} else {
			int convertedNum;
			convertedNum = atoi(recurPeriod.c_str());
			return convertedNum;
		}
	}
}

//Determine if the user want to do a task daily/weekly/monthly/yearly
//precondition : user input a recurring tas
//postcondition : return the recurring command word
string defaultclass::getRecurruingCommandWord(string description) {
	assert(description.length() != 0);
	int start = getStartPosition(description);
	int end = getEndPosition(description);

	string recurringCommandWord = description.substr(start, end - start);	

	return recurringCommandWord;
}


//Determine the position of the start of the description
//precondition : take in the description entered by user
//postcondition : return the start position
int defaultclass::getStartPosition(string description) {
	assert(description.length() != 0);
	int start;
	
	start = description.find_first_not_of(" ");
	
	return start;
}

//Determine the position of the end of the first word
//precondition : take in the description entered by user
//postcondition : return the end position
int defaultclass::getEndPosition(string description) {
	assert(description.length() != 0);
	int end;

	end = description.find_first_of(" ");

	return end;
}

//Add the recurring task entered by the user to the vector toDoList by categorise them into deadline and timed tasks
//precondition : user key in a recurring task of type deadline or timed task
//postcondition : recurring task is added to the toDoList
void defaultclass::addRecurringTask(int recurPeriod,string recurringCommandWord, string description, vector<task> & toDoList,storage *store ) {
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time, end;
	parser parse;
	string text;
	storage *stor = store;
	logic function;

	assert(description.length() != 0);

	end = getEndPosition(description);

	description = description.substr(end+1);

	if(parse.checktype(description) == "deadline") {
	    parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
	    recurringTask recurTask(text,0,e_time);
		task datainput(text);
		if(printErrorMsgForAddDeadlineTask( text,  datainput, toDoList, store, e_date,  e_month,  e_year,  e_time)) {
		} else {
			function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	        recurTask.AddRecurring(recurPeriod,recurringCommandWord,e_date,e_month,e_year,0,0,0,"deadline",toDoList);
		}
	} else {
	    parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
	    recurringTask recurTask(text,s_time,e_time);
		task datainput(text);
		if(printErrorMsgForAddTimedTask( text, datainput,toDoList, store,  e_date, e_month,  e_year,  e_time,  s_date, s_month,  s_year,  s_time)) {
		} else {
			function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	        recurTask.AddRecurring(recurPeriod,recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,"timed",toDoList);
		}
	}
}


//Add the task to the toDoList if it has a floating type
//Successful added message is shown to user if the task is added successfully
//Failure added message is shown to user if the task already existed
//precondition : user added a floating type
//postcondition : add float task to toDoList if the task is not duplicated
void defaultclass::addFloatTask(string description,vector<task> &toDoList,storage *store) {
	storage *stor = store;
	logic function;
	assert(description.length() != 0);
	task datainput(description);
	datainput.addFloatItem();

	if (system("CLS")) system("clear");
	if(!store->isFloatDuplicated(datainput, toDoList)) {
		toDoList.push_back(datainput);
		function.printMessage(description, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	} else {
		function.printMessage(MESSAGE_DUPLICATE_FLOAT_TASK);
	}
}

//Add the task to the toDoList if it has a deadline type
//Successful added message is shown to user if the task is added successfully
//Failure added message is shown to user if the task already existed or there are errors in the user inputs
//precondition : user added a deadline type
//postcondition : add deadline task to toDoList if the task entered has no errors
void defaultclass::addDeadlineTask(string description,vector<task> &toDoList,storage *store) {
	string text;
	parser parse;
	storage *stor = store;
	logic function;
	int e_date, e_month, e_year, e_time;

	assert(description.length() != 0);
	parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
	task datainput(text);
	datainput.addDeadlineItem(e_date, e_month, e_year, e_time);

	if(printErrorMsgForAddDeadlineTask( text,datainput,toDoList, store, e_date,  e_month,  e_year,  e_time)) {
	} else {
		toDoList.push_back(datainput);
		function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	}
}

//Add the task to the toDoList if it has a timed type
//Successful added message is shown to user if the task is added successfully
//Failure added message is shown to user if the task already existed or there are errors in the user inputs
//precondition : user added a timed type
//postcondition : add timed task to toDoList if the task entered has no errors
void defaultclass::addTimedTask(string description,vector<task> &toDoList,storage *store) {
	string text;
	parser parse;
	logic function;
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
	}
}

//User can delete an unwanted task by key in delete <index>
//This can be done in the default page or after the user has operate the search or display command
//precondition : the index of the unwanted task is read in
//postcondition : delete the unwanted task according to its index shown on the console
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

//clear all content in the toDoList
//precondition : clear command is entered
//postcondition : vector toDoList is cleared
void defaultclass::clearTasks(string fileName,storage *store,vector<task> &toDoList, vector<undo> &undomemory) {
	logic function;
	undo undofunction;
	storage *stor=store;

	function.clearAll(toDoList);
    undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
    store->saveToSaveFile(fileName,toDoList);
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

	function.sorttext(defaultmemory.floatVec);
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

//Display all floating task in the default page
//precondition : none
//postcondition : floating task displayed in alphabetical order
void defaultclass::defaultFloatDisplay(defaultclass &defaultmemory) {
	for(int index = 0; index != defaultmemory.floatVec.size(); ++index) {
		cout << defaultmemory.floatVec[index].displayFloat(index) << endl;
	}
}

//Display all task to be finished by today in the default page
//precondition : none
//postcondition : today's tasks are displayed according to the end timing
void defaultclass::DisplayTaskFinishByToday(defaultclass &defaultmemory) {
	for(int i = 0; i != defaultmemory.todayTaskVec.size(); ++i){
		int s_day,s_month,s_year,e_day,e_month,e_year;

		s_day=defaultmemory.todayTaskVec[i].returnstartdate();
		s_month=defaultmemory.todayTaskVec[i].returnstartmonth();
		s_year=defaultmemory.todayTaskVec[i].returnstartyear();
		e_day=defaultmemory.todayTaskVec[i].returnenddate();
		e_month=defaultmemory.todayTaskVec[i].returnendmonth();
		e_year=defaultmemory.todayTaskVec[i].returnendyear();

		if(s_day==e_day && s_month==e_month && s_year==e_year) {
			cout << defaultmemory.todayTaskVec[i].displayDefaultTasksWithTwoTimes(i)<<endl;
		} else {
			cout << defaultmemory.todayTaskVec[i].displayDefaultTasks(i)<<endl;
		}
	}
}

//Display all task to be finished by tomorow in the default page
//precondition : none
//postcondition : tomorrow's tasks are displayed according to the end timing
void defaultclass::DisplayTaskFinishByTmr(defaultclass &defaultmemory) {
	for(int i = 0; i != defaultmemory.tomorTaskVec.size(); ++i) {
		int s_day,s_month,s_year,e_day,e_month,e_year;

		s_day=defaultmemory.tomorTaskVec[i].returnstartdate();
		s_month=defaultmemory.tomorTaskVec[i].returnstartmonth();
		s_year=defaultmemory.tomorTaskVec[i].returnstartyear();
		e_day=defaultmemory.tomorTaskVec[i].returnenddate();
		e_month=defaultmemory.tomorTaskVec[i].returnendmonth();
		e_year=defaultmemory.tomorTaskVec[i].returnendyear();

		if(s_day==e_day && s_month==e_month && s_year==e_year) {
			cout << defaultmemory.tomorTaskVec[i].displayDefaultTasksWithTwoTimes(i)<<endl;
		} else {
		cout << defaultmemory.tomorTaskVec[i].displayDefaultTasks(i)<<endl;
		}
	}
}

//Check if the day, month, year correspond to today's system timing
//precondition : take in the day, month and year parameters
//postcondition : return true if the date mathces today's system date, else return falase
bool defaultclass::checkIfIsToday(int e_day,int e_month,int e_year) {
	parser parse;
	if(e_day == parse.getSystemDay() && e_month == parse.getSystemMonth() && e_year == parse.getSystemYear()) {
		return true;
	} else {
		return false;
	}
}

//Check if the day, month, year correspond to tomorrow's system timing
//precondition : take in the day, month and year parameters
//postcondition : return true if the date mathces tomorrow's system date, else return falase
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
	storage *stor = store;
	if (system("CLS")) system("clear");
	if(store->isDeadlineDuplicated(datainput, toDoList)) {
		function.printMessage(MESSAGE_DUPLICATE_DEADLINE_TASK);
	} else if(!function.checkIsDateOverdue(e_date,e_month,e_year,e_time) && !function.isValidTime(e_time)) {
		function.printMessage(MESSAGE_DATE_OVERDUE);
		cout << "and";
		function.printMessage(MESSAGE_TIME_INVALID);
	} else if(!function.isValidDate(e_date,e_month,e_year) && !function.isValidTime(e_time)) {
		function.printMessage(MESSAGE_DATE_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_TIME_INVALID);
	} else if (!function.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
			function.printMessage(MESSAGE_DATE_OVERDUE);
	} else if(!function.isValidDate(e_date,e_month,e_year)) {
			function.printMessage(MESSAGE_DATE_INVALID);
	} else if (!function.isValidTime(e_time)) {
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
	storage *stor = store;
	bool result = true;
	if (system("CLS")) system("clear");
	if (function.checkIfStartTimeIsEarlierThanEndTime(s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time)) {
		function.printMessage(MESSAGE_START_AND_END_TIME_ERROR);
	} else if (store->isTimeClashed(datainput, toDoList)) {
		function.printMessage(MESSAGE_TIME_SLOT_CLASH);
	} else if(!function.checkIsDateOverdue(s_date,s_month,s_year,s_time) && !function.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
	} else if(!function.isValidTime(s_time) && !function.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_START_DATE_INVALID);
	} else if(!function.checkIsDateOverdue(e_date,e_month,e_year,e_time) && !function.isValidTime(e_time)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if(!function.isValidTime(e_time) && !function.isValidDate(e_date,e_month,e_year)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_INVALID);
	} else if(!function.isValidDate(e_date,e_month,e_year)&&!function.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_BOTH_DATE_INVALID);
	} else if(!function.isValidTime(e_time) && !function.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_TIME_INVALID);
	} else if(!function.checkIsDateOverdue(s_date,s_month,s_year,s_time) && !function.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if(!function.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
	} else if(!function.isValidTime(e_time)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
	} else if (!function.checkIsDateOverdue(s_date,s_month,s_year,s_time)) {
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
	} else if (!function.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if (!function.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_START_DATE_INVALID);
	} else if(!function.isValidDate(e_date,e_month,e_year)) {
		function.printMessage(MESSAGE_END_DATE_INVALID);
	} else{
		return false;
	}
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

	if(temp == "float"){
		size = defaultmemory.floatVec.size();

		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		} else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}
		originindex = defaultmemory.floatVec[index].returntempnum();
	} else if(temp == "today"){ 
		   size = defaultmemory.todayTaskVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		} else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}
		originindex = defaultmemory.todayTaskVec[index].returntempnum();
	} else if(temp == "tomorrow"){
		size = defaultmemory.tomorTaskVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		} else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}
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
		}
		originindex = tempVec[index].returntempnum();
	}
	return true;
}

//function updates the defaultmemory 
//The task will be pushed back into today's task vector, tomorrow's task vector and float task vector respectively if task
//is due today, tomorrow or has a floating type
//precondition : toDoList is read in
//postcondition : tasks are being categorised and pushed into respective vectors
void defaultclass::updatedefaultmemory(vector<task> &toDoList){
	vector<task> floatVec_;
	task temp;
	int index, i = 0, j = 0, k = 0;

	for(index = 0; index != toDoList.size(); ++index) {
		if(checkIfIsToday(toDoList[index].returnenddate(),toDoList[index].returnendmonth(),toDoList[index].returnendyear())){
			   todayTaskVec.push_back(toDoList[index]);
			   todayTaskVec[i].inserttempnum(index);
			   i++;
		} else if(checkIfIsTomorrow(toDoList[index].returnenddate(),toDoList[index].returnendmonth(),toDoList[index].returnendyear())) {
			   tomorTaskVec.push_back(toDoList[index]);
			   tomorTaskVec[j].inserttempnum(index);
			   j++;
		} else if(toDoList[index].returntype() =="float"){
			floatVec_.push_back(toDoList[index]);
			floatVec_[k].inserttempnum(index);
			k++;
		}
	}
	floatVec = floatVec_;
}
