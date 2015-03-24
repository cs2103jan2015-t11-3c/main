#include "logic.h"
#include "parser.h"
#include "Task.h"
#include "storage.h"
#include <sstream>
#include <fstream>

logic::logic(void) {
	_size=0;
}

logic::~logic(void) {
	_items.erase(_items.begin(),_items.end());
	_size=0;
}

void logic::executeCommand(string command, string description, logic *toDoList, logic *undo) {
	string task;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	parser::trimString(description);

	if(!parser::isValidCommand(command, description))
		return;
	else if(command=="add") {
		undo = toDoList;
		if(parser::checktype(description) == 1){
			parser::splitinputtypeone(description, task);
			toDoList->addItemtypeone(task);
		}
		else if(parser::checktype(description) == 2){
			parser::splitinputtypetwo(description, task, e_date, e_month, e_year, e_time);
			toDoList->addItemtypetwo(task, e_date, e_month, e_year, e_time);
		}
		else if(parser::checktype(description) == 3){
			parser::splitinputtypethree(description, task, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
			toDoList->addItemtypethree(task, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
		}
		storage::saveToSaveFile(fileName, toDoList->displayAll(fileName));
		return;
	}
	else if(command=="delete") {
		undo = toDoList;
		toDoList->deleteItem(parser::convertStringToIntegerIndex(description), fileName);
		storage::saveToSaveFile(fileName, toDoList->displayAll(fileName));
		return;
	}
	else if(command=="display") {
		cout << toDoList->displayAll(fileName);
		return;
	}
	else if(command=="clear") {
		undo = toDoList;
		toDoList->clearAll(fileName);
		storage::saveToSaveFile(fileName, toDoList->displayAll(fileName));
		return;
	}
	else if(command == "edit") {
		undo = toDoList;
		istringstream in(description);
		int index;
		in>>index;
		toDoList->editTask(index,fileName,description);
		storage::saveToSaveFile(fileName, toDoList->displayAll(fileName));
		return;
	}
	else if(command=="exit") {
		storage::saveToSaveFile(fileName, toDoList->displayAll(fileName));
		return;
	}

	else if(command == "done") {
		undo = toDoList;
		toDoList->markcompleted(parser::convertStringToIntegerIndex(description), fileName);
		return;
	}
	else if(command == "undo") {
		toDoList  = undo;
		cout << "undo succesful";
		return;
	};

}
	

void logic::readItem(const Data input) {
	_items.push_back(input);
	_size++;
}

void logic::addItemtypeone(string task){
	Data datainput;

	datainput.task = task;
	datainput.s_date=0;
	datainput.s_month=0;
	datainput.s_year=0;
	datainput.s_time=0;
	datainput.e_date=0;
	datainput.e_month=0;
	datainput.e_year=0;
	datainput.e_time=0;
	datainput.type = 1;
	datainput.complete = false;

	_items.push_back(datainput);
	_size++;
}

void logic::addItemtypetwo(string task, int e_date, int e_month, int e_year, int e_time){ 
	Data datainput;

   datainput.task = task;
   datainput.s_date=0;
	datainput.s_month=0;
	datainput.s_year=0;
	datainput.s_time=0;
	datainput.e_date=e_date;
	datainput.e_month=e_month;
	datainput.e_year=e_year;
	datainput.e_time=e_time;
	datainput.type = 2;
	datainput.complete = false;

	_items.push_back(datainput);
	_size++;
}

void logic::addItemtypethree(string task, int s_date, int s_month, int s_year, int s_time, int e_date, int e_month, int e_year, int e_time){ 
	Data datainput;

   datainput.task = task;
   datainput.s_date=s_date;
	datainput.s_month=s_month;
	datainput.s_year=s_year;
	datainput.s_time=s_time;
	datainput.e_date=e_date;
	datainput.e_month=e_month;
	datainput.e_year=e_year;
	datainput.e_time=e_time;
	datainput.type = 3;
	datainput.complete = false;

	_items.push_back(datainput);
	_size++;
}

string logic::displaytypeone(int index){
	ostringstream oss;
	oss << endl<<  index+1 << "." << _items[index].task;
	return oss.str();
}

string logic::displaytypetwo(int index){
	ostringstream oss;
	oss << endl<<  index+1 << "." << _items[index].task <<  " by " << _items[index].e_time << " on " << _items[index].e_date<<" "
			<< _items[index].e_month << " " << _items[index].e_year;
	return oss.str();
}

string logic::displaytypethree(int index){
	ostringstream oss;
	 oss << endl << index+1 << "." << _items[index].task << " from " <<_items[index].s_time << " on "<<_items[index].s_date<<" "
			<< _items[index].s_month << " " << _items[index].s_year << " to " << _items[index].e_time << " on " << _items[index].e_date<<" "
			<< _items[index].e_month << " " << _items[index].e_year ;
	return oss.str();
}

string logic::displayAll(const string fileName) {
	ostringstream oss;
	if(_size==0)
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	else {
		for(int i=0;i<_size;i++){
			if(_items[i].type == 1)
				oss << displaytypeone(i);
			else if(_items[i].type == 2)
				oss << displaytypetwo(i);
			else if(_items[i].type == 3)
			    oss << displaytypethree(i);
		}
	}
	return oss.str();
}


void logic::deleteItem(const int index, const string fileName) {
	if(_size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else if(index>=_size||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else {
		_items.erase(_items.begin()+index);
		_size--;
		cout << "deleted";
	}
}

void logic::clearAll(const string fileName) {
	_items.erase(_items.begin(),_items.end());
	_size=0;
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY,fileName);
}

void logic::editTask(int &index, string fileName, string description) {
	string TextAfterIndex, VariableToChange, PartTochange, temp;

	index = index - 1;
	if(_size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
		return;
	}
	else if(index > _size||index < 0) {
		printMessage(ERROR_INVALID_INDEX);
		return;
	}
	else if( _items[index].type == 1){
		size_t pos = description.find("-name");
		PartTochange = description.substr(pos+6);
		_items[index].task = PartTochange;
	}
	else if(_items[index].type == 2){
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
	else if(_items[index].type == 3){
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

void logic::markcompleted(int index, const string filename){
	if(_size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else if(index>=_size||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else {
		_items[index].complete = true;
		cout << "task marked completed";
	}
}

void logic::readToDoListFromTextFile(string fileName, logic *toDoList) {
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
		string task;
		int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;

		if(parser::checktype(input) == 1){
			parser::splitinputtypeone(input, task);
		    toDoList->addItemtypeone(task);
		}
		else if(parser::checktype(input) == 2){
			parser::splitinputtypetwo(input, task, e_date, e_month, e_year, e_time);
		    toDoList->addItemtypetwo(task, e_date, e_month, e_year, e_time);
		}
		else if(parser::checktype(input) == 3){
			parser::splitinputtypethree(input, task, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
		    toDoList->addItemtypethree(task, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
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


void logic::getsize(){
	cout<<_size;
}