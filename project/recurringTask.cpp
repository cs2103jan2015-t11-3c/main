#include "recurringTask.h"

recurringTask::recurringTask(void )
{
}

recurringTask::recurringTask(string text, int stime ,int etime )
{    description=text;
	 s_time=stime;
	 e_time=etime;
}

recurringTask::~recurringTask(void)
{
}

void recurringTask::AddRecurring(string recurType,int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,int type,vector<task> &toDoList){
	
	if(recurType=="daily")
		DailyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="weekly")
	    WeeklyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="monthly")
		MonthlyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	if(recurType=="yearly")
		YearlyRec(e_date,e_month, e_year, s_date,s_month, s_year, type,toDoList);
	return;
}

void recurringTask::DailyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,int type,vector<task> &toDoList){
	int n=30;                                                                   //the default recurring period for daily task is set to be 30 days
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
          addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		  e_date=e_date+1;
		}
		else{
			e_date=1;
			e_month++;
		 if (function.isValidDate(e_date,e_month,e_year)){
              addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
		    e_date=e_date+1;
		}
		 
		}
	}   
	return;
}

void recurringTask::WeeklyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,int type,vector<task> &toDoList){
	int n=52;                           //default recurring period for weekly task is 1 year(52)weeks;
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
             addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

		  e_date=e_date+7;
		}
		else{
			e_date=e_date-getNumDays(e_month,e_year);                      
			e_month++;                                                   //move to next month
			if(function.isValidDate(e_date,e_month,e_year)){
			   addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

			   e_date=e_date+7;
			}
			else{
				e_year++;                                           //move to the next year
				e_month=1;
				e_date-=getNumDays(e_month,e_year); 
				if(function.isValidDate(e_date,e_month,e_year)){
				    addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

			       e_date=e_date+7;
				}
			}
		}


}
	return;
}


void recurringTask::MonthlyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,int type,vector<task> &toDoList){
	int n=12;                          //default recurring period is 12 month if user do not specify
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
            addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

		  e_month=e_month+1;
		}
		else if(!isValidforMoreDays(e_month)){                                    //same year, if the date is 31st of the month, make it the last day of each month 
			if(e_date==31&&function.isValidDate(e_date-1,e_month,e_year)){
		        addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			}
			else if((e_date==31||e_date==30)&&e_month==2){                       //special case for Feburary
				if(function.isleapyear(e_year)){
				  addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
				else{
			     addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
				}
			}
		}
			e_month=1;                                          //start from next year
			e_year++;
			if(function.isValidDate(e_date,e_month,e_year)){
		     addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);
			}
			
		}
			return;
}
	
void recurringTask::YearlyRec(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,int type,vector<task> &toDoList){
    int n=5;
	logic function;
    task datainput;
	for(int i=1;i<=n;i++){
		if (function.isValidDate(e_date,e_month,e_year)){
           addTodifferentType(type, e_date, e_month, e_year,s_date, s_month,s_year,  toDoList);

		  e_year=e_year+1;
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

int recurringTask::getNumDays(int month,int year){
	logic function;
	int LMonth[7]={1,3,5,7,8,10,12};
	int SMonth[]={4,6,9,11};
	for(int i=0;i<7;i++){
		if(LMonth[i]==month)
			return 31;
		else if(SMonth[i]==month)
			return 30;
	}
	
	if(month==2&&function.isleapyear(year))
		return 29;
	else
		return 28;
}

void recurringTask::addRecDeadline(int e_date, int e_month, int e_year, vector<task> &toDoList){
	 task datainput;
	 datainput.addItemtypetwo(e_date, e_month, e_year, e_time);
	
	 toDoList.push_back(datainput);
	 return;
}

void recurringTask::addRecTimed(int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,vector<task> &toDoList){
	 task datainput;
	 datainput.addItemtypethree( s_date, s_month, s_year, s_time, e_date, e_month, e_year, e_time);
	 toDoList.push_back(datainput);
	 return;
}

void recurringTask::addTodifferentType(int type, int e_date,int e_month,int e_year,int s_date,int s_month,int s_year,vector<task> &toDoList){
	if(type==2)
			addRecDeadline( e_date, e_month, e_year, toDoList);
	if(type==3)
			addRecTimed( s_date, s_month, s_year, e_date, e_month, e_year, toDoList);
	return;
}

int recurringTask::recurPeriod(){
	cout<<"Enter Recurring period: "<<endl;
	int n;
	cin>>n;
	return n;
}

