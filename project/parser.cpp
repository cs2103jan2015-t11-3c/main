#include "parser.h"
#include <iostream>
#include <sstream>
#include <string>
#include "logic.h" //need to remove this


//Checks if the command entered is a recognised valid user command
//Checks if the description entered is valid for the command entered
//Prints error messages if either of the aforementioned conditions are not met
bool parser::isValidCommand(const string command, const string description){
	logic function;
	if(command=="add"||command=="+") {
		if(description.size()==0) {
			function.printMessage(ERROR_MISSING_DESCRIPTION);
			return false;
		}
		return true;
	}
	else if(command=="delete"||command=="-"||command=="remove") {
		if(description.size()==0) {
			function.printMessage(ERROR_MISSING_DESCRIPTION);
			return false;
		}
		else
		return true;
	}
	else if(command=="display"||command=="show"||command=="clear"||command=="clear all"||command=="exit"||command=="undo"||command=="search"||command=="default")
		return true;

	else if (command=="edit"||command=="modify"||command=="change"){
		if(description.size()==0) {
			function.printMessage(ERROR_MISSING_INDEX);
			return false;
	}   else return true;
	}
	function.printMessage(ERROR_INVALID_COMMAND);

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

int parser::checktype(string description){
	size_t foundtype2 = description.find("by");
	size_t foundtype3 = description.find("from");
	if(foundtype2!=std::string::npos)
		return 2;
	else if(foundtype3!=std::string::npos)
		return 3;
	else
		return 1;
}

		
void parser::splitinputDeadline(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time){
	string temp;
	char c;
	string date;
	string month;
	string year;

	size_t bypos = description.find("by");
	text = description.substr(0 , bypos-1);//"meeting"
	description = description.substr(bypos + 3);
	istringstream in(description);// meeting by 1800 31 06 2016
		in>>e_time;//1800
		in>>temp;//on
		in>>e_date;//31
		in>>c;//"/"
		in>>date;
		int pos=date.find("/");
		month=date.substr(0,pos);
		year=date.substr(pos+1);
		if(isNumerical(month)){
			e_month=convertStringToInteger(month);
		}
		else{
			e_month=convertAlphabetMonthToInteger(month);
		}
		e_year=convertStringToInteger(year);

}//added char c;

void parser::splitinputTimed(string description, string &text, int &s_date, int &s_month, int &s_year, int &s_time, int &e_date, int &e_month, int &e_year, int &e_time){
	string temp;
	char c;
	string date;
	string smonth,emonth;
	string syear,eyear;
	
	size_t bypos = description.find("from");
	text = description.substr(0 , bypos-1);
	description = description.substr(bypos+5);
	istringstream in(description);
	in>>s_time;//1900
	in>>temp;//on
	in>>s_date;//28
	in>>c;//"/"
	in>>date;
		int tend=date.find_first_of("/");
		smonth=date.substr(0,tend);
        if(isNumerical(smonth)){
			s_month=convertStringToInteger(smonth);
		}
		else{
			s_month=convertAlphabetMonthToInteger(smonth);
		}
        
		int pos=date.find("to");
		syear=date.substr(tend+1,pos-tend);
		s_year=convertStringToInteger(syear);

		
	    in>>temp;//to
	    in>>e_time;//2000
	    in>>temp;//on
	    in>>e_date;//29
	    in>>c;//"/"
		in>>date;
		int post=date.find("/");
		emonth=date.substr(0,post);
		eyear=date.substr(post+1);
		if(isNumerical(emonth)){
			e_month=convertStringToInteger(emonth);
		}
		else{
			e_month=convertAlphabetMonthToInteger(emonth);
		}		
		
		e_year=convertStringToInteger(eyear);
}//added char c;



int parser::convertAlphabetMonthToInteger (string month) {
	int monthInt;
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