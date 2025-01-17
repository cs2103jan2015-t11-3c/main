#include "parser.h"
#include <sstream>
#include "logic.h"


//@author: A0119322N

//Check if the command entered by the user is valid 
//precondition : user input a command
//postcondition : return true if command is valid; error message is shown to user if command entered is invalid
//and false is returned
bool parser::isValidCommand(const string command, const string description){
	logic function;
	try{
		if(command=="add"||command=="+"||command== "changeDirectory"||command== "changeFilename") {
			if(description.size()==0) {
				throw ERROR_MISSING_DESCRIPTION;
			}
			return true;
		}

		else if(command == "help" || command=="display"||command=="show"||command=="clear"||command=="clear all"||
			command=="exit"||command=="undo"||command=="search"||command=="default"||command== "changeDirectory"||command== "changeFilename")
			return true;

		else if (command=="delete"||command=="-"||command=="remove"||command=="done"){
			if(description.size()==0) {
				throw ERROR_MISSING_INDEX;		
			}  
			return true;
		}
		else if(command=="edit"||command=="modify"||command=="change"){
			if(description.size()==0) {
				throw ERROR_MISSING_INDEX;
			}    
			else if(!canFindPartoChange(description)){
				throw ERROR_MISSING_CHANGINGPART;			
			}  
  
			return true;
		}

		throw ERROR_INVALID_COMMAND;
	}

	catch(const string ERROR_MESSAGE){
		function.printMessage(ERROR_MESSAGE);
		return false;
	}
}


//Remove leading and following whitespaces of a string
void parser::trimString(string &description) {
	size_t lineStart=0, lineEnd=0;
	
	lineStart=description.find_first_not_of(DELIMITERS);
	lineEnd=description.find_last_not_of(DELIMITERS);
	
	if(lineStart==string::npos||lineEnd==string::npos)
		description="";
	else{
		description=description.substr(lineStart,lineEnd-lineStart+1);
	}
}

//Converts a number in string format to integer format
//Then converts the integer from base 1 to base 0, ie: 1,2,3,4,5... -> 0,1,2,3,4...
//String must not contain leading or following whitespaces, or function will fail
//precondition : pass in the description entered by user
//postcondition : converted index is returned
int parser::convertStringToIntegerIndex(const string description) {
	unsigned int t_start = 0, t_end=description.size();
	int output=0;

	while(t_start!=t_end) {
		output*=10;
		output+=description[t_start]-'0';
		t_start++;
	}
	
	return output-1;
}


int parser::convertStringToInteger(const string description) {
	unsigned int t_start = 0, t_end=description.size();
	int output=0;

	while(t_start!=t_end) {
		output*=10;
		output+=description[t_start]-'0';
		t_start++;
	}
	
	return output;
}

//check the type of the task input by the user
string parser::checktype(string description){
	size_t foundtypeDeadline = description.find("/by");
	size_t foundtypeTimed = description.find("/from");
	if(foundtypeDeadline!=std::string::npos){
		return "deadline";
	}
	else if(foundtypeTimed!=std::string::npos){
		return "timed";
	}
	else{
		return "float";
	}
	
}

//split the input task string into its ending date, month, year, timing and task name(text)
//precondition : task entered is a deadline task
//postcondition : string is splited into different portions using istringstream
void parser::splitinputDeadline(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time){
	string temp;
	char c;
	string date;
	string month;
	string year;


	size_t bypos = description.find("/by");
	text = description.substr(0 , bypos-1);  //"meeting"
	description = description.substr(bypos + 4);
	istringstream in(description);    // meeting by 1800 31 06 2016
	in>>e_time;         //1800

	if(containShortForm(description)){                        // to check whether the description contain words such as "today", "tomorrow","tmr"
	getInfo(description, e_date, e_month, e_year);
	}
	else{
		in>>temp;  //on
		in>>e_date;  //31
		in>>c;  //"/"
		int s=description.find("/");
		int pos=description.find("/",s+1);

		month=description.substr(s+1,pos-s-1);
    	trimString(month);
	
		year=description.substr(pos+1);
     	trimString(year);
		e_month=convertMonth(month);
		e_year=convertStringToInteger(year);

       }
}

//split the input task string into its starting date, month, year, timing
//and into ending date, month, year, timing and task name(text)
//precondition : task entered is a timed task
//postcondition : string is splited into different portions using istringstream
void parser::splitinputTimed(string description, string &text, int &s_date, int &s_month, int &s_year, int &s_time, int &e_date, int &e_month, int &e_year, int &e_time){
	string temp;
	char c;
	string date;
	string smonth,emonth;
	string syear,eyear;

	size_t bypos = description.find("/from");
	text = description.substr(0 , bypos-1);
	description = description.substr(bypos+6);
	istringstream in(description);
	in>>s_time;//1900

	int spos=description.find("/to ");
	if(containShortForm(description.substr(0,spos))){
		in>>temp;
		getInfo(description, s_date, s_month, s_year);
	}
	else{
		in>>temp;//on
		in>>s_date;//28
		in>>c;//"/"
		in>>date;
		int tend=date.find_first_of("/");
		smonth=date.substr(0,tend);
		trimString(smonth);
		s_month=convertMonth(smonth);

		int pos=date.find("to");
		syear=date.substr(tend+1,pos-tend);
		trimString(syear);
		s_year=convertStringToInteger(syear);
	}

	in>>temp;//to
	in>>e_time;//2000
	in>>temp;//on
	if(containShortForm(temp)){		
		getInfo(temp, e_date, e_month, e_year);
	}
	else{	   
		in>>e_date;//29
		in>>c;//"/"
		in>>date;
		int post=date.find("/");
		emonth=date.substr(0,post);
		trimString(emonth);
		eyear=date.substr(post+1);
		trimString(eyear);

		e_month=convertMonth(emonth);
		e_year=convertStringToInteger(eyear);
	}
}



//Convert alphabet month into corresponding integer. 
//i.e: Jan - Dec correspons to 1 - 12
//precondition : month input by user is in alphabetic form
//postcondition : converted integer month is returned
//@author: A0119322N -reused
int parser::convertAlphabetMonthToInteger (string month) {
	int monthInt=0;
	if (month == "january" || month == "jan"||month == "JAN") {
		monthInt = 1;
	}
	else if (month == "february" || month == "feb"||month == "FEB") {
		monthInt = 2;
	}
	else if (month == "march" || month == "mar"||month == "MAR") {
		monthInt = 3;
	}
	else if (month == "april" || month == "apr"||month == "APR") {
		monthInt = 4;
	}
	else if (month == "may" || month == "may"||month == "MAY") {
		monthInt = 5;
	}
	else if (month == "june" || month == "jun"||month == "JUN") {
		monthInt = 6;
	}
	else if (month == "july" || month == "jul"||month == "JUL") {
		monthInt = 7;
	}
	else if (month == "august" || month == "aug"||month == "AUG") {
		monthInt = 8;
	}
	else if (month == "september" || month == "sep"||month == "SEP") {
		monthInt = 9;
	}
	else if (month == "october" || month == "oct"||month == "OCT") {
		monthInt = 10;
	}
	else if (month == "november" || month == "nov"||month == "NOV") {
		monthInt = 11;
	}
	else if (month == "december" || month == "dec"||month == "DEC") {
		monthInt = 12;
	}
	else{
		throw ERROR_MESSAGE_INVALIDMONTH;
	}
	return monthInt;
}

//@author: A0119322N
//Determine if month is in numerical form or not
bool parser::isNumerical(string month){
    for(int i=0;i<month.length();i++)
    {
     char a=month[i];
     if(a<'0'||a>'9') {
      return false;
     }
    }
    return true;

}

//Convert alphabetic month into integer
//precondition : month entered by user is a alphabet
//postcondition : return the corresponding integer month
int parser::convertMonth(string month){
	if(isNumerical(month)){
			return convertStringToInteger(month);
		}
		else{
			return convertAlphabetMonthToInteger(month);
		}
}


//Determine if today/tomorrow/tmr exists in user input
bool parser::containShortForm(string description){
	int n=description.find("today");
	if(n!=-1)
		return true;
	int m=description.find("tomorrow");
	if(m!=-1)
		return true;
	int p=description.find("tmr");
	if(p!=-1)
		return true;

	return false;
}



//Determine if today/tomorrow/tmr exists in user input
//precondition : user input a new task 
//postcondition : return today if "today" is found,
//return tomorrow if "tomorrow" or "tmr" is found
string parser::shortForm(string description){
	int n=description.find("today");
	if(n!=-1)
		return "today";
	int m=description.find("tomorrow");
	if(m!=-1)
		return "tomorrow";
	int p=description.find("tmr");
	if(p!=-1)
		return "tomorrow";

}

//Get the corresponding numeric day, month and year if the date entered by user is "today" or "tomorrow"
//precondition : user input date is "today" or "tomorrow" instead of numerical date
//postcondition : numerical day, month, year corresponding to "today" and "tomorrow" is get
void parser::getInfo(string description, int &e_date, int &e_month, int &e_year){
		if(shortForm(description)=="today"){
		e_date=getSystemDay();		
		}
		if(shortForm(description)=="tomorrow"){
		e_date=getSystemDay()+1;
		}
		e_month=getSystemMonth();
		e_year=getSystemYear();
}


bool parser::canFindPartoChange(string description){
	if(description.find("-name")!=-1){
		int n=description.find("-name");
		description=description.substr(n+5);
		cout<<description;
	    if(description.size()==0){
			return false;
		}
		return true;
	}
	else if(description.find("-due")!=-1){
		int n=description.find("-due");
		description=description.substr(n+4);
	    if(description.size()==0){
			return false;
		}
		return true;
	}
		
	else if(description.find("-start")!=-1){
		int n=description.find("-start");
		description=description.substr(n+6);
	    if(description.size()==0){
			return false;
		}
		return true;
	}
	
	else if(description.find("-end")!=-1){
		int n=description.find("-end");
		description=description.substr(n+5);
	    if(description.size()==0){
			return false;
		}
		return true;
	}
	else{
		throw ERROR_MESSAGE_INVALIDEDITFORMAT;
	}
   return false;
}

//@author A0113745J

//Get the current local day on the system the program is running
//precondition : none
//postcondition : system day is returned
int parser::getSystemDay() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int day = timePtr->tm_mday;
	return day;
}

int parser::getSystemMonth() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int month = timePtr->tm_mon + 1;
	return month;
}

int parser::getSystemYear() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int year = timePtr->tm_year+1900;
	return year;
}

int parser::getSystemHour() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int hour = timePtr->tm_hour;
	return hour;
}

int parser::getSystemMinute() {
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int minute = timePtr->tm_min;
	return minute;
}

//Check whether there is any integer in the keyword
//Precondition: keyword
//Postcondition: return false if integer if found, else return true
bool parser::isCheckSearchStringDigit(string description) {
	unsigned int i;
	bool result = true;
	for(i = 0; i < description.size(); ++i) {
		if(!isdigit(description[i])) {
			result = false;
		}
	}
	return result;
}

int parser::convertNumStringToInt(string description) {
	int convertedNum;
	convertedNum = atoi(description.c_str());
    return convertedNum;
}

bool parser::isleapyear(unsigned short year){
	return (!(year%4) && (year%100) || !(year%400));
}

bool parser::isValidDate(unsigned short day,unsigned short month,unsigned short year){
	unsigned short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (!year || !month || !day || month>12 || year > 2030)
		return 0;
	if (isleapyear(year) && month==2)
		monthlen[1]++;
	if (day>monthlen[month-1])
		return 0;
	return 1;
}

bool parser::isValidTime(int time) {
	int minute = time%10;
	if((time>=100)&&(time<=2400) && minute <=59) {
		return 1;
	} else {
		return 0;
	}
}

bool parser::checkIsDateOverdue(int day, int month, int year,int timing) {
	bool result = true;
	parser p;
	int sysDay, sysMonth, sysYear, sysHr, sysMin, sysTime;
	
	sysDay = p.getSystemDay();
	sysMonth = p.getSystemMonth();
	sysYear = p.getSystemYear();
	sysHr = p.getSystemHour();
	sysMin = p.getSystemMinute();
	sysTime = sysHr * 100 + sysMin;

	if(year < sysYear) {
		return false;
	} else if(year == sysYear && month < sysMonth) {
		return  false;
	} else if(year == sysYear && month == sysMonth && day < sysDay) {
		return false;
	} else if(year == sysYear && month == sysMonth && day == sysDay && timing < sysTime) {
		return false;
	}
	return result;
}

//Determine the recurring period the user want to do a recurring task
//precondition : user enter a recurring task
//postcondition : return the recurring period, if not specified by user, default period is zero
int parser::getRecurPeriod(string description) {
	assert(description.length() != 0);
	int start = getStartPosition(description);
	int end = getEndPosition(description);

	string recurPeriod = description.substr(start, end - start);

	for(int i = 0; i < recurPeriod.size(); ++i) {
		if(!isdigit(recurPeriod[i])) {
			return 0;
		} else {
			int convertedNum;
			convertedNum = atoi(recurPeriod.c_str());
			return convertedNum;
		}
	}
}

//Determine if the user want to do a task daily/weekly/monthly/yearly
//precondition : user input a recurring tas
//postcondition : return the recurring command word
string parser::getRecurruingCommandWord(string description) {
	assert(description.length() != 0);
	int start = getStartPosition(description);
	int end = getEndPosition(description);

	string recurringCommandWord = description.substr(start, end - start);	

	return recurringCommandWord;
}


//Determine the position of the start of the description
//precondition : take in the description entered by user
//postcondition : return the start position
int parser::getStartPosition(string description) {
	assert(description.length() != 0);
	int start;
	
	start = description.find_first_not_of(" ");
	
	return start;
}

//Determine the position of the end of the first word
//precondition : take in the description entered by user
//postcondition : return the end position
int parser::getEndPosition(string description) {
	assert(description.length() != 0);
	int end;

	end = description.find_first_of(" ");

	return end;
}
