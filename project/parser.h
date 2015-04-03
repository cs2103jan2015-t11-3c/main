#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class parser{
public:
	bool isValidCommand(const string command, const string description);
	void trimString(string &description);
	int convertStringToIntegerIndex(const string description);
	int checktype(string description);
	
	void splitinputDeadline(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time);
	void splitinputTimed(string description, string &text, int &s_date, int &s_month, int &s_year, int &s_time, int &e_date, int &e_month, int &e_year, int &e_time);
};
#endif
