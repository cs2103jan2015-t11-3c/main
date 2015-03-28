#include "logic.h"
#include <sstream>
#include <fstream>
#include <iostream>


void logic::readToDoListFromTextFile(string fileName, vector<task> &toDoList) {
	fstream textFile;
	string input;
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


void logic::executeCommand(string command, string description, vector<task> &toDoList, vector<task> &floatVec, 
						   vector<task> &deadlineVec, vector<task>&timedVec, vector<undo> &undomemory, undo &currentundomemory) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
    logic function;
	task datainput;
	storage store;
	parser parse;
	undo undofunction;

	parse.trimString(description);

	if(!parse.isValidCommand(command, description))
		return;
	else if(command=="add") {
		if(parse.checktype(description) == 1){  //floating task: add swimming 
			parse.splitinputtypeone(description, text);
			datainput.addItemtypeone(text);
			toDoList.push_back(datainput); //push back the floating task "swimming" into the vector toDoList
		}
		else if(parse.checktype(description) == 2){
			parse.splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
			datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		else if(parse.checktype(description) == 3){
			parse.splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="delete") {

		function.deleteItem(checkfororiginalindex(description, floatVec, deadlineVec, timedVec), fileName, toDoList);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="display") {
		cout << function.displayAll(fileName, toDoList);
		return;
	}
	else if(command=="clear") {
		function.clearAll(fileName, toDoList);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command == "edit") {
		function.editTask(checkfororiginalindex(description, floatVec, deadlineVec, timedVec),fileName,description, toDoList);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="exit") {
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command == "done") {
		function.markcompleted(checkfororiginalindex(description, floatVec, deadlineVec, timedVec), fileName, toDoList);
		undomemory.push_back(undofunction.converttoundoclass(undomemory, toDoList));
		return;
	}
	else if(command == "undo"){
		currentundomemory = undomemory[undomemory.size()-2];
		toDoList = currentundomemory.returnmemory();
		undomemory.pop_back();
	}
}

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

	for(int i=0; i<size; ++i){
		for(int j=1; j<size-i; ++j){
			if(next.returntext(j - 1, toDoList).compare(next.returntext(j, toDoList))>0){
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
		for(j = 1; j < toDoList.size() - i; ++j) {
			if(temp.returnendyear(j-1, toDoList) > temp.returnendyear(j, toDoList)) {
				vector<task> tempVec;
				tempVec.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec[0];
				tempVec.pop_back();
 			}
		}
	
	}//sort year

	for(i = 0; i < toDoList.size()-1; ++i) {
		if(temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList)){
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((temp.returnendmonth(j-1, toDoList) > temp.returnendmonth(j, toDoList))&&(temp.returnendyear(j-i, toDoList) == temp.returnendyear(j, toDoList))) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
	}
	}//sort month

	for(i = 0; i < toDoList.size()-1; ++i) {
		if((temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))&&(temp.returnendmonth(i, toDoList) == temp.returnendmonth(i+1, toDoList))) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((temp.returnenddate(j-1,toDoList) > temp.returnenddate(j,toDoList))&&(temp.returnendyear(j-1, toDoList) == temp.returnendyear(j, toDoList))&&(temp.returnendmonth(j-1, toDoList) == temp.returnendmonth(j, toDoList))) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
	}//sort date

};

void logic::sorttime(vector<task> &toDoList){
	task temp;
	unsigned int i , j;
	for(i = 0; i < toDoList.size()-1; ++i) {
		if((temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))&&(temp.returnendmonth(i, toDoList) == temp.returnendmonth(i+1, toDoList))
			&&(temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if((temp.returnendtime(j-1,toDoList) > temp.returnendtime(j,toDoList))&&(temp.returnendyear(j-1, toDoList) == temp.returnendyear(j, toDoList))&&(temp.returnendmonth(j-1, toDoList) == temp.returnendmonth(j, toDoList))
				&&(temp.returnendyear(i, toDoList) == temp.returnendyear(i+1, toDoList))) {
				vector<task> tempVec1;
				tempVec1.push_back(toDoList[j-1]);
				toDoList[j-1] = toDoList[j];
				toDoList[j] = tempVec1[0];
				tempVec1.pop_back();
 			}
		}
		}
	}
}

void logic::printMessage(const string message) {
	cout << endl << message << endl;
}

void logic::printMessage(const string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}

