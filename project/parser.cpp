#include "parser.h"
#include <sstream>
#include "logic.h"

//Checks if the command entered is a recognised valid user command
//Checks if the description entered is valid for the command entered
//Prints error messages if either of the aforementioned conditions are not met
bool parser::isValidCommand(const string command, const string description){
	if(command=="add"||command=="+"||command== "changeDirectory"||command== "changeFilename") {
		if(description.size()==0) {
			printMessage(ERROR_MISSING_DESCRIPTION);
			return false;
		}
		return true;
	}

	 else if(command=="display"||command=="show"||command=="clear"||command=="clear all"||
		    command=="exit"||command=="undo"||command=="search"||command=="default"||command== "changeDirectory"||command== "changeFilename")
		return true;

	 else if (command=="edit"||command=="modify"||command=="change"||command=="delete"||command=="-"||command=="remove"||command=="done"){
		if(description.size()==0) {
			printMessage(ERROR_MISSING_INDEX);
			return false;
	}  
		return true;
	}

	printMessage(ERROR_INVALID_COMMAND);

	return false;
}


//Remove leading and following whitespaces of a string
void parser::trimString(string &description) {
	size_t lineStart=0, lineEnd=0;
	
	lineStart=description.find_first_not_of(DELIMITERS);
	lineEnd=description.find_last_not_of(DELIMITERS);
	
	if(lineStart==string::npos||lineEnd==string::npos)
		description="";
	else
		description=description.substr(lineStart,lineEnd-lineStart+1);
}

//Converts a number in string format to integer format
//Then converts the integer from base 1 to base 0, ie: 1,2,3,4,5... -> 0,1,2,3,4...
//String must not contain leading or following whitespaces, or function will fail
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

string parser::checktype(string description){
	size_t foundtypeDeadline = description.find("/by");
	size_t foundtypeTimed = description.find("/from");
	if(foundtypeDeadline!=std::string::npos)
		return "deadline";
	else if(foundtypeTimed!=std::string::npos)
		return "timed";
	else
		return "float";
}

		
void parser::splitinputDeadline(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time){
	string temp;
	char c;
	string date;
	string month;
	string year;

	
	
	size_t bypos = description.find("/by");
	text = description.substr(0 , bypos-1);//"meeting"
	description = description.substr(bypos + 4);
	istringstream in(description);// meeting by 1800 31 06 2016
		in>>e_time;//1800

		if(containShortForm(description)){
		getInfo(description, e_date, e_month, e_year);
	}
		else{
		in>>temp;//on
		in>>e_date;//31
		in>>c;//"/"
		in>>date;
		int pos=date.find("/");
		month=date.substr(0,pos);
		year=date.substr(pos+1);
		
		e_month=convertMonth(month);
		e_year=convertStringToInteger(year);

}
}

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

        s_month=convertMonth(smonth);
        
		int pos=date.find("to");
		syear=date.substr(tend+1,pos-tend);
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
		eyear=date.substr(post+1);

		e_month=convertMonth(emonth);
		
		e_year=convertStringToInteger(eyear);
		}
}



int parser::convertAlphabetMonthToInteger (string month) {
	int monthInt=0;
	if (month == "Jan" || month == "jan") {
		monthInt = 1;
	}
	else if (month == "Feb" || month == "feb") {
		monthInt = 2;
	}
	else if (month == "Mar" || month == "mar") {
		monthInt = 3;
	}
	else if (month == "Apr" || month == "apr") {
		monthInt = 4;
	}
	else if (month == "May" || month == "may") {
		monthInt = 5;
	}
	else if (month == "Jun" || month == "jun") {
		monthInt = 6;
	}
	else if (month == "Jul" || month == "jul") {
		monthInt = 7;
	}
	else if (month == "Aug" || month == "aug") {
		monthInt = 8;
	}
	else if (month == "Sep" || month == "sep") {
		monthInt = 9;
	}
	else if (month == "Oct" || month == "oct") {
		monthInt = 10;
	}
	else if (month == "Nov" || month == "nov") {
		monthInt = 11;
	}
	else if (month == "Dec" || month == "dec") {
		monthInt = 12;
	}
	return monthInt;
}

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

void parser::printMessage(const string message) {
	cout << endl << message << endl;
}


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

	//use exception

}

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


int parser::convertMonth(string month){
	if(isNumerical(month)){
			return convertStringToInteger(month);
		}
		else{
			return convertAlphabetMonthToInteger(month);
		}
}

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