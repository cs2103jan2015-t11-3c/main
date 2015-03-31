#include "search.h"

void searchclass::searchexecuteCommand(string &command, string &description, vector<task> &toDoList,  vector<undo> &undomemory, undo &currentundomemory) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	logic function;
	task datainput;
	storage store;
	parser parse;
	undo undofunction;
	vector<task> tempVec;
	defaultclass defaultfunction, defaultmemory;


	while(command!="exit"){
		parse.trimString(description);

		if(parse.isValidCommand(command, description)){
			if(command=="add" ||command =="+") {
				if(parse.checktype(description) == 1){
					parse.splitinputtypeone(description, text);
					datainput.addItemtypeone(text);
					if(!store.isFloatDuplicated(datainput, toDoList))
					       toDoList.push_back(datainput);
					else
						function.printMessage("float task exist already");
				}
				else if(parse.checktype(description) == 2){
					parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
					datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
					if(!store.isDeadlineDuplicated(datainput, toDoList)){
						if(function.isValidDate(e_date,e_month,e_year))
					       toDoList.push_back(datainput);
						else
							function.printMessage("inValid date, try again");
					}
					else
						function.printMessage("deadline task exist already");
				}
				else if(parse.checktype(description) == 3){
					parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
					datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
					if(!store.isTimeClashed(datainput, toDoList)){
						if(!function.isValidDate(e_date,e_month,e_year)&&!function.isValidDate(s_date,s_month,s_year)) {
							cout << "inValid Start and End Dates, try again" << endl;
						}else if(!function.isValidDate(s_date,s_month,s_year)) {
							cout << "inValid Start Date, try again" << endl;
						}else if(!function.isValidDate(e_date,e_month,e_year)) {
							cout << "inValid End Date, try again" << endl;
						}else{
							toDoList.push_back(datainput);}
					}
					else
						function.printMessage("timed slot clashes");
				}
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="delete"||command=="-"||command=="remove") {

				function.deleteItem(checkfororiginalindex(description, tempVec), toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="display") {
				cout << function.displayAll(toDoList);
			}
			else if(command=="clear") {
				function.clearAll(toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command == "edit") {
				function.editTask(checkfororiginalindex(description, tempVec),description, toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
				store.saveToSaveFile(fileName,toDoList);
			}
			else if(command=="exit") {
				store.saveToSaveFile(fileName,toDoList);
				return;
			}
			else if(command == "done") {
				function.markcompleted(checkfororiginalindex(description, tempVec), toDoList);
				undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
			}
			else if(command == "undo"){
				currentundomemory = undomemory[undomemory.size()-2];
				toDoList = currentundomemory.returnmemory();
				undomemory.pop_back();
			}
			else if(command == "default") {
				defaultfunction.showDefaultTaskList(toDoList);
				return;
			}
			else if(command == "search") {
				searchTask(toDoList, tempVec, fileName, description);
			}
		}

		cout << endl << "command: ";
		cin >> command;
		getline(cin,description);
	}

}

int searchclass::checkfororiginalindex(string description, vector<task>tempVec){
	string temp;
	int index, originindex;

	istringstream in(description);
	in>> index;
	index = index -1;

	originindex = tempVec[index].returntempnum();
	return originindex;

}


void searchclass::searchTask(vector<task> &toDoList, vector<task> &tempVec, string fileName, string description) {
	unsigned int i;
	task task;
	logic logic;

	tempVec.clear();

	for(i = 0; i < toDoList.size(); ++i) {
	if(!isCheckSearchStringDigit(description)) { //searched word is not a digit-->can only be found in task name
		unsigned int t = -1;
		t = (toDoList[i].returntext()).find(description);
		if(t != -1) {
			pushback(toDoList, tempVec, i);
	}
	} else if(isCheckSearchStringDigit(description)) { // searched word is a pure digit-->can only be found in time/date/month/year
		int convertedInt = convertNumStringToInt(description);
		if(toDoList[i].returnstarttime() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else if (toDoList[i].returnendtime() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else if(toDoList[i].returnstartdate() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else if (toDoList[i].returnenddate() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else if (toDoList[i].returnstartmonth() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else if (toDoList[i].returnendmonth() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else if (toDoList[i].returnstartyear() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else if (toDoList[i].returnendyear() == convertedInt) {
			pushback(toDoList, tempVec, i);
		} else {}
	}
	}
	cout << logic.displayAll(tempVec);
}

bool searchclass::isCheckSearchStringDigit(string description) {
	unsigned int i;
	bool result = true;
	for(i = 0; i < description.size(); ++i) {
		if(!isdigit(description[i])) {
			result = false;
		}
	}
return result;
}

int searchclass::convertNumStringToInt(string description) {
	int convertedNum;
	convertedNum = atoi(description.c_str());
    return convertedNum;
}

void searchclass::pushback(vector<task>& toDoList, vector<task>& tempVec, int index){
	task task_;
	task_ = toDoList[index];
	task_.inserttempnum(index);
	tempVec.push_back(task_);
}

