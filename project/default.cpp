#include "default.h"
#include <iostream>
#include <sstream>
#include <fstream> 
#include <algorithm>
#include <windows.h>
#include <ctime>

void defaultclass::updatedefaultmemory(vector<task> &toDoList){
	vector<task> floatVec_;
	task temp;
	int index, i=0, j=0, k=0;

	for(index = 0; index != toDoList.size(); ++index) {
		if(checkIfIsToday(toDoList[index].returnenddate(),toDoList[index].returnendmonth(),toDoList[index].returnendyear())){
			   todayTaskVec.push_back(toDoList[index]);
			   todayTaskVec[i].inserttempnum(index);
			   i++;
		}else if(checkIfIsTomorrow(toDoList[index].returnenddate(),toDoList[index].returnendmonth(),toDoList[index].returnendyear())) {
			   tomorTaskVec.push_back(toDoList[index]);
			   tomorTaskVec[j].inserttempnum(index);
			   j++;
		}else if(toDoList[index].returntype() =="float"){
			floatVec_.push_back(toDoList[index]);
			floatVec_[k].inserttempnum(index);
			k++;
		}
	}
	floatVec = floatVec_;
}

string defaultclass::getRecurruingCommandWord(string description) {
	int start = getStartPosition(description);
	int end = getEndPosition(description);
	string recurringCommandWord = description.substr(start, end - start);	
	return recurringCommandWord;
}

int defaultclass::getStartPosition(string description) {
	int start = description.find_first_not_of(" ");
	return start;
}

int defaultclass::getEndPosition(string description) {
	int end = description.find_first_of(" ");
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

void defaultclass::addRecurringTask(string recurringCommandWord, string description, vector<task> & toDoList) {
	string text;
	parser parse;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	int end, posOfFrom, posOfBy;
	
	end = getEndPosition(description);
	posOfBy = getPosOfBy(description);
	posOfFrom = getPosOfFrom(description);

	description = description.substr(end+1);
	addDeadlineAndTimedRecurringTask(description,recurringCommandWord,toDoList);
}

void defaultclass::addDeadlineAndTimedRecurringTask(string description,string recurringCommandWord,vector<task> &toDoList) {
	string text;
	parser parse;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	int end, posOfFrom, posOfBy;

	end = getEndPosition(description);
	posOfBy = getPosOfBy(description);
	posOfFrom = getPosOfFrom(description);
	
	if(parse.checktype(description) == "deadline") {
		addDeadlineRecurTask(description,recurringCommandWord,toDoList);
	} else {
		addTimedRecurTask(description,recurringCommandWord,toDoList);
	}
}

void defaultclass::addDeadlineRecurTask(string description,string recurringCommandWord, vector<task> &toDoList) {
	string text;
	parser parse;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	int end, posOfFrom, posOfBy;

	end = getEndPosition(description);
	posOfBy = getPosOfBy(description);
	posOfFrom = getPosOfFrom(description);

	string type;
	type = "deadline";

	    text = description.substr(end+1,posOfBy-1-end);
		parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
		recurringTask recurTask(text,0,e_time);
		recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,type,toDoList);
}

void defaultclass::addTimedRecurTask(string description,string recurringCommandWord, vector<task> &toDoList) {
	string text;
	parser parse;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	int end, posOfFrom, posOfBy;

	end = getEndPosition(description);
	posOfBy = getPosOfBy(description);
	posOfFrom = getPosOfFrom(description);

	string type;
	type = "timed";

	text = description.substr(end+1,posOfFrom-1-end);
		parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
		recurringTask recurTask(text,s_time,e_time);
		recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,type,toDoList);
}

void defaultclass::addFloatTask(string description,vector<task> &toDoList,storage *store) {
	storage *stor = store;
	string text;
	logic function;

	task datainput(description);
	datainput.addItemtypeone();
	if (system("CLS")) system("clear");
	if(!store->isFloatDuplicated(datainput, toDoList)) {
		toDoList.push_back(datainput);
		function.printMessage(text, "succesfully added");
	} else {
		function.printMessage("float task exist already");
	}
}

void defaultclass::addDeadlineTask(string description,vector<task> &toDoList,storage *store) {
	string text;
	parser parse;
    logic function;
	storage *stor=store;
	int e_date, e_month, e_year, e_time;


	parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
						task datainput(text);
						datainput.addItemtypetwo(e_date, e_month, e_year, e_time);
						printErrorMsgForAddDeadlineTask( datainput,toDoList, store, e_date,  e_month,  e_year,  e_time);
}

void defaultclass::printErrorMsgForAddDeadlineTask(task datainput, vector<task> &toDoList,storage *store,
												   int e_date, int e_month, int e_year, int e_time) {
	string text;
    logic function;
	storage *stor=store;

	if (system("CLS")) system("clear");
						if(!store->isDeadlineDuplicated(datainput, toDoList)){
							if(!function.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
								function.printMessage("Date entered is already overdued");
							} else if(function.isValidDate(e_date,e_month,e_year)&&function.isValidTime(e_time)&&function.isValidTime(e_time)) {
								toDoList.push_back(datainput);
								function.printMessage(text, "succesfully added");
							} else if(!function.isValidDate(e_date,e_month,e_year)) {
								function.printMessage("invalid input date, try again");
							} else if(!function.isValidTime(e_time)) {
								function.printMessage("invalid input timing, try again");
							} 
						}else {
							function.printMessage("deadline task exist already");
						}
}

void defaultclass::addTimedTask(string description,vector<task> &toDoList,storage *store) {
	string text;
	parser parse;
    logic function;
	storage *stor=store;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;

	parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						task datainput(text);
						datainput.addItemtypethree(s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						printErrorMsgForAddTimedTask(datainput, toDoList, store,e_date,  e_month,  e_year,  
							                         e_time,  s_date, s_month, s_year,  s_time); 
						
}

void defaultclass::printErrorMsgForAddTimedTask(task datainput, vector<task> &toDoList,storage *store,
												   int e_date, int e_month, int e_year, int e_time, int s_date,int s_month,
												   int s_year, int s_time) {
	string text;
    logic function;
	storage *stor=store;

	if (system("CLS")) system("clear");
						if(!store->isTimeClashed(datainput, toDoList)){
							if(!function.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
								function.printMessage("Ending date entered is already overdued");
							} else if(!function.checkIsDateOverdue(s_date,s_month,s_year,s_time)) {
								function.printMessage("Starting date entered is already overdued");
							}else if(!function.isValidDate(e_date,e_month,e_year)&&!function.isValidDate(s_date,s_month,s_year)) {
								cout << "inValid Start and End Dates, try again" << endl;
							}else if(!function.isValidDate(s_date,s_month,s_year)) {
								cout << "inValid Start Date, try again" << endl;
							}else if(!function.isValidDate(e_date,e_month,e_year)) {
								cout << "inValid End Date, try again" << endl;
							}else if(!function.isValidTime(s_time)) {
								cout << "invalid Start Timing, try again" << endl;
							} else if(!function.isValidTime(e_time)) {
								cout << "invalid End Timing, try again" << endl;
							} else{
								toDoList.push_back(datainput);
								function.printMessage(text, "succesfully added");
							} 
						} else {
							function.printMessage("timed slot clashes");
						}
}

void defaultclass::deleteTask(string description,vector<task> &toDoList,storage *store,vector<undo> &undomemory) {
	
	int originindex;
    logic function;
	undo undofunction;
	storage *stor=store;
	vector<task> tempVec;
	defaultclass defaultmemory;

	if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
				function.deleteItem(originindex, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				if (system("CLS")) system("clear");
				showDefaultTaskList(toDoList, defaultmemory);
				store->saveToSaveFile(fileName,toDoList);
				}
}

void defaultclass::displayTask(string description, vector<task> &toDoList) {
	logic function;
	vector<task> tempVec;

	tempVec.clear();
	if (system("CLS")) system("clear");
    function.display(toDoList, tempVec, fileName, description);
}

void defaultclass::clearTasks(storage *store,vector<task> &toDoList, vector<undo> &undomemory) {
	logic function;
	undo undofunction;
	storage *stor=store;

	function.clearAll(toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store->saveToSaveFile(fileName,toDoList);
}

void defaultclass::defaultexecuteCommand(storage *store, string &command, string &description, vector<task> &toDoList, vector<undo> &undomemory, undo &currentundomemory) {
	
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
				int end, posOfBy, posOfFrom;

				end = getEndPosition(description);
				posOfBy = getPosOfBy(description);
			    posOfFrom = getPosOfFrom(description);
				recurringCommandWord = getRecurruingCommandWord(description);

				if(recurringCommandWord=="daily") {
					recurringCommandWord=="daily";
					addRecurringTask(recurringCommandWord,description, toDoList);
				} else if(recurringCommandWord=="weekly") {
					recurringCommandWord=="weekly";
					addRecurringTask(recurringCommandWord,description, toDoList);
				} else if (recurringCommandWord=="monthly") {
					recurringCommandWord=="monthly";
					addRecurringTask(recurringCommandWord,description, toDoList);
				} else if(recurringCommandWord=="yearly") {
					recurringCommandWord=="yearly";
					addRecurringTask(recurringCommandWord,description, toDoList);
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
				deleteTask(description,toDoList,store,undomemory);
			} else if(command=="display") {
				displayTask(description,toDoList);
			} else if(command=="clear") {
				clearTasks( store,toDoList,undomemory);
			} else if(command == "edit") {
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)) {
					function.editTask(originindex ,description, toDoList);
					undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
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
				showDefaultTaskList(toDoList, defaultmemory);
			} else if(command == "search") {
				function.searchTask(toDoList, tempVec, fileName, description);
			} else if(command == "default") {
				showDefaultTaskList(toDoList, defaultmemory);
			}
}
cout << endl << "command: ";
cin >> command;
getline(cin,description);
}
}

bool defaultclass::checkfororiginalindex(string description, defaultclass defaultmemory, vector<task> &tempVec, int &originindex){
	string temp;
	parser parse;
	logic function;
	unsigned int index;
	int size;

	istringstream in(description);
	in>> temp;
	in>> index;
	index = index -1;

	if(temp == "float"){
		size = defaultmemory.floatVec.size();

		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		}
		else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}
		originindex = defaultmemory.floatVec[index].returntempnum();
	}
	else if(temp == "today"){
		size = defaultmemory.todayTaskVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		}
		else if((index >= size)||(index < 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}

		originindex = defaultmemory.todayTaskVec[index].returntempnum();
	}
	else if(temp == "tomorrow"){
		size = defaultmemory.tomorTaskVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		}
		else if((index >= size)||(index <= 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}

		originindex = defaultmemory.tomorTaskVec[index].returntempnum();
	}
	else{
		istringstream intemp(description);
		intemp >> index;
		index = index - 1;

		size = tempVec.size();
		if(size==0){
			function.printMessage(ERROR_LIST_IS_EMPTY);
			return false;
		}
		else if((index >= size)||(index <= 0)){
			function.printMessage(INVALID_INDEX);
			return false;
		}

		originindex = tempVec[index].returntempnum();
	}
	return true;
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
	cout << endl << "[Floating]" << endl << endl;
	for(index = 0; index != defaultmemory.floatVec.size(); ++index) {
		cout << defaultmemory.floatVec[index].displayFloat(index) << endl;
	}

	cout << endl << "[Today: " <<  now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << "]" << "============================================================" << endl << endl;
	function.sortEndTime(defaultmemory.todayTaskVec);

	for(i = 0; i != defaultmemory.todayTaskVec.size(); ++i){
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

    cout << endl << "[Tomorrow: " <<  now->tm_mday +1 << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << "]" << "============================================================" << endl;
	function.sortEndTime(defaultmemory.tomorTaskVec);

	for(i = 0; i != defaultmemory.tomorTaskVec.size(); ++i){
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
	}cout <<endl;
}

bool defaultclass::checkIfIsToday(int e_day,int e_month,int e_year) {
	logic logic;
	if(e_day == logic.getSystemDay() && e_month == logic.getSystemMonth() && e_year == logic.getSystemYear()) {
		return true;
	} else {
		return false;
	}
}

bool defaultclass::checkIfIsTomorrow(int e_day,int e_month,int e_year) {
	logic logic;
	if(e_day == (logic.getSystemDay()+1) && e_month == logic.getSystemMonth() && e_year == logic.getSystemYear()) {
		return true;
	} else {
		return false;
	}
}
