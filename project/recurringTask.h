#pragma once
#include "Task.h"
#include "logic.h"
class recurringTask
{

public:
	recurringTask(void);
	~recurringTask(void);
	void DailyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList);
	void WeeklyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList);
	void MonthlyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList);
	void YearlyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList);
	bool isValidforMoreDays(int month);
	void addRecDeadline(string description, int e_date, int e_month, int e_year, int e_time,vector<task> &toDoList);
	void addRecTimed(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,vector<task> &toDoList);

	int recurPeriod();


};

