#include "default.h"
#include <iostream>
#include <sstream>
#include <fstream> 
#include <algorithm>
#include <windows.h>

void defaultclass::defaultexecuteCommand(string &command, string &description, vector<task> &toDoList, vector<undo> &undomemory, undo &currentundomemory) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	vector<task> tempVec;
    logic function;
	storage store;
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
						parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else if(recurringCommandWord=="weekly") {
					description = description.substr(end + 1);
					if(parse.checktype(description) == 2) {
						parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else if (recurringCommandWord=="monthly") {
					description = description.substr(end + 1);
					if(parse.checktype(description) == 2) {
						parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else if(recurringCommandWord=="yearly") {
					description = description.substr(end + 1);
					if(parse.checktype(description) == 2) {
						parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,0,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,0,0,0,2,toDoList);
					} else {
						parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
						recurringTask recurTask(description,s_time,e_time);
						recurTask.AddRecurring(recurringCommandWord,e_date,e_month,e_year,s_date,s_month,s_year,2,toDoList);
					}
				} else {
				if(parse.checktype(description) == 1){
					task datainput(description);
					datainput.addItemtypeone();
					if(!store.isFloatDuplicated(datainput, toDoList))
					       toDoList.push_back(datainput);
					else
						function.printMessage("float task exist already");
				}
				else if(parse.checktype(description) == 2){
					parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
					task datainput(description);
					datainput.addItemtypetwo(e_date, e_month, e_year, e_time);
					if(!store.isDeadlineDuplicated(datainput, toDoList)){
						if(!function.checkIsDateOverdue(e_date,e_month,e_year)) {
							function.printMessage("Date entered is already overdued");
						} if(function.isValidDate(e_date,e_month,e_year)&&function.isValidTime(e_time)&&function.isValidTime(e_time)) {
					       toDoList.push_back(datainput);
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
					parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
					task datainput(description);
					datainput.addItemtypethree(s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
					if(!store.isTimeClashed(datainput, toDoList)){
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
						} 
					} else
						function.printMessage("timed slot clashes");
				} 
				}
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}//finish add function
			else if(command=="delete"||command=="-"||command=="remove") {

				function.deleteItem(checkfororiginalindex(description, defaultmemory, tempVec), toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="display") {
				tempVec.clear();
				function.display(toDoList, tempVec, fileName, description);
			}
			
			else if(command=="clear") {
				function.clearAll(toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command == "edit") {
				function.editTask(checkfororiginalindex(description, defaultmemory, tempVec),description, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="exit") {
				store.saveToSaveFile(fileName,toDoList);
				return;
			}
			else if(command == "done") {
				function.markcompleted(checkfororiginalindex(description, defaultmemory, tempVec), toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
			}
			else if(command == "undo"){
				currentundomemory = undomemory[undomemory.size()-2];
				toDoList = currentundomemory.returnmemory();
				undomemory.pop_back();
			}
			else if(command == "search") {
				function.searchTask(toDoList, tempVec, fileName, description);
			}
			else if(command == "default") {
				showDefaultTaskList(toDoList);
			}

		}
		cout << endl << "command: ";
		cin >> command;
		getline(cin,description);
	}

}

int defaultclass::checkfororiginalindex(string description, defaultclass defaultmemory, vector<task> &tempVec){
	string temp;
	parser parse;
	int index, originindex;

	istringstream in(description);
	in>> temp;
	in>> index;
	index = index -1;

	if(temp == "float"){
		originindex = defaultmemory.floatVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "deadline"){
	    originindex = defaultmemory.deadlineVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "timed"){
		originindex = defaultmemory.timedVec[index].returntempnum();
	    return originindex;
	}
	else{
		index = parse.convertStringToIntegerIndex(description);
		originindex = tempVec[index].returntempnum();
		return originindex;
	}
	return 0;
}

void defaultclass::updatedefaultmemory(vector<task> &toDoList){
	vector<task> tempVec, floatVec_, deadlineVec_, timedVec_;
	task temp;
	int index, i=0, j=0, k=0;

	floatVec.clear();
	deadlineVec.clear();
	timedVec.clear();

	for(index = 0; index != toDoList.size(); ++index)
		tempVec.push_back(toDoList[index]);

	for(index = 0; index != tempVec.size(); ++index){
		if(tempVec[index].returntype() == 1){
			floatVec_.push_back(tempVec[index]);
			floatVec_[i].inserttempnum(index);
			i++;
		}
		else if(tempVec[index].returntype() == 2){
			deadlineVec_.push_back(tempVec[index]);
			deadlineVec_[j].inserttempnum(index);
			j++;
		}
		else {
			timedVec_.push_back(tempVec[index]);
			timedVec_[k].inserttempnum(index);
			k++;
		}
	}
	floatVec = floatVec_;
	timedVec = timedVec_;
	deadlineVec = deadlineVec_;
}


void defaultclass::showDefaultTaskList(vector<task> &toDoList) {
	int index, i=0, j=0, k=0;
	logic function;
	vector<task> tempVec;	
	defaultclass defaultmemory;

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
		cout << defaultmemory.floatVec[index].displaytypeone(index) << endl;
	}


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
		cout << defaultmemory.deadlineVec[index].displaytypetwo(index) << endl;
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
	    cout << defaultmemory.timedVec[index].displaytypethree(index) << endl;

	}
	HANDLE hConsole;
    hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	std::cout << endl <<  "********************************************************************************";
	SetConsoleTextAttribute
    (hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
