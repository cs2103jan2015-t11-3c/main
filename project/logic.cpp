#include "logic.h"
#include "parser.h"
#include "Task.h"
#include "storage.h"
#include <sstream>
#include <fstream>



void logic::executeCommand(string command, string description, vector<task> &toDoList) {
	string text;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
    logic function;
	task datainput;
	storage store;

	parser::trimString(description);

	if(!parser::isValidCommand(command, description))
		return;
	else if(command=="add") {
		if(parser::checktype(description) == 1){
			parser::splitinputtypeone(description, text);
			datainput.addItemtypeone(text);
			toDoList.push_back(datainput);
		}
		else if(parser::checktype(description) == 2){
			parser::splitinputtypetwo(description, text, e_date, e_month, e_year, e_time);
			datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		else if(parser::checktype(description) == 3){
			parser::splitinputtypethree(description, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="delete") {
		function.deleteItem(parser::convertStringToIntegerIndex(description), fileName, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command=="display") {
		cout << function.displayAll(fileName, toDoList);
		return;
	}
	else if(command=="clear") {
		function.clearAll(fileName, toDoList);
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	/*else if(command == "edit") {
		istringstream in(description);
		int index;
		in>>index;
		function.editTask(index,fileName,description, toDoList);
		storage::saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}*/
	else if(command=="exit") {
		store.saveToSaveFile(fileName, function.displayAll(fileName, toDoList));
		return;
	}
	else if(command == "done") {
		function.markcompleted(parser::convertStringToIntegerIndex(description), fileName, toDoList);
		return;
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
	if(toDoList.size()==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	/*else if(index>=toDoList.size()||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}*/
	else {
		toDoList.erase(toDoList.begin()+index);
		cout << "deleted";
	}
}

void logic::clearAll(const string fileName, vector<task> &toDoList) {
	toDoList.clear();
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY,fileName);
}

void logic::editTask(int &index, string fileName, string description, vector<task> &toDoList) {
	string TextAfterIndex, VariableToChange, PartTochange, temp;
	task taskclass;

	index = index - 1;
	if(toDoList.size() == 0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
		return;
	}
	else if(index > toDoList.size()||index < 0) {
		printMessage(ERROR_INVALID_INDEX);
		return;
	}
	else if(taskclass.returntype(index, toDoList) == 1){
		size_t pos = description.find("-name");
		PartTochange = description.substr(pos+6);
		_items[index].task = PartTochange;
	}
	else if(taskclass.returntype(index, toDoList) == 2){
		size_t foundname = description.find("-name");
		size_t founddue = description.find("-due");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		   _items[index].task = PartTochange;
		}
		else if(founddue!=std::string::npos){
			PartTochange = description.substr(founddue+5);
			istringstream in(PartTochange);
			in>>_items[index].e_time;
			in >> temp;
			in>>_items[index].e_date;
		    in>>_items[index].e_month;
		    in>>_items[index].e_year;
		}
	}
	else if(taskclass.returntype(index, toDoList) == 3){
		size_t foundname = description.find("-name");
		size_t foundstart = description.find("-start");
		size_t foundend = description.find("-end");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		   _items[index].task = PartTochange;
		}
		else if(foundstart!=std::string::npos){
			PartTochange = description.substr(foundstart+7);
			istringstream in(PartTochange);
			in>>_items[index].s_time;
			in >> temp;
			in>>_items[index].s_date;
		    in>>_items[index].s_month;
			in>>_items[index].s_year;
		}
		else if(foundend!=std::string::npos){
			PartTochange = description.substr(foundend+5);
			istringstream in(PartTochange);
			in>>_items[index].e_time;
			in >> temp;
			in>>_items[index].e_date;
		    in>>_items[index].e_month;
			in>>_items[index].e_year;
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

void logic::readToDoListFromTextFile(string fileName, vector<task> &toDoList) {
	fstream textFile;
	string input, temp;
	textFile.open(fileName.c_str());
	getline(textFile, temp);

	//Remove the index of each line, eg: remove "1)" from "1) Some List Entry"
	//Adds the rest of the line to the to-do list after removing leading and following whitespaces
	while(getline(textFile,input)) {
		size_t pos = input.find('.');
		input = input.substr(pos+1);

		parser::trimString(input);
		string text;
		int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
		task datainput;

		if(parser::checktype(input) == 1){
			parser::splitinputtypeone(input, text);
			datainput.addItemtypeone(text);
			toDoList.push_back(datainput);
		}
		else if(parser::checktype(input) == 2){
			parser::splitinputtypetwo(input, text, e_date, e_month, e_year, e_time);
			datainput.addItemtypetwo(text, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}
		else if(parser::checktype(input) == 3){
			parser::splitinputtypethree(input, text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			datainput.addItemtypethree(text, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList.push_back(datainput);
		}

	}
	textFile.close();
}


void logic::printMessage(const string message) {
	cout << endl << message << endl;
}

void logic::printMessage(const string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}

