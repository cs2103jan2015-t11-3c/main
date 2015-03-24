#include "parser.h"
#include <iostream>
#include <sstream>
#include "logic.h"


//Checks if the command entered is a recognised valid user command
//Checks if the description entered is valid for the command entered
//Prints error messages if either of the aforementioned conditions are not met
bool parser::isValidCommand(const string command, const string description){
	logic function;
	if(command=="add") {
		if(description.size()==0) {
			function.printMessage(ERROR_MISSING_DESCRIPTION);
			return false;
		}
		return true;
	}
	else if(command=="delete" ) {
		if(description.size()==0) {
			function.printMessage(ERROR_MISSING_DESCRIPTION);
			return false;
		}

		unsigned int index=0;

		while(index<description.size()) {
			if(!isdigit(description[index])) {
				function.printMessage(ERROR_INVALID_INDEX);
				return false;
			}
			index++;
		}
		return true;
	}
	else if(command=="display"||command=="clear"||command=="exit"||command=="undo")
		return true;

	else if (command=="edit"){
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

void parser::splitinputtypeone(string description, string &text){
	text = description;
}
		
void parser::splitinputtypetwo(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time){
	string temp;

	size_t bypos = description.find("by");
	text = description.substr(0 , bypos-1);
	description = description.substr(bypos + 3);
	istringstream in(description);
		in>>e_time;
		in>>temp;
		in>>e_date;
		in>>e_month;
		in>>e_year;
}

void parser::splitinputtypethree(string description, string &text, int &s_date, int &s_month, int &s_year, int &s_time, int &e_date, int &e_month, int &e_year, int &e_time){
	string temp;
	
	size_t bypos = description.find("from");
	text = description.substr(0 , bypos-1);
	description = description.substr(bypos+5);
	istringstream in(description);
	in>>s_time;
	in>>temp;
	in>>s_date;
	in>>s_month;
	in>>s_year;
	in>>temp;
	in>>e_time;
	in>>temp;
	in>>e_date;
	in>>e_month;
	in>>e_year;
}