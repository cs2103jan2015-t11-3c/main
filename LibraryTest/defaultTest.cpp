#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(deafulat_Test)
	{
	public:
		
		//@author A0113745J
		TEST_METHOD(TEST_checkIfIsToday)
		{
			defaultclass d;
			parser p;
			int day = p.getSystemDay();
			int month = p.getSystemMonth();
			int year = p.getSystemYear();
			bool testResult;
			testResult = d.checkIfIsToday(day,month,year);
			Assert::AreEqual(testResult,true);
		}
		TEST_METHOD(TEST_checkIfIsToday_year)
		{
			defaultclass d;
			parser p;
			int day = p.getSystemDay();;
			int month = p.getSystemMonth();
			int year = 15;
			bool testResult;
			testResult = d.checkIfIsToday(day,month,year);
			Assert::AreEqual(testResult,false);
		}
		TEST_METHOD(TEST_checkIfIsTmr)
		{
			defaultclass d;
			parser p;
			int day = p.getSystemDay()+1;
			int month = p.getSystemMonth();
			int year = p.getSystemYear();
			bool testResult;
			testResult = d.checkIfIsTomorrow(day,month,year);
			Assert::AreEqual(testResult,true);
		}
		TEST_METHOD(TEST_checkIfIsTmr_2)
		{
			defaultclass d;
			parser p;
			int day = p.getSystemDay()+1;
			int month = 04;
			int year = p.getSystemYear();
			bool testResult;
			testResult = d.checkIfIsTomorrow(day,month,year);
			Assert::AreEqual(testResult,true);
		}
		TEST_METHOD(TEST_addFloatTask)
		{
			defaultclass d;
			vector<task> Vec;
			vector<undo> undomemory;
			storage *store=storage::getInstance();
			string inputStr = "TASK NAME";
			d.addFloatTask(inputStr,Vec,store, undomemory);
			string output = Vec[0].returntext();
			Assert::AreEqual(inputStr,output);
		}
		TEST_METHOD(Test_addDeadlineTask)
		{
			defaultclass d;
			vector<task> vec;
			vector<undo> undomemory;
			storage *store=storage::getInstance();
			string inputStr = "swimming /by 1000 on 10/10/2015";
			string expected = "swimming by 1000 on 10/10/2015";
			d.addDeadlineTask(inputStr,vec,store, undomemory);
			int size = vec.size();
			Assert::AreEqual(size,1);
			string output = vec[0].displayDeadline(0);
			string result = output.substr(2);
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(Test_addTimedTask)
		{
			defaultclass d;
			vector<task> vec;
			vector<undo> undomemory;
			storage *store=storage::getInstance();
			string inputStr = "attend meeting <love from heart> /from 2400 on 1/2/2016 to 0600 on 2/2/2016";
			string expected = "attend meeting <love from heart> from 2400 on 1/2/2016 to 600 on 2/2/2016";
			d.addTimedTask(inputStr,vec,store, undomemory);
			string output = vec[0].displayTimed(0);
			string result = output.substr(2);
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(TEST_addRecurTask)
		{
			defaultclass d;
			vector<task> Vec;
			vector<undo> undomemory;
			storage *store=storage::getInstance();
			int recurPeriod = 2;
			string recurringCommandWord = "yearly";
			string description = "yearly TEST WEEKLY /from 2400 on 1/1/2016 to 2300 on 2/1/2016";
			d.addRecurringTask(recurPeriod,recurringCommandWord,description,Vec,store, undomemory);
			string test1 = "1.TEST WEEKLY from 2400 on 1/1/2016 to 2300 on 2/1/2016";
			string test2 = "2.TEST WEEKLY from 2400 on 1/1/2017 to 2300 on 2/1/2017";
			string output1 = Vec[0].displayTimed(0);
			string output2 = Vec[1].displayTimed(1);
			Assert::AreEqual(test1,output1);
			Assert::AreEqual(test2,output2);
		}
		TEST_METHOD(TEST_addRecurTask_2)
		{
			defaultclass d;
			vector<task> Vec;
			vector<undo> undomemory;
			storage *store=storage::getInstance();
			int recurPeriod = 2;
			string recurringCommandWord = "weekly";
			string description = "weekly TEST WEEKLY /from 2400 on 1/1/2016 to 2300 on 2/1/2016";
			d.addRecurringTask(recurPeriod,recurringCommandWord,description,Vec,store, undomemory);
			string test1 = "1.TEST WEEKLY from 2400 on 1/1/2016 to 2300 on 2/1/2016";
			string test2 = "2.TEST WEEKLY from 2400 on 8/1/2016 to 2300 on 9/1/2016";
			string output1 = Vec[0].displayTimed(0);
			string output2 = Vec[1].displayTimed(1);
			Assert::AreEqual(test1,output1);
			Assert::AreEqual(test2,output2);
		}
		TEST_METHOD(TEST_addRecurTask_3)
		{
			defaultclass d;
			vector<task> Vec;
			vector<undo> undomemory;
			storage *store=storage::getInstance();
			int recurPeriod = 0;
			string recurringCommandWord = "yearly";
			string description = "yearly birthday /by 2400 on 25/4/2016";
			d.addRecurringTask(recurPeriod,recurringCommandWord,description,Vec,store, undomemory);
			string test1 = "1.birthday by 2400 on 25/4/2016";
			string test2 = "2.birthday by 2400 on 25/4/2017";
			string test3 = "3.birthday by 2400 on 25/4/2018";
			string test4 = "4.birthday by 2400 on 25/4/2019";
			string test5 = "5.birthday by 2400 on 25/4/2020";
			string output1 = Vec[0].displayDeadline(0);
			string output2 = Vec[1].displayDeadline(1);
			string output3 = Vec[2].displayDeadline(2);
			string output4 = Vec[3].displayDeadline(3);
			string output5 = Vec[4].displayDeadline(4);
			Assert::AreEqual(test1,output1);
			Assert::AreEqual(test2,output2);
			Assert::AreEqual(test3,output3);
			Assert::AreEqual(test4,output4);
			Assert::AreEqual(test5,output5);
		}
		TEST_METHOD(Test_displayFloat)
		{
			defaultclass d;
			storage *store=storage::getInstance();
			vector<task> vec;
			vector<task> tempVec;
			vector<undo> undomemory;
			string inputStr1 = "TASK 1";
			string inputStr2 = "TASK 2";
			d.addFloatTask(inputStr1,vec,store, undomemory);
			d.addFloatTask(inputStr2,vec,store, undomemory);
			d.displayTask("fileName","float",vec,tempVec);
			string output1 = tempVec[0].displayFloat(0);
			string output2 = tempVec[1].displayFloat(1);
			string result1 = output1.substr(2);
			string result2 = output2.substr(2);
			Assert::AreEqual(inputStr1,result1);
			Assert::AreEqual(inputStr2,result2);
		}
		TEST_METHOD(Test_displayFloat_1)
		{
			defaultclass d;
			storage *store=storage::getInstance();
			vector<task> vec;
			vector<task> tempVec;
			vector<undo> undomemory;
			string inputStr1 = "TASK 1";
			string inputStr2 = "This should not appear /by 1000 today";
			string inputStr3 = "TASK 2";
			d.addFloatTask(inputStr1,vec,store, undomemory);
			d.addDeadlineTask(inputStr2,vec,store, undomemory);
			d.addFloatTask(inputStr3,vec,store, undomemory);
			d.displayTask("fileName","float",vec,tempVec);
			int sizeTest = tempVec.size();
			int expect = 2;
			Assert::AreEqual(expect,sizeTest);
			string output1 = tempVec[0].displayFloat(0);
			string output2 = tempVec[1].displayFloat(1);
			string result1 = output1.substr(2);
			string result2 = output2.substr(2);
			Assert::AreEqual(inputStr1,result1);
			Assert::AreEqual(inputStr3,result2);
		}
		TEST_METHOD(Test_display_deadline)
		{
			defaultclass d;
			storage *store=storage::getInstance();
			vector<task> vec;
			vector<task> tempVec;
			vector<undo> undomemory;
			string inputStr2 = "Test Task";
			d.addFloatTask(inputStr2,vec,store, undomemory);
			d.displayTask("fileName","float",vec,tempVec);
			int sizeOfDisplay = tempVec.size();
			Assert::AreEqual(1,sizeOfDisplay);
		}
		TEST_METHOD(Test_display_timed_recur)
		{
			defaultclass d;
			storage *store=storage::getInstance();
			vector<task> vec;
			vector<task> tempVec;
			vector<undo> undomemory;
			string inputStr1 = "Test Task";
			string inputStr2 = "TEST TASK /from 0600 on 1/1/2016 to 0800 on 2/1/2016";
			d.addRecurringTask(2,"yearly","yearly RECUR TASK /from 2400 on 2/2/2016 to 2400 on 3/2/2016",vec,store, undomemory);
			d.addFloatTask(inputStr1,vec,store, undomemory);
			d.addTimedTask(inputStr2,vec,store, undomemory);
			d.displayTask("fileName","timed",vec,tempVec);
			int sizeOfDisplay = tempVec.size();
			Assert::AreEqual(3,sizeOfDisplay);
			string output1 = tempVec[0].displayTimed(0);
			string output2 = tempVec[1].displayTimed(1);
			string output3 = tempVec[2].displayTimed(2);
			string expStr1 = "TEST TASK from 600 on 1/1/2016 to 800 on 2/1/2016";
			string expStr2 = "RECUR TASK from 2400 on 2/2/2016 to 2400 on 3/2/2016";
			string expStr3 = "RECUR TASK from 2400 on 2/2/2017 to 2400 on 3/2/2017";
			string result1 = output1.substr(2);
			string result2 = output2.substr(2);
			string result3 = output3.substr(2);
			Assert::AreEqual(expStr1,result1);
			Assert::AreEqual(expStr2,result2);
			Assert::AreEqual(expStr3,result3);
		}
		TEST_METHOD(Test_display_Timed_)
		{
			defaultclass d;
			storage *store=storage::getInstance();
			vector<task> vec;
			vector<task> tempVec;
			vector<undo> undomemory;
			d.addRecurringTask(3,"monthly","monthly MONTHLY RECUR /from 2400 on 1/1/2016 to 2400 on 2/1/2016",vec,store, undomemory);
			d.addFloatTask("gym",vec,store, undomemory);
			d.addDeadlineTask("DEADLINE TASK /by 1000 on 1/1/2016",vec,store, undomemory);
			d.addTimedTask("cs tutorial /from 1100 on 3/3/2016 to 1200 on 3/3/2016",vec,store, undomemory);
			d.displayTask("fileName","timed",vec,tempVec);
			int tempVecSize = tempVec.size();
			Assert::AreEqual(4,tempVecSize);
			string output1 = tempVec[0].displayTimed(0);
			string output2 = tempVec[1].displayTimed(1);
			string output3 = tempVec[2].displayTimed(2);
			string output4 = tempVec[3].displayTimed(3);
			string result1 = output1.substr(2);
			string result2 = output2.substr(2);
			string result3 = output3.substr(2);
			string result4 = output4.substr(2);
			string expected4 = "cs tutorial from 1100 on 3/3/2016 to 1200 on 3/3/2016";
			string expected1 = "MONTHLY RECUR from 2400 on 1/1/2016 to 2400 on 2/1/2016";
			string expected2 = "MONTHLY RECUR from 2400 on 1/2/2016 to 2400 on 2/2/2016";
			string expected3 = "MONTHLY RECUR from 2400 on 1/3/2016 to 2400 on 2/3/2016";
			Assert::AreEqual(expected1,result1);
			Assert::AreEqual(expected2,result2);
			Assert::AreEqual(expected3,result3);
			Assert::AreEqual(expected4,result4);
		}
		TEST_METHOD(Test_displayTask_All)
		{
			defaultclass d;
			storage *store=storage::getInstance();
			vector<task> vec;
			vector<task> tempVec;
			vector<undo> undomemory;
			d.addFloatTask("task I",vec,store, undomemory);
			d.addDeadlineTask("task II /by 1000 on 1/1/2016",vec,store, undomemory);
			d.displayTask("fileName","all",vec,tempVec);
			int size = tempVec.size();
			Assert::AreEqual(2,size);
			string output1 = tempVec[0].displayFloat(0);
			string output2 = tempVec[1].displayDeadline(1);
			string result1 = output1.substr(2);
			string result2 = output2.substr(2);
			string expected1 = "task I";
			string expected2 = "task II by 1000 on 1/1/2016";
			Assert::AreEqual(expected1,result1);
			Assert::AreEqual(expected2,result2);
		}
	};
}
