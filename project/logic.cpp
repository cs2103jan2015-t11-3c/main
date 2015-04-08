#include "logic.h"
#include <iostream>

string logic::displayAll(vector<task> &tempVec) {
	vector<task> temporary, temp;
	vector<vector<task>> temps;
	ostringstream oss;
	int i = 0;
	task temp_t;
	if(tempVec.size()==0) {
		printMessage(ERROR_LIST_IS_EMPTY);
	}
	else {
		for(unsigned j = 0; j < tempVec.size(); j++){
			if(tempVec[j].returntype() == "float"){
				temp.push_back(tempVec[j]);
			}
			else
				temporary.push_back(tempVec[j]);
		}
		sorttext(temp);
		oss <<"Float Task: " << endl;
		for(unsigned j = 0; j < temp.size(); j++){
			oss << temp[j].displayFloat(i) << endl;
			i++;
		}

		tempVec = temporary;
		temporary.clear();
		if(tempVec.size() != 0){
			sortdates(tempVec);
			temporary.push_back(tempVec[0]);
			for(int j = 0; j < tempVec.size() - 1 ; j++){
				if((tempVec[j].returnenddate() == tempVec[j+1].returnenddate()) && (tempVec[j].returnendmonth() == tempVec[j+1].returnendmonth()) && 
					(tempVec[j].returnendyear() == tempVec[j].returnendyear())){
						temporary.push_back(tempVec[j+1]);
				}
				else{
					sortEndTime(temporary);
					for( unsigned k = 0; k<temporary.size(); k++)
						temp.push_back(temporary[k]);
					temporary.clear();
					temporary.push_back(tempVec[j+1]);
				}
			}
			sortEndTime(temporary);
			for( unsigned k = 0; k<temporary.size(); k++)
				temp.push_back(temporary[k]);

			oss << endl << "Date: " << temp[i].returnenddate() << "/" << temp[i].returnendmonth() << "/" << temp[i].returnendyear() << endl;
			if(temp[i].returntype() == "deadline")
				oss << temp[i].displayDefaultTasks(i) << endl;
			else if(temp[i].returntype() == "timed")
				oss <<  temp[i].displayDefaultTasksWithTwoTimes(i) << endl;

			while(i != temp.size() - 1){
				if((temp[i].returnenddate() != temp[i+1].returnenddate())||(temp[i].returnendmonth() != temp[i+1].returnendmonth()) || 
					(temp[i].returnendyear() != temp[i+1].returnendyear()))
					oss << endl << "Date: " << temp[i+1].returnenddate() << "/" << temp[i+1].returnendmonth() << "/" << temp[i+1].returnendyear() << endl;
				if(temp[i+1].returntype() == "deadline")
					oss << temp[i+1].displayDefaultTasks(i+1) << endl;
				else if(temp[i+1].returntype() == "timed")
					oss <<  temp[i+1].displayDefaultTasksWithTwoTimes(i+1) << endl;
				i++;
			}
		}
	}
	tempVec = temp;
	return oss.str();
}

void logic::deleteItem(const int index, vector<task> &toDoList) {
		cout << toDoList[index].returntext() ;
		if (system("CLS")) system("clear");
		printMessage(MESSAGE_ITEM_DELETED_SUCCESSFULLY);
		toDoList.erase(toDoList.begin()+index);
}

void logic::clearAll(vector<task> &toDoList) {
	toDoList.clear();
	if (system("CLS")) system("clear");
	printMessage(MESSAGE_ITEMS_CLEARED_SUCCESSFULLY);
}

void logic::editTask(int index, string description, vector<task> &toDoList) {
	string TextAfterIndex, VariableToChange, PartTochange, temp, tempdescription;
	int s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time;
	task taskclass;
	char c;

	if(toDoList[index].returntype() == "float") {
		size_t pos = description.find("-name");
		PartTochange = description.substr(pos+6);
		toDoList[index].edittext(PartTochange);
		if (system("CLS")) system("clear");
		printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
	} else if(toDoList[index].returntype() == "deadline"){
		size_t foundname = description.find("-name");
		size_t founddue = description.find("-due");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		toDoList[index].edittext(PartTochange);
		} else if(founddue!=std::string::npos){
			PartTochange = description.substr(founddue+5);
			istringstream in(PartTochange);
			in>>e_time;;
			in>>temp;
			in>>e_date;
			in>>c;
		    in>>e_month;
			in>>c;
		    in>>e_year;

			toDoList[index].edite_time(e_time);
			toDoList[index].edite_date(e_date);
			toDoList[index].edite_month(e_month);
			toDoList[index].edite_year(e_year);
		}
		printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
	}
	else if(toDoList[index].returntype() == "timed"){
		size_t foundname = description.find("-name");
		size_t foundstart = description.find("-start");
		size_t foundend = description.find("-end");
		if(foundname!=std::string::npos){
			PartTochange = description.substr(foundname+6);
		    toDoList[index].edittext(PartTochange);
		}
		else{ 
			if(foundstart!=std::string::npos){
				PartTochange = description.substr(foundstart+7);
				istringstream in(PartTochange);
				in>>s_time;
				in>>temp;
				in>>s_date;
				in>>c;
				in>>s_month;
				in>>c;
				in>>s_year;

				toDoList[index].edits_time(s_time);
				toDoList[index].edits_date(s_date);
				toDoList[index].edits_month(s_month);
				toDoList[index].edits_year(s_year);
			}
			if(foundend!=std::string::npos){
				PartTochange = description.substr(foundend+5);
				istringstream in(PartTochange);
				in>>e_time;
				in>>temp;
				in>>e_date;
				in>>c;
				in>>e_month;
				in>>c;
				in>>e_year;

				toDoList[index].edite_time(e_time);
				toDoList[index].edite_date(e_date);
				toDoList[index].edite_month(e_month);
				toDoList[index].edite_year(e_year);
			}
		}
		if (system("CLS")) system("clear");
		printMessage(MESSAGE_ITEM_EDITED_SUCCESSFULLY);
	}
}

void logic::markcompleted(int index, vector<task> &toDoList){
	task temp;
	int size = toDoList.size();

	toDoList[index].editDone(true);
	if (system("CLS")) system("clear");
	printMessage(toDoList[index].returntext(), "completed");
}

void logic::sorttext(vector<task> &toDoList){
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


void logic::sortdates(vector<task> &toDoList){
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

void logic::sorttime(vector<task> &toDoList){
	task temp;
	unsigned int i , j;

	for(i = 0; i<toDoList.size(); ++i)
		toDoList[i].edittemp((toDoList[i].returnendyear()*100000000)+(toDoList[i].returnendmonth()*1000000)+
		(toDoList[i].returnenddate()*10000)+(toDoList[i].returnendtime()));

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



void logic::searchTask(vector<task> &toDoList, vector<task> &tempVec, string fileName, string description) {
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
	if( tempVec.size() == 0) {
		printMessage(MESSAGE_SEARCH_FAILED);
	} else {
	cout << displayAll(tempVec);
	}
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



void logic::display(vector<task> &toDoList, vector<task> &tempVec, string fileName, string description){
	int size, day, month, year, count = 0;
	size = toDoList.size();

	if(description == "today"){
		count++;
		for(int i=0; i<size; i++){
			day = toDoList[i].returnenddate();
			month = toDoList[i].returnendmonth();
			year = toDoList[i].returnendyear();
			if(day == getSystemDay() && (month == getSystemMonth())&& (year == getSystemYear())){
				pushback(toDoList, tempVec, i);
			}
		}
	}
	else if(description == "tomorrow" || description == "tmr" || description == "tomor"){
		count++;
		for(int i=0; i<size; i++){
			day = toDoList[i].returnenddate();
			month = toDoList[i].returnendmonth();
			year = toDoList[i].returnendyear();
			if((day == (getSystemDay())+1) && (month == getSystemMonth())&& (year == getSystemYear())){
				pushback(toDoList, tempVec, i);
			}
		}
	}
	else if(description == "not done"){
		count++;
		for(int i=0; i<size; i++){
			bool status = toDoList[i].returnstatus();
			if(status == false){
				pushback(toDoList, tempVec, i);
			}
		}
	}
	else if(description == "done"){
		count++;
		for(int i=0; i<size; i++){
			bool status = toDoList[i].returnstatus();
			if(status == true){
				pushback(toDoList, tempVec, i);
			}
		}
	}
	else if(description == "float"){
		count++;
		for(int i=0; i<size; i++){
			string type = toDoList[i].returntype();
			if(type == "float"){
				pushback(toDoList, tempVec, i);
			}
		}
	}
	else if(description == "deadline"){
		count++;
		for(int i=0; i<size; i++){
			string type = toDoList[i].returntype();
			if(type =="deadline"){
				pushback(toDoList, tempVec, i);
			}
		}
	}
	else if(description == "timed"){
		count++;
		for(int i=0; i<size; i++){
			string type = toDoList[i].returntype();
			if(type =="timed"){
				pushback(toDoList, tempVec, i);
			}
		}
	} 
	else if(description == "all"){
		count++;
		for(int i=0; i<size; i++)
			pushback(toDoList, tempVec, i);
	}
	if(count == 0) {
		printMessage(MESSAGE_INVALID_DISPLAY_COMMAND);
	} else {
	cout << displayAll(tempVec);
	}
}


int logic::getSystemDay() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int day = timePtr->tm_mday;
	return day;
}

int logic::getSystemMonth() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int month = timePtr->tm_mon + 1;
	return month;
}

int logic::getSystemYear() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int year = timePtr->tm_year+1900;
	return year;
}

void logic::pushback(vector<task>& toDoList, vector<task>& tempVec, int index){
	task task_;
	task_ = toDoList[index];
	task_.inserttempnum(index);
	tempVec.push_back(task_);
}

//check whether input date is valid function starts here
bool logic::isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

bool logic::isValidDate(unsigned short day,unsigned short month,unsigned short year){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (!year || !month || !day || month>12 || year > 2030)
		return 0;
	if (isleapyear(year) && month==2)
		monthlen[1]++;
	if (day>monthlen[month-1])
		return 0;
	return 1;
}

bool logic::isValidTime(int time) {
	if((time>=0)&&(time<=2400)) {
		return 1;
	} else {
		return 0;
	}
}

bool logic::checkIsDateOverdue(int day, int month, int year,int timing) {
	bool result = true;
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int systemDay, systemMonth, systemYear, systemHr, systemMin, systemTiming;
	systemDay = timePtr->tm_mday;
	systemMonth = timePtr->tm_mon + 1;
	systemYear = timePtr->tm_year+1900;
	systemHr = timePtr->tm_hour;
	systemMin = timePtr->tm_min;
	systemTiming = systemHr*100 + systemMin;

	if(year < systemYear) {
		return false;
	} else if(year == systemYear && month < systemMonth) {
		return  false;
	} else if(year == systemYear && month == systemMonth && day < systemDay) {
		return false;
	} else if(year == systemYear && month == systemMonth && day == systemDay && timing < systemTiming) {
		return false;
	}
	return result;
}
//check whether input date is valid ends here


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