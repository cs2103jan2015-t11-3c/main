#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class parser{
public:
	static bool isValidCommand(const string command, const string description);
	static void trimString(string &description);
	static int convertStringToIntegerIndex(const string description);
	static int checktype(string description);
	static void splitinputtypeone(string description, string &text);
	static void splitinputtypetwo(string description, string &text, int &e_date, int &e_month, int &e_year, int &e_time);
	static void splitinputtypethree(string description, string &text, int &s_date, int &s_month, int &s_year, int &s_time, int &e_date, int &e_month, int &e_year, int &e_time);
};
#endif
