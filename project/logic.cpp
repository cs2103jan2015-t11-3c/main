#include "logic.h"
#include <iostream>

//display temporary vector
//precondition: temporary vector
//postcondition: list of tasks
//@author A0116006X
string logic::displayAll(vector<task> &tempVec) {
	vector<task> temp, other;
	vector<vector<task>> temps;
	ostringstream oss;
	int i = 0;
	task temp_t;
	if(tempVec.size()==0)
		printMessage(ERROR_LIST_IS_EMPTY);
	else {
		separateFloatAndOthers(tempVec, temp, other);

		sortText(temp);
		oss <<"Float Task: " << endl << printFloatTasks(temp, i);

		if(other.size() != 0){
			sortDates(other);
			sortOthers(other, temp);
			oss << printOthers(temp, i);
		}
	}
	tempVec = temp;
	return oss.str();
}

void logic::separateFloatAndOthers(vector<task> & tempVec, vector<task> & floattemp, vector<task> & other){
	for(unsigned j = 0; j < tempVec.size(); j++){
		if(tempVec[j].returntype() == "float"){
			floattemp.push_back(tempVec[j]);
		}
		else
			other.push_back(tempVec[j]);
	}
}

string logic::printFloatTasks(vector<task> & floattemp, int & i){
	ostringstream oss;
	for(unsigned j = 0; j < floattemp.size(); j++){
		oss << floattemp[j].displayFloat(i) << endl;
		i++;
	}
	return oss.str();
}


void logic::sortOthers(vector<task> & other, vector<task> & temp){
	vector<task> temporary;
	temporary.push_back(other[0]);
	for(int j = 0; j < other.size() - 1 ; j++){
		if((other[j].returnenddate() == other[j+1].returnenddate()) && (other[j].returnendmonth() == other[j+1].returnendmonth()) && 
			(other[j].returnendyear() == other[j].returnendyear())){
				temporary.push_back(other[j+1]);
		}
		else{
			sortEndTime(temporary);
			for( unsigned k = 0; k<temporary.size(); k++)
				temp.push_back(temporary[k]);
			temporary.clear();
			temporary.push_back(other[j+1]);
		}
	}
	sortEndTime(temporary);
	for( unsigned k = 0; k<temporary.size(); k++)
		temp.push_back(temporary[k]);
}

string logic::printOthers(vector<task> & temp, int & i){
	ostringstream oss;
	oss << endl << "Date: " << temp[i].returnenddate() << "/" << temp[i].returnendmonth() << "/" << temp[i].returnendyear() << endl;
	if(temp[i].returntype() == "deadline")
		oss << temp[i].displayDefaultTasks(i) << endl;
	else if(temp[i].returntype() == "timed"){
		if((temp[i].returnenddate() != temp[i].returnenddate())||(temp[i].returnendmonth() != temp[i].returnstartmonth()))
			oss << temp[i].displayDefaultTasksOver2days(i) << endl;
		else
			oss << temp[i].displayDefaultTasksWithTwoTimes(i) << endl;
	}

	while(i != temp.size() - 1){
		if((temp[i].returnenddate() != temp[i+1].returnenddate())||(temp[i].returnendmonth() != temp[i+1].returnendmonth()) || 
			(temp[i].returnendyear() != temp[i+1].returnendyear()))
			oss << endl << "Date: " << temp[i+1].returnenddate() << "/" << temp[i+1].returnendmonth() << "/" << temp[i+1].returnendyear() << endl;
		if(temp[i+1].returntype() == "deadline")
			oss << temp[i+1].displayDefaultTasks(i+1) << endl;
		else if(temp[i+1].returntype() == "timed"){
			if((temp[i+1].returnenddate() != temp[i+1].returnstartdate())||(temp[i+1].returnendmonth() != temp[i+1].returnstartmonth()))
				oss << temp[i+1].displayDefaultTasksOver2days(i+1) << endl;
			else
				oss <<  temp[i+1].displayDefaultTasksWithTwoTimes(i+1) << endl;
		}
		i++;
	}
	return oss.str();
}

//edit existing task, name, dates, times
//Precondition: index of task, string that include command and changes to be made, vector
//postcondition: none
bool logic::editTask(int index, string description, vector<task> &toDoList) {

	if(toDoList[index].returntype() == "float")
		return editFloatClass(toDoList, description, index);
	else if(toDoList[index].returntype() == "deadline")
		return editDeadlineClass(toDoList, description, index);
	else if(toDoList[index].returntype() == "timed")
		return editTimedClass(toDoList, description, index);
}

bool logic::editFloatClass(vector<task> & toDoList, string description, int index){
	string PartToChange;
	
	size_t pos = description.find("-name");
	PartToChange = description.substr(pos+6);
	toDoList[index].edittext(PartToChange);
	return true;
	
}

bool logic::editDeadlineClass(vector<task> & toDoList, string description, int index){
	string PartTochange, temp, month, year;
	parser parse;
	char c;
	int e_date, e_month, e_year, e_time;

	size_t foundname = description.find("-name");
	size_t founddue = description.find("-due");
	if(foundname!=std::string::npos){
		PartTochange = description.substr(foundname+6);
		toDoList[index].edittext(PartTochange);
		if (system("CLS")) system("clear");
		printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
	} else if(founddue!=std::string::npos){
		description = description.substr(founddue + 5);
		istringstream in(description);// 1800 on 31/06/2016
		in>>e_time;//1800

		if(parse.containShortForm(description))
			parse.getInfo(description, e_date, e_month, e_year);
		else{
			in>>temp;//on
			in>>e_date;//31
			in>>c;//"/"

			int s=description.find("/");
			int pos=description.find("/",s+1);

			month=description.substr(s+1,pos-s-1);
			parse.trimString(month);

			year=description.substr(pos+1);
			parse.trimString(year);
			e_month=parse.convertMonth(month);
			e_year=parse.convertStringToInteger(year);
		}
		if(printErrorMsgForEditDeadlineTask(e_date, e_month, e_year, e_time))
			return false;
		else {
			toDoList[index].edite_time(e_time);
			toDoList[index].edite_date(e_date);
			toDoList[index].edite_month(e_month);
			toDoList[index].edite_year(e_year);
			return true;
		}
	}else{
		printMessage(ERROR_INVALID_COMMAND);
		return false;
	}
}

bool logic::editTimedClass(vector<task> & toDoList, string description, int index){
	string PartTochange, temp, date, smonth, syear, emonth, eyear;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	char c;
	parser parse;

	size_t foundname = description.find("-name");
	size_t foundstart = description.find("-start");
	if(foundname!=std::string::npos){
		PartTochange = description.substr(foundname+6);
		toDoList[index].edittext(PartTochange);
	}
	else if(foundstart!=std::string::npos){
		description = description.substr(foundstart+6);
		istringstream inStart(description);
		inStart>>s_time;//1900

		size_t foundend = description.find("-end");
		temp = description.substr(0,foundend);
		if(parse.containShortForm(temp)){
			parse.getInfo(temp, s_date, s_month, s_year);
		}
		else{
			inStart>>temp;//on
			inStart>>s_date;//28
			inStart>>c;//"/"
			inStart>>date;
			int tend=date.find_first_of("/");
			smonth=date.substr(0,tend);
			parse.trimString(smonth);
			s_month=parse.convertMonth(smonth);

			int pos=date.find("to");
			syear=date.substr(tend+1,pos-tend);
			parse.trimString(syear);
			s_year=parse.convertStringToInteger(syear);
		}

		description = description.substr(foundend+5);
		istringstream inEnd(description);
		inEnd>>e_time;//2000
		if(parse.containShortForm(description)){		
			parse.getInfo(description, e_date, e_month, e_year);
		}
		else{	
			inEnd>>temp;//on
			inEnd>>e_date;//29
			inEnd>>c;//"/"
			inEnd>>date;
			int post=date.find("/");
			emonth=date.substr(0,post);
			parse.trimString(emonth);
			eyear=date.substr(post+1);
			parse.trimString(eyear);

			e_month=parse.convertMonth(emonth);
			e_year=parse.convertStringToInteger(eyear);
		}

		if(printErrorMsgForEditTimedTask(e_date,  e_month,  e_year, e_time,  s_date, s_month, s_year,  s_time))
			return false;
		else {
			toDoList[index].edits_time(s_time);
			toDoList[index].edits_date(s_date);
			toDoList[index].edits_month(s_month);
			toDoList[index].edits_year(s_year);
			toDoList[index].edite_time(e_time);
			toDoList[index].edite_date(e_date);
			toDoList[index].edite_month(e_month);
			toDoList[index].edite_year(e_year);
			return true;
		}
	}else{
		printMessage(ERROR_INVALID_COMMAND);
		return false;
	}
}

bool logic::printErrorMsgForEditDeadlineTask(int e_date, int e_month, int e_year, int e_time){
	logic function;
	parser parse;

	if(!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time) && !parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_DATE_OVERDUE);
		cout << "and";
		function.printMessage(MESSAGE_TIME_INVALID);
	} else if(!parse.isValidDate(e_date,e_month,e_year) && !parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_DATE_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_TIME_INVALID);
	} else if (!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
		function.printMessage(MESSAGE_DATE_OVERDUE);
	} else if(!parse.isValidDate(e_date,e_month,e_year)) {
		function.printMessage(MESSAGE_DATE_INVALID);
	} else if (!parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_TIME_INVALID);
	} else{
		return false;
	}
}

bool logic::printErrorMsgForEditTimedTask(int e_date, int e_month, int e_year, int e_time, int s_date,int s_month, int s_year, int s_time){
	parser parse;
	logic function;

	if(!parse.checkIsDateOverdue(s_date,s_month,s_year,s_time) && !parse.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
	} else if(!parse.isValidTime(s_time) && !parse.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_START_DATE_INVALID);
	} else if(!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time) && !parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if(!parse.isValidTime(e_time) && !parse.isValidDate(e_date,e_month,e_year)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_INVALID);
	} else if(!parse.isValidDate(e_date,e_month,e_year)&&!parse.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_BOTH_DATE_INVALID);
	} else if(!parse.isValidTime(e_time) && !parse.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
		cout << "and";
		function.printMessage(MESSAGE_END_TIME_INVALID);
	} else if(!parse.checkIsDateOverdue(s_date,s_month,s_year,s_time) && !parse.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
		cout << "and";
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if(!parse.isValidTime(s_time)) {
		function.printMessage(MESSAGE_START_TIME_INVALID);
	} else if(!parse.isValidTime(e_time)) {
		function.printMessage(MESSAGE_END_TIME_INVALID);
	} else if (!parse.checkIsDateOverdue(s_date,s_month,s_year,s_time)) {
		function.printMessage(MESSAGE_START_DATE_OVERDUE);
	} else if (!parse.checkIsDateOverdue(e_date,e_month,e_year,e_time)) {
		function.printMessage(MESSAGE_END_DATE_OVERDUE);
	} else if (!parse.isValidDate(s_date,s_month,s_year)) {
		function.printMessage(MESSAGE_START_DATE_INVALID);
	} else if(!parse.isValidDate(e_date,e_month,e_year)) {
		function.printMessage(MESSAGE_END_DATE_INVALID);
	} else{
		return false;
	}
}

//delete task from toDoList
//Precondition: take in index and vector
//postcondition: none
void logic::deleteItem(const int index, vector<task> &toDoList) {
	if (system("CLS")) system("clear");
	printMessage(MESSAGE_ITEM_DELETED_SUCCESSFULLY);
	toDoList.erase(toDoList.begin()+index);
}

//clear all the task from toDolist
//Precondition: take in vector
//postcondition: none
void logic::clearAll(vector<task> &toDoList) {
	toDoList.clear();
	if (system("CLS")) system("clear");
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY);
}

//mark task as completed
//Precondition: index of task, vector
//Postcondition: none
void logic::markCompleted(int index, vector<task> &toDoList){
	toDoList[index].editDone(true);
	if (system("CLS")) system("clear");
	printMessage(toDoList[index].returntext(), "completed");
}

//mark task as not completed
//Precondition: index of task, vector
//Postcondition: none
void logic::markNotCompleted(int index, vector<task> &toDoList){
	toDoList[index].editDone(false);
	if (system("CLS")) system("clear");
	printMessage(toDoList[index].returntext(), "not yet completed");
}

//sort vector alphabetically
//precondition: vector
//postcondition: none
void logic::sortText(vector<task> &toDoList){
	int size = toDoList.size();
	task temp;

	for(int i=0; i<size-1; ++i){
		for(int j=1; j<size-i; ++j){
			if(toDoList[j-1].returntext().compare(toDoList[j].returntext())>0){
				temp = toDoList[j-1];
				toDoList[j-1] = toDoList[j];
				toDoList[j] = temp;
			}
		}
	}
}

//sort vector by dates
//Precondition: vector
//Postcondition: none
void logic::sortDates(vector<task> &toDoList){
	unsigned int i, j;
	task temp;

	for(i = 0; i<toDoList.size(); ++i)
		toDoList[i].edittemp((toDoList[i].returnendyear()*10000)+(toDoList[i].returnendmonth()*100)+(toDoList[i].returnenddate()));

	for(i = 0; i < toDoList.size(); ++i) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if(toDoList[j-1].returntemp() > toDoList[j].returntemp()){
				temp = toDoList[j-1];
				toDoList[j-1] = toDoList[j];
				toDoList[j] = temp;
			}
		}
	}
}

//Sort vector by endtime
//Precondition: vector
//Postcondition: none
void logic::sortEndTime(vector<task> &toDoList){
	task temp;
	unsigned int i , j;

	for(i = 0; i < toDoList.size(); ++i) {
		for(j = 1; j < toDoList.size()-i; ++j) {
			if(toDoList[j-1].returnendtime() > toDoList[j].returnendtime()){
				temp = toDoList[j-1];
				toDoList[j-1] = toDoList[j];
				toDoList[j] = temp;
			}
		}
	}
}

//search for keyword or number within the vector
//Precondition: main vector, temporary vector, keyword
//Postcondition: none
void logic::searchTask(vector<task> &toDoList, vector<task> &tempVec, string description) {
	tempVec.clear();
	parser parse;

	if(!parse.isCheckSearchStringDigit(description)) {
		searchWord(toDoList,description,tempVec);
	} else {
		searchDigit(toDoList,description,tempVec);
	}

	if( tempVec.size() == 0) {
		printMessage(MESSAGE_SEARCH_FAILED);
	} else {
		cout << displayAll(tempVec);
	}
}

//search for tasks with keyword
//precondition: main vector, keyword, temporary vector
//postcondition: none
void logic::searchWord(vector<task> &toDoList, string description, vector<task> &tempVec) {
	for(int i = 0; i < toDoList.size(); ++i) {
		//searched word is not a digit-->can only be found in task name
		unsigned int t = -1;
		t = (toDoList[i].returntext()).find(description);
		if(t != -1) {
			pushback(toDoList, tempVec, i);
		}
	}
}

//search for tasks with name, dates, time with the particular digit
//precondition: main vector, keyword, temporary vector
//postcondition: none
void logic::searchDigit(vector<task> &toDoList, string description, vector<task> &tempVec) {
	parser parse;
	for(int i = 0; i < toDoList.size(); ++i) { // searched word is a pure digit-->can only be found in time/date/month/year
		unsigned int t = -1;
		t = (toDoList[i].returntext()).find(description);
		if(t != -1) {
			pushback(toDoList, tempVec, i);
		}
		int convertedInt = parse.convertNumStringToInt(description);
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

//to display tasks that are due today/tomorrow, not done, three different types of tasks, all
//precondition: main vector, temporary vector, vector size
//postcondition: none
void logic::displayToday(vector<task> &tempVec, vector<task> &toDoList,int size) {
	int day, month, year;
	parser parse;
	for(int i=0; i<size; i++) {
		day = toDoList[i].returnenddate();
		month = toDoList[i].returnendmonth();
		year = toDoList[i].returnendyear();
		if(day == parse.getSystemDay() && (month == parse.getSystemMonth())&& (year == parse.getSystemYear())){
			pushback(toDoList, tempVec, i);
		}
	}
}

void logic::displayTomorrow(vector<task> &tempVec, vector<task> &toDoList,int size) {
	int day, month, year;
	parser parse;
	for(int i=0; i<size; i++){
		day = toDoList[i].returnenddate();
		month = toDoList[i].returnendmonth();
		year = toDoList[i].returnendyear();
		if((day == (parse.getSystemDay())+1) && (month == parse.getSystemMonth())&& (year == parse.getSystemYear())){
			pushback(toDoList, tempVec, i);
		}
	}
}

void logic::displayNotDone(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
		bool status = toDoList[i].returnstatus();
		if(status == false){
			pushback(toDoList, tempVec, i);
		}
	}
}

void logic::displayDone(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
		bool status = toDoList[i].returnstatus();
		if(status == true){
			pushback(toDoList, tempVec, i);
		}
	}
}

void logic::displayFloat(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
		string type = toDoList[i].returntype();
		if(type == "float"){
			pushback(toDoList, tempVec, i);
		}
	}
}

void logic::displayDeadline(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
		string type = toDoList[i].returntype();
		if(type =="deadline"){
			pushback(toDoList, tempVec, i);
		}
	}
}

void logic::displayTimed(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++){
		string type = toDoList[i].returntype();
		if(type =="timed"){
			pushback(toDoList, tempVec, i);
		}
	}
}

void logic::displayEverything(int size,vector<task> &toDoList,vector<task> &tempVec) {
	for(int i=0; i<size; i++) {
		pushback(toDoList, tempVec, i);
	}
}

//function to work on the display, 
//precondition: main vector, temporary vector, filename, command
//postcondition: none
void logic::display(vector<task> &toDoList, vector<task> &tempVec, string fileName, string description){
	int size, day, month, year;
	int count = 0;
	size = toDoList.size();

	if(description == "today"){
		count++;
		displayToday(tempVec, toDoList, size);
	}
	else if(description == "tomorrow" || description == "tmr" || description == "tomor"){
		count++;
		displayTomorrow(tempVec, toDoList, size);
	}
	else if(description == "not done"){
		count++;
		displayNotDone(size,toDoList,tempVec);
	}
	else if(description == "done"){
		count++;
		displayDone(size,toDoList,tempVec);
	}
	else if(description == "float"){
		count++;
		displayFloat(size,toDoList,tempVec);
	}
	else if(description == "deadline"){
		count++;
		displayDeadline(size,toDoList,tempVec);
	}
	else if(description == "timed"){
		count++;
		displayTimed(size,toDoList,tempVec);
	} 
	else if(description == "all"){
		count++;
		displayEverything(size,toDoList,tempVec);
	}

	if(count == 0) {
		printMessage(MESSAGE_INVALID_DISPLAY_COMMAND);
	} else {
		cout << displayAll(tempVec);
	}
}

//pushback task to a temporary vector that includes it's index on the main vector
//precondition: main vector, temporary vector, index
//postcondition: none
void logic::pushback(vector<task>& toDoList, vector<task>& tempVec, int index){
	task task_;
	task_ = toDoList[index];
	task_.inserttempnum(index);
	tempVec.push_back(task_);
}

void logic::printMessage(const string message) {
	cout << endl << message << endl;
}

void logic::printMessage( string message1, const string message2) {
	cout << endl << message1 << " " << message2 << endl;
}

bool logic::checkIfStartTimeIsEarlierThanEndTime (int s_day,int s_month,int s_year,int s_time,int e_day,int e_month,int e_year,int e_time) {
	bool result = true;

	if(checkIsSameDate(e_day,s_day) && checkIsSameMonth(e_month,s_month) && checkIsSameYear(e_year,s_year)) {
		if(s_time >= e_time) {
			return result;
		} else {
			return !result;
		}
	}
}

bool logic::checkIsSameDate(int e_day,int s_day) {
	return (e_day == s_day);
}
bool logic::checkIsSameMonth(int e_month,int s_month) {
	return (e_month == s_month);
}
bool logic::checkIsSameYear(int e_year,int s_year) {
	return (e_year == s_year);
}
