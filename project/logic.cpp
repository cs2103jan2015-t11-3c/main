#include "logic.h"
#include "parser.h"
#include "Task.h"
#include "storage.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <iostream>


void logic::readToDoListFromTextFile(string fileName, vector<task> &toDoList) {
	fstream textFile;
	string input;//deleted string temp
	textFile.open(fileName.c_str());

	//Remove the index of each line, eg: remove "1)" from "1) Some List Entry"
	//Adds the rest of the line to the to-do list after removing leading and following whitespaces
	while(getline(textFile,input)) {
		size_t pos = input.find('.');
		input = input.substr(pos+1);
		parser parse;

		parse.trimString(input);
		string text;
		int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
		task datainput;

		if(parse.checktype(input) == 1){
			parse.splitinputtypeone(input, text);
			datainput.addItemtypeone(text);
			toDoList.push_back(datainput);
		}
		else if(parse.checktype(input) == 2){
			parse.splitinputtypetwo(input, text, e_date, e_month, e_year, e_time);
			datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		else if(parse.checktype(input) == 3){
			parse.splitinputtypethree(input, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}

	}
	textFile.close();
}


void logic::executeCommand(string command, string description, vector<task> &toDoList, vector<task> &floatVec, vector<task> &deadlineVec, vector <task>timedVec) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
    logic function;
	task datainput;
	storage store;
	parser parse;
	bool result=true;

	parse.trimString(description);

	if(!parse.isValidCommand(command, description))
		return;
	else if(command=="add" ||command =="+") {
		if(parse.checktype(description) == 1){  //floating task: add swimming 
			parse.splitinputtypeone(description, text);
			datainput.addItemtypeone(text);
			toDoList.push_back(datainput); //push back the floating task "swimming" into the vector toDoList
		}
		else if(parse.checktype(description) == 2){
			parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
			if(!isValidDate(e_date,e_month,e_year)) {
				cout << "inValid date, try again" << endl;
			}
			datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		else if(parse.checktype(description) == 3){
			parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			if(!isValidDate(e_date,e_month,e_year)&&!isValidDate(s_date,s_month,s_year)) {
				cout << "inValid Start and End Dates, try again" << endl;
			}else if(!isValidDate(s_date,s_month,s_year)) {
				cout << "inValid Start Date, try again" << endl;
			}else if(!isValidDate(e_date,e_month,e_year)) {
				cout << "inValid End Date, try again" << endl;
			} else {
			datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
			}
		}
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="delete"||command=="-"||command=="remove") {

		function.deleteItem(checkfororiginalindex(description, floatVec, deadlineVec, timedVec), fileName, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="display"||command=="show") {
		cout << function.displayAll(fileName, toDoList);
		return;
	}
	else if(command=="clear"||command=="clear all") {
		function.clearAll(fileName, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command == "edit"||command=="modify"||command=="change") {
		function.editTask(checkfororiginalindex(description, floatVec, deadlineVec, timedVec),fileName,description, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="exit") {
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command == "done") {
		function.markcompleted(checkfororiginalindex(description, floatVec, deadlineVec, timedVec), fileName, toDoList);
		return;
	}
	else if(command == "search") {
		function.searchTask(toDoList, fileName, description);
		return;
	}

}

//check whether input date is valid function starts here
bool logic::isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

bool logic::isValidDate(unsigned short day,unsigned short month,unsigned short year){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (!year || !month || !day || month>12)
		return 0;
	if (isleapyear(year) && month==2)
		monthlen[1]++;
	if (day>monthlen[month-1])
		return 0;
	return 1;
}
//check whether input date is valid ends here

//search functions start here
void logic::searchTask(vector<task> &toDoList, string fileName, string description) {
	vector<task> tempVec;
	unsigned int i;
	task task;
	logic logic;
	for(i = 0; i < toDoList.size(); ++i) {
	if(!isCheckSearchStringDigit(description)) { //searched word is not a digit-->can only be found in task name
		unsigned int t = -1;
		t = (task.returntext(i,toDoList)).find(description);
		if(t != -1) {
			tempVec.push_back(toDoList[i]);
	}
	} else if(isCheckSearchStringDigit(description)) { // searched word is a pure digit-->can only be found in time/date/month/year
		int convertedInt = convertNumStringToInt(description);
		if(task.returnstarttime(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnendtime(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if(task.returnstartdate(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnenddate(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnstartmonth(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnendmonth(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnstartyear(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else if (task.returnendyear(i,toDoList) == convertedInt) {
			tempVec.push_back(toDoList[i]);
		} else {}
	}
	}
	cout << logic.displayAll(fileName, tempVec);
}

bool logic::isCheckSearchStringDigit(string description) {
	unsigned int i;
	bool result = true;
	for(i = 0; i < description.size(); ++i) {
		if(!isdigit(description[i])) {
			result = false;
		}
	}
return result;
}

int logic::convertNumStringToInt(string description) {
	int convertedNum;
	convertedNum = atoi(description.c_str());
return convertedNum;
}
//search functions end here

int logic::checkfororiginalindex(string description, vector<task>floatVec, vector<task>deadlineVec, vector<task>timedVec){
	string temp;
	parser parse;
	int index, originindex;

	istringstream in(description);
	in>> temp;
	in>> index;
	index = index -1;

	if(temp == "float"){
		originindex = floatVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "deadline"){
	    originindex = deadlineVec[index].returntempnum();
		return originindex;
	}
	else if(temp == "timed"){
		originindex = timedVec[index].returntempnum();
	    return originindex;
	}
	else{
		originindex = parse.convertStringToIntegerIndex(description);
		return originindex;
	}
}

string logic::displayAll(const string fileName, vector<task> &toDoList) {
	task temp;
	ostringstream oss;
	if(toDoList.size()==0)
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	else {
		for(unsigned i = 0; i < toDoList.size(); i++){
			if(temp.returntype(i,toDoList) == 1)
				oss << temp.displaytypeone(i, toDoList);
			else if(temp.returntype(i,toDoList) == 2)
				oss << temp.displaytypetwo(i, toDoList);
			else if(temp.returntype(i,toDoList) == 3)
			    oss << temp.displaytypethree(i, toDoList);
		}
	}
	return oss.str();
}

void logic::deleteItem(const int index, const string fileName, vector<task> &toDoList) {
	int size = toDoList.size();
	if(size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else if(index>=size||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else {
		toDoList.erase(toDoList.begin()+index);
		cout << "deleted";
	}
}

void logic::clearAll(const string fileName, vector<task> &toDoList) {
	toDoList.clear();
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY,fileName);
}

void logic::editTask(int index, string fileName, string description, vector<task> &toDoList) {
	string TextAfterIndex, VariableToChange, PartTochange, temp;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	task taskclass;
	char c;

	int size = toDoList.size();
	if(size == 0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
		return;
	}
	else if(index > size||index < 0) {
		printMessage(ERROR_INVALID_INDEX);
		return;
	}
	else if(taskclass.returntype(index, toDoList) == 1){
		size_t pos = description.find("-name");
		PartTochange = description.substr(pos+6);
		taskclass.edittext(index, PartTochange, toDoList);
	}
	else if(taskclass.returntype(index, toDoList) == 2){
		size_t foundname = description.find("-name");
		size_t founddue = description.find("-due");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		   taskclass.edittext(index, PartTochange, toDoList);
		}
		else if(founddue!=std::string::npos){
			PartTochange = description.substr(founddue+5);
			istringstream in(PartTochange);
			in>>e_time;;
			in>>temp;
			in>>e_date;
			in>>c;
		    in>>e_month;
			in>>c;
		    in>>e_year;

			taskclass.edite_time(index, e_time, toDoList);
			taskclass.edite_date(index, e_date, toDoList);
			taskclass.edite_month(index, e_month, toDoList);
			taskclass.edite_year(index, e_year, toDoList);
		}
	}
	else if(taskclass.returntype(index, toDoList) == 3){
		size_t foundname = description.find("-name");
		size_t foundstart = description.find("-start");
		size_t foundend = description.find("-end");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		   taskclass.edittext(index, PartTochange, toDoList);
		}
		else if(foundstart!=std::string::npos){
			PartTochange = description.substr(foundstart+7);
			istringstream in(PartTochange);
			in>>s_time;
			in>>temp;
			in>>s_date;
			in>>c;
		    in>>s_month;
			in>>c;
		    in>>s_year;

			taskclass.edits_time(index, e_time, toDoList);
			taskclass.edits_date(index, e_date, toDoList);
			taskclass.edits_month(index, e_month, toDoList);
			taskclass.edits_year(index, e_year, toDoList);
		}
		else if(foundend!=std::string::npos){
			PartTochange = description.substr(foundend+5);
			istringstream in(PartTochange);
			in>>e_time;
			in>>temp;
			in>>e_date;
			in>>c;
		    in>>e_month;
			in>>c;
		    in>>e_year;

			taskclass.edite_time(index, e_time, toDoList);
			taskclass.edite_date(index, e_date, toDoList);
			taskclass.edite_month(index, e_month, toDoList);
			taskclass.edite_year(index, e_year, toDoList);
		}
	}
}

void logic::markcompleted(int index, const string filename, vector<task> &toDoList){
	task temp;
	int size = toDoList.size();
	index = index - 1;

	if(size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else if(index>=size||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else {
		temp = toDoList[index];
		temp.completed(index, toDoList);
		toDoList[index] = temp;
		cout << "task marked completed";
	}
}

void logic::sorttext(vector<task> &toDoList){
	int size = toDoList.size();
	task next;
	
	for(int i=0; i<size-1; ++i){
		for(int j=1; j<size-i; ++j){
			if(next.returntext(j-1 , toDoList).compare(next.returntext(j, toDoList))>0){
				task temp = toDoList[j-1];
				toDoList[j-1] = toDoList[j];
				toDoList[j] = temp;
			}
		}
	}
}


void logic::sortdates(vector<task> &toDoList){
	unsigned int i, j;
	task temp;

	for(i = 0; i < toDoList.size(); ++i) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if(temp.returnendyear(j-1, toDoList) > temp.returnendyear(j, toDoList)) {
				vector<task> tempVec;
				tempVec.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec[0];
				tempVec.pop_back();
 			}
			else{}
		}
	
	}//sort year

	/*for(i = 0; i < toDoList.size()-1; ++i) {
		if(temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList)){
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((temp.returnendmonth(j-1, toDoList) > temp.returnendmonth(j, toDoList))
				&&(temp.returnendyear(j-1, toDoList) == temp.returnendyear(j, toDoList))) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
		else{}
	}//sort month

	/*for(i = 0; i < toDoList.size()-1; ++i) {
		if((temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))
			&&(temp.returnendmonth(i, toDoList) == temp.returnendmonth(i+1, toDoList))) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((temp.returnenddate(j-1,toDoList) > temp.returnenddate(j,toDoList))
				&&(temp.returnendyear(j-1, toDoList) == temp.returnendyear(j, toDoList))
				&&(temp.returnendmonth(j-1, toDoList) == temp.returnendmonth(j, toDoList))) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
	}//sort date*/

};

void logic::sorttime(vector<task> &toDoList){
	task temp;
	/*unsigned int i , j;
	for(i = 0; i < toDoList.size()-1; ++i) {
		if((temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))
			&&(temp.returnendmonth(i, toDoList) == temp.returnendmonth(i+1, toDoList))
			&&(temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((temp.returnendtime(j-1,toDoList) > temp.returnendtime(j,toDoList))
				&&(temp.returnendyear(j-1, toDoList) == temp.returnendyear(j, toDoList))
				&&(temp.returnendmonth(j-1, toDoList) == temp.returnendmonth(j, toDoList))
				&&(temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
	}*/
}

void logic::printMessage(const string message) {
	cout << endl << message << endl;
}

void logic::printMessage(const string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}



