#include "recurringTask.h"


recurringTask::recurringTask(void)
{
}


recurringTask::~recurringTask(void)
{
}
void recurringTask::DailyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList){
	int n=30;
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
        if(type==2)
			addRecDeadline(description, e_date, e_month, e_year, e_time,toDoList);
		if(type==3)
			addRecTimed(description, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time,toDoList);

		  e_date=e_date+i;
		}
		else{
			e_date=1;
			e_month++;
		 if (function.isValidDate(e_date,e_month,e_year)){
          if(type==2)
			addRecDeadline(description, e_date, e_month, e_year, e_time,toDoList);
		  if(type==3)
			addRecTimed(description, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time,toDoList);
		  e_date=e_date+i;
		}
		 return;
		}
	}
}
/*
void recurringTask::WeeklyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList){
	int n=52;
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
         if(type==2)
			addRecDeadline(description, e_date, e_month, e_year, e_time,toDoList);
	   	if(type==3)
			addRecTimed(description, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time,toDoList);

		  e_date=e_date+7*i;
		}
		else

}

*/

void recurringTask::MonthlyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList){
	int n=12;    //default recurring period is 12 month if user do not specify
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
         if(type=2)
			addRecDeadline(description, e_date, e_month, e_year, e_time,toDoList);
		if(type=3)
			addRecTimed(description, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time,toDoList);

		  e_month=e_month+i;
		}
		else if(!isValidforMoreDays(e_month)){                         //same year 
			if(e_date==31&&function.isValidDate(e_date-1,e_month,e_year)){
		     if(type=2)
			 addRecDeadline(description, e_date-1, e_month, e_year, e_time,toDoList);
		     if(type=3)
			 addRecTimed(description, s_date, s_month, s_year, s_time, e_date-1, e_month, e_year, e_time,toDoList);
			}
			else if((e_date==30||e_date==30)&&e_month==2){
				if(function.isleapyear(e_year)){
				if(type==2)
			     addRecDeadline(description, 29, e_month, e_year, e_time,toDoList);
		        if(type==3)
			     addRecTimed(description, s_date, s_month, s_year, s_time, 29, e_month, e_year, e_time,toDoList);
				}
				else{
			    if(type==2)
			     addRecDeadline(description, 28, e_month, e_year, e_time,toDoList);
		        if(type==3)
			     addRecTimed(description, s_date, s_month, s_year, s_time, 28, e_month, e_year, e_time,toDoList);
				}
			}
		}
			e_month=1;                                          //start from next year
			e_year++;
			if(function.isValidDate(e_date,e_month,e_year)){
			if(type==2)
			addRecDeadline(description, e_date, e_month, e_year, e_time,toDoList);
		    if(type==3)
			addRecTimed(description, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time,toDoList);
			}
			
		}
			return;
}
	
void recurringTask::YearlyRec(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,int type,vector<task> &toDoList){
    int n=5;
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
        if(type==2)
			addRecDeadline(description, e_date, e_month, e_year, e_time,toDoList);
		if(type==3)
			addRecTimed(description, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time,toDoList);

		  e_year=e_year+i;
		}
	}
		return;
}

bool recurringTask::isValidforMoreDays(int month){
	if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
		return true;
	}
	else{
		return false;
	}
}

void recurringTask::addRecDeadline(string description, int e_date, int e_month, int e_year, int e_time,vector<task> &toDoList){
	 task datainput;
	 datainput.addItemtypetwo(description, e_date, e_month, e_year, e_time);
	 toDoList.push_back(datainput);
	 return;
}

void recurringTask::addRecTimed(string description,int e_date,int e_month,int e_year,int e_time,int s_date,int s_month,int s_year,int s_time,vector<task> &toDoList){
	 task datainput;
	 datainput.addItemtypethree(description, s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
	 toDoList.push_back(datainput);
	 return;
}

int recurringTask::recurPeriod(){
	cout<<"Enter Recurring period: "<<endl;
	int n;
	cin>>n;
	return n;
}

