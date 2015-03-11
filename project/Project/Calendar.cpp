#include "Calendar.h"
#include <sstream>
#include <fstream>

Calendar::Calendar(void) {
	_size=0;
}

Calendar::~Calendar(void) {
	_items.erase(_items.begin(),_items.end());
	_size=0;
}

void Calendar::readItem(const Data input) {
	_items.push_back(input);
	_size++;
}

void Calendar::addItem(const string description, const string fileName) {
	   Data datainput;
	   string task;
	   int date, month, year;
	   double t_start, t_end;

	   istringstream in(description);
		in>>task;
		in>>t_start;
		in>>t_end;
		in>>date;
		in>>month;
		in>>year;
		
		datainput.task=task;
		datainput.date=date;
		datainput.month=month;
		datainput.year=year;
		datainput.t_start=t_start;
		datainput.t_end=t_end;

	_items.push_back(datainput);
	_size++;
	printMessage(MESSAGE_ITEM_ADDED_SUCCESSFULLY, fileName, datainput);
}



void Calendar::displayAll(const string fileName) {
	ostringstream oss;
	
	if(_size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else {
		for(int i=0;i<_size;i++)
			oss << endl << i+1 << ". " << _items[i].task << " from " <<_items[i].t_start<<" to "<<_items[i].t_end<<" on "<<_items[i].date<<"/"
			<< _items[i].month << "/" << _items[i].year << endl;
	}

	cout << oss.str();
}

void Calendar::clearAll(const string fileName) {
	_items.erase(_items.begin(),_items.end());
	_size=0;
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY,fileName);
}

void Calendar::saveToSaveFile(const string fileName) {
	fstream textFile;
	
	textFile.open(fileName.c_str(), fstream::out);
	textFile << toString();
	textFile.close();
}

void Calendar::deleteItem(const int index, const string fileName) {
	if(_size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else if(index>=_size||index<0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else {
		printMessage(MESSAGE_ITEM_DELETED_SUCCESSFULLY, fileName, *(_items.begin()+index));
		_items.erase(_items.begin()+index);
		_size--;
	}
}

void Calendar::editTask(const int index, const string fileName, const string description) {
	string TextAfterIndex;
	TextAfterIndex = description.substr(1);   //1   -n txt

	unsigned int spacePosition = 0;
	spacePosition = TextAfterIndex.find_first_not_of(" ");
	
	string VariableToChange;
	VariableToChange = TextAfterIndex.substr(spacePosition, spacePosition+1);

	string PartTochange;
	PartTochange = TextAfterIndex.substr(spacePosition+3);

	if(_size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else if(index > _size||index <= 0) {
		printMessage(ERROR_INVALID_INDEX);
		
	}
	else if(VariableToChange == "-n") {
		_items[index-1].task = PartTochange;
	} else if(VariableToChange == "-s") {
		_items[index-1].t_start = convertStringToInteger( PartTochange);
	} else if(VariableToChange == "-e") {
		_items[index-1].t_end = convertStringToInteger( PartTochange);
	}

}

int Calendar::convertStringToInteger(const string description) {
	unsigned int t_start = 0, t_end=description.size();
	int output=0;

	while(t_start!=t_end) {
		output*=10;
		output+=description[t_start]-'0';
		t_start++;
	}
	return output;
}


string Calendar::toString() {
	ostringstream oss;

	if(_size>0) {

		for(int i=0;i<_size;i++)
			oss << endl << i+1 << ". " <<_items[i].task <<" "<< _items[i].t_start<<" "<<_items[i].t_end<<" "<<_items[i].date<<"/"<<" "
			<< _items[i].month << " /" << _items[i].year << endl;
	}
	return oss.str();
}

void Calendar::printMessage(const string message) {
	cout << endl << message << endl;
}

void Calendar::printMessage(const string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}

void Calendar::printMessage(const string message, const string fileName, const Data input) {
	cout << endl << message << " " << fileName << ": \"" << input.task<<" from "<<input.t_start<<" to "<<input.t_end<<" at " <<input.date << "/"<<input.month<<"/"<<input.year<< endl;
}

void Calendar::getsize(){
	cout<<_size;
}