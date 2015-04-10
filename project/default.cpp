#include "default.h"
#include <iostream>
#include <sstream>
#include <fstream> 
#include <algorithm>
#include <windows.h>
#include <ctime>

void defaultclass::defaultexecuteCommand(string fileName,storage *store, string &command, string &description, vector<task> &toDoList, vector<undo> &undomemory, undo &currentundomemory) {
	string text;
	parser parse;
    logic function;
	undo undofunction;
	storage *stor=store;
	vector<task> tempVec;
	defaultclass defaultmemory;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time, originindex;

	defaultmemory.updatedefaultmemory(toDoList);
	
	while(command != "exit"){
		parse.trimString(description);
		if(parse.isValidCommand(command, description)) {
			if(command == "add" || command =="+") {
				string recurringCommandWord;
				int end, posOfBy, posOfFrom, recurPeriod;
				
                //5 daily name /bysdklfjklsjf
				//daily
				end = getEndPosition(description);
				posOfBy = getPosOfBy(description);
			    posOfFrom = getPosOfFrom(description);
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
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)) {
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
				function.searchTask(toDoList, tempVec, fileName, description);
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

//weekly
//10 weekly

int defaultclass::getRecurPeriod(string description) {
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

string defaultclass::getRecurruingCommandWord(string description) {
	int start = getStartPosition(description);
	int end = getEndPosition(description);

	string recurringCommandWord = description.substr(start, end - start);	

	return recurringCommandWord;
}

int defaultclass::getStartPosition(string description) {
	int start;
	
	start = description.find_first_not_of(" ");
	
	return start;
}

int defaultclass::getEndPosition(string description) {
	int end;

	end = description.find_first_of(" ");

	return end;
}

int defaultclass::getPosOfBy(string description) {
    int posOfBy;

	posOfBy = description.find("by");

	return posOfBy;
}

int defaultclass::getPosOfFrom(string description) {
	int posOfFrom;

	posOfFrom = description.find("from");

	return posOfFrom;
}

void defaultclass::addRecurringTask(int recurPeriod,string recurringCommandWord, string description, vector<task> & toDoList,storage *store ) {
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time, end, posOfFrom, posOfBy;
	parser parse;
	string text;
	storage *stor = store;
	logic function;

	end = getEndPosition(description);
	posOfBy = getPosOfBy(description);
	posOfFrom = getPosOfFrom(description);

	description = description.substr(end+1);

	if(parse.checktype(description) == "deadline") {
		text = description.substr(end+1,posOfBy-1-end);
	    parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
	    recurringTask recurTask(text,0,e_time);
		task datainput(text);
		if(printErrorMsgForAddDeadlineTask( text,  datainput, toDoList, store, e_date,  e_month,  e_year,  e_time)) {
		} else {
			function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	        recurTask.AddRecurring(recurPeriod,recurringCommandWord,e_date,e_month,e_year,0,0,0,"deadline",toDoList);
		}
	} else {
		text = description.substr(end+1,posOfFrom-1-end);
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

void defaultclass::addFloatTask(string description,vector<task> &toDoList,storage *store) {
	storage *stor = store;
	logic function;

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

void defaultclass::addDeadlineTask(string description,vector<task> &toDoList,storage *store) {
	string text;
	parser parse;
	storage *stor = store;
	logic function;
	int e_date, e_month, e_year, e_time;


	parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
	task datainput(text);
	datainput.addDeadlineItem(e_date, e_month, e_year, e_time);

	if(printErrorMsgForAddDeadlineTask( text,datainput,toDoList, store, e_date,  e_month,  e_year,  e_time)) {
	} else {
		toDoList.push_back(datainput);
		function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	}
}

void defaultclass::addTimedTask(string description,vector<task> &toDoList,storage *store) {
	string text;
	parser parse;
	logic function;
	storage *stor = store;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;

	parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
	task datainput(text);
	datainput.addTimedItem(s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);

	if(printErrorMsgForAddTimedTask(text,datainput, toDoList, store,e_date,  e_month,  e_year, e_time,  s_date, s_month, s_year,  s_time)) {
	} else {
		toDoList.push_back(datainput);
		function.printMessage(text, MESSAGE_ITEM_ADDED_SUCCESSFULLY);
	}
}

void defaultclass::deleteTask(string fileName,string description, vector<task> &toDoList, storage *store, vector<undo> &undomemory, vector<task> &tempVec, defaultclass &defaultmemory) {
	int originindex;
    logic function;
	undo undofunction;
	storage *stor=store;

	if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
		function.deleteItem(originindex, toDoList);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		showDefaultTaskList(toDoList, defaultmemory);
		store->saveToSaveFile(fileName,toDoList);
	}
}

void defaultclass::displayTask(string fileName,string description, vector<task> &toDoList, vector<task> &tempVec) {
	logic function;

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
	defaultDeadlineDisplay(defaultmemory);
	

    cout << endl << "[Tomorrow: " <<  now->tm_mday +1 << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << "]" << "===========================================================" << endl;
	function.sortEndTime(defaultmemory.tomorTaskVec);
	defaultTimedDisplay(defaultmemory);
	
	cout <<endl;
}

void defaultclass::defaultFloatDisplay(defaultclass &defaultmemory) {
	for(int index = 0; index != defaultmemory.floatVec.size(); ++index) {
		cout << defaultmemory.floatVec[index].displayFloat(index) << endl;
	}
}

void defaultclass::defaultDeadlineDisplay(defaultclass &defaultmemory) {
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

void defaultclass::defaultTimedDisplay(defaultclass &defaultmemory) {
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

bool defaultclass::printErrorMsgForAddDeadlineTask(string text, task datainput, vector<task> &toDoList, storage *store, 
												   int e_date, int e_month, int e_year, int e_time) {
	
    logic function;
	storage *stor = store;
	bool result = true;

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

//upadte
bool defaultclass::printErrorMsgForAddTimedTask(string text,task datainput, vector<task> &toDoList,storage *store, int e_date, 
												int e_month, int e_year, int e_time, int s_date,int s_month, int s_year, int s_time) {
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

bool defaultclass::checkfororiginalindex(string description, defaultclass defaultmemory, vector<task> &tempVec, int &originindex){
	string temp;
	parser parse;
	logic function;
	int index, size;


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