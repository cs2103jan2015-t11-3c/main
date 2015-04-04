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
		}
	}

	for(index = 0; index != toDoList.size(); ++index) {
		if(checkIfIsTomorrow(toDoList[index].returnenddate(),toDoList[index].returnendmonth(),toDoList[index].returnendyear())) {
			   tomorTaskVec.push_back(toDoList[index]);
			   tomorTaskVec[j].inserttempnum(index);
			   j++;
		}
	}


	for(index = 0; index != toDoList.size(); ++index){
		if(toDoList[index].returntype() =="float"){
			floatVec_.push_back(toDoList[index]);
			floatVec_[k].inserttempnum(index);
			k++;
		}
	}
	floatVec = floatVec_;
}

void defaultclass::defaultexecuteCommand(storage *store, string &command, string &description, vector<task> &toDoList, vector<undo> &undomemory, 
										 undo &currentundomemory) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time, originindex;
	vector<task> tempVec;
    logic function;
	storage *stor=store;
	parser parse;
	undo undofunction;
	defaultclass defaultmemory;

	defaultmemory.updatedefaultmemory(toDoList);
	
	while(command!="exit"){
		parse.trimString(description);

		if(parse.isValidCommand(command, description)){
			if(command=="add" ||command =="+") {

				size_t start = description.find_first_not_of(" ");
				size_t end = description.find_first_of(" ");
				string recurringCommandWord = description.substr(start, end - start);
				if(recurringCommandWord=="daily") {
					description = description.substr(end + 1);
					if(parse.checktype(description) == 2) {
						parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else if(recurringCommandWord=="weekly") {
					description = description.substr(end + 1);
					if(parse.checktype(description) == 2) {
						parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else if (recurringCommandWord=="monthly") {
					description = description.substr(end + 1);
					if(parse.checktype(description) == 2) {
						parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else if(recurringCommandWord=="yearly") {
					description = description.substr(end + 1);
					if(parse.checktype(description) == 2) {
						parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else {
					if(parse.checktype(description) == 1){
						task datainput(description);
						datainput.addItemtypeone();
						if(!store->isFloatDuplicated(datainput, toDoList)){
							toDoList.push_back(datainput);
							function.printMessage(text, "succesfully added");
						}
						else
							function.printMessage("float task exist already");
					}
					else if(parse.checktype(description) == 2){
						parse.splitinputDeadline(description, text, e_date, e_month, e_year, e_time);
						task datainput(text);
						datainput.addItemtypetwo(e_date, e_month, e_year, e_time);
						if(!store->isDeadlineDuplicated(datainput, toDoList)){
							if(!function.checkIsDateOverdue(e_date,e_month,e_year)) {
								function.printMessage("Date entered is already overdued");
							} if(function.isValidDate(e_date,e_month,e_year)&&function.isValidTime(e_time)&&function.isValidTime(e_time)) {
								toDoList.push_back(datainput);
								function.printMessage(text, "succesfully added");
							} if(!function.isValidDate(e_date,e_month,e_year)) {
								function.printMessage("invalid input date, try again");
							} if(!function.isValidTime(e_time)) {
								function.printMessage("invalid input timing, try again");
							} 
						}else {
							function.printMessage("deadline task exist already");
						}
					}
					else if(parse.checktype(description) == 3){
						parse.splitinputTimed(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						task datainput(text);
						datainput.addItemtypethree(s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						if(!store->isTimeClashed(datainput, toDoList)){
							if(!function.checkIsDateOverdue(e_date,e_month,e_year)) {
								function.printMessage("Ending date entered is already overdued");
							}if(!function.checkIsDateOverdue(s_date,s_month,s_year)) {
								function.printMessage("Starting date entered is already overdued");
							}if(!function.isValidDate(e_date,e_month,e_year)&&!function.isValidDate(s_date,s_month,s_year)) {
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
						} else
							function.printMessage("timed slot clashes");
					} 
				}
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				showDefaultTaskList(toDoList, defaultmemory);
				store->saveToSaveFile(fileName,toDoList);
			}//finish add function
			else if(command=="delete"||command=="-"||command=="remove") {
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
				function.deleteItem(originindex, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				showDefaultTaskList(toDoList, defaultmemory);
				store->saveToSaveFile(fileName,toDoList);
				}
			}
			else if(command=="display") {
				tempVec.clear();
				function.display(toDoList, tempVec, fileName, description);
			}
			
			else if(command=="clear") {
				function.clearAll(toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store->saveToSaveFile(fileName,toDoList);
			}
			else if(command == "edit") {
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
				function.editTask(originindex ,description, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				showDefaultTaskList(toDoList, defaultmemory);
				store->saveToSaveFile(fileName,toDoList);
				}
			}
			else if(command=="exit") {
				store->saveToSaveFile(fileName,toDoList);
				return;
			}
			else if(command == "done") {
				if(checkfororiginalindex(description, defaultmemory, tempVec, originindex)){
				function.markcompleted(originindex, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				}
			}
			else if(command == "undo"){
				currentundomemory = undomemory[undomemory.size()-2];
				toDoList = currentundomemory.returnmemory();
				undomemory.pop_back();
				showDefaultTaskList(toDoList, defaultmemory);
			}
			else if(command == "search") {
				function.searchTask(toDoList, tempVec, fileName, description);
				showDefaultTaskList(toDoList, defaultmemory);
			}
			else if(command == "default") {
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
	int index, i=0, j=0, k=0;
	logic function;
	vector<task> tempVec;	
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

	defaultmemory.todayTaskVec.clear();
	defaultmemory.tomorTaskVec.clear();
	defaultmemory.floatVec.clear();
	defaultmemory.updatedefaultmemory(toDoList);
	//*************************(1) float task (1)****************************************************************************
	function.sorttext(defaultmemory.floatVec);
	
	int pos=(int)((80-15)/2);
	for(int i=0;i<pos;i++) {
			cout<<" ";
	}
	cout << "Floating tasks:" << endl << endl;

	for(index = 0; index != defaultmemory.floatVec.size(); ++index) {
		int size;
		size = (defaultmemory.floatVec[index].displayfloat()).size();
		int pos=(int)((80-size)/2);
		for(int i=0;i<pos;i++) {
			cout<<" ";
		}
		cout << defaultmemory.floatVec[index].displayFloat(index) << endl;
	}

	/*
	//*************************(2) deadline task (2)****************************************************************************
    function.sortdates(defaultmemory.deadlineVec);
	function.sorttime(defaultmemory.deadlineVec);

	cout << endl;
	std::cout << endl <<  "********************************************************************************" << endl;
	int pos1=(int)((80-15)/2);
	for(int i=0;i<pos1;i++) {
			cout<<" ";
	}
	
	cout <<  "Deadline tasks:" << endl << endl;


	for(index = 0; index != defaultmemory.deadlineVec.size(); ++index) {
		int size;
		size = (defaultmemory.deadlineVec[index].displaydeadline()).size();
		int pos=(int)((80-size)/2);
		for(int i=0;i<pos;i++) {
			cout<<" ";
		}
		cout << defaultmemory.deadlineVec[index].displayDeadline(index) << endl;
	}


	//*************************(3) timed task (3)****************************************************************************
	function.sortdates(defaultmemory.timedVec);
	function.sorttime(defaultmemory.timedVec);
	
	cout << endl;
	std::cout << endl <<  "********************************************************************************" << endl;
	int pos2=(int)((80-12)/2);
	for(int i=0;i<pos2;i++) {
			cout<<" ";
	}
	cout <<  "Timed tasks:" << endl << endl;
	


	for(index = 0; index != defaultmemory.timedVec.size(); ++index) {
		int size;
		size = (defaultmemory.timedVec[index].displaytimed()).size();
		int pos=(int)((80-size)/2);
		for(int i=0;i<pos;i++) {
			cout<<" ";
		}
	    cout << defaultmemory.timedVec[index].displayTimed(index) << endl;
	}
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << endl <<  "********************************************************************************";
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);*/

	//=========================================================Today===================================================================

	cout << "[Today: " <<  now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << "]" << 
		     "============================================================" << endl << endl;
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
	cout <<endl;


	//========================================================Tomorrow=================================================================
	cout << "[Tomorrow: " <<  now->tm_mday +1 << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900 << "]" << 
		     "============================================================" << endl;

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
	}
	cout <<endl;

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
