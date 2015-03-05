#include "Calendar.h"
#include <sstream>
#include <fstream>

Timetable::Timetable(void) {
	_size=0;
}

Timetable::~Timetable(void) {
	_items.erase(_items.begin(),_items.end());
	_size=0;
}

void Timetable::readItem(const string input) {
	_items.push_back(input);
	_size++;
}

void Timetable::addItem(const string input, const string fileName) {
	_items.push_back(input);
	_size++;
	printMessage(MESSAGE_ITEM_ADDED_SUCCESSFULLY, fileName, input);
}

void Timetable::deleteItem(const int index, const string fileName) {
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

void Timetable::displayAll(const string fileName) {
	ostringstream oss;
	
	if(_size==0) {
		printMessage(fileName, ERROR_LIST_IS_EMPTY);
	}
	else {
		for(int i=0;i<_size;i++)
			oss << endl << i+1 << ". " << _items[i] << endl;
	}

	cout << oss.str();
}

void Timetable::clearAll(const string fileName) {
	_items.erase(_items.begin(),_items.end());
	_size=0;
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY,fileName);
}

void Timetable::saveToSaveFile(const string fileName) {
	fstream textFile;
	
	textFile.open(fileName.c_str(), fstream::out);
	textFile << toString();
	textFile.close();
}

string Timetable::toString() {
	ostringstream oss;

	if(_size>0) {
		oss << "1. " << _items[0] << endl;
		for(int i=1;i<_size;i++)
			oss << endl << i+1 << ". " << _items[i] << endl;
	}
	return oss.str();
}

void Timetable::printMessage(const string message) {
	cout << endl << message << endl;
}

void Timetable::printMessage(const string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}

void Timetable::printMessage(const string message, const string fileName, const string input) {
	cout << endl << message << " " << fileName << ": \"" << input << "\"" << endl;
}

//wangyalan