#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(deafulat_Test)
	{
	public:
		
		TEST_METHOD(Test_getRecurPeriod)
		{
			defaultclass d;
			int expected = 3;
			string testStr = "3 daily swimming /by 1000 today";
			int testResult = d.getRecurPeriod(testStr);
			Assert::AreEqual(expected,testResult);
		}
		TEST_METHOD(Test_default_getRecurPeriod)
		{
			defaultclass d;
			int expected = 0;
			string testStr = "daily swimming /by 1000 tmr";
			int testResult = d.getRecurPeriod(testStr);
			Assert::AreEqual(expected,testResult);
		}
		TEST_METHOD(Test_getStartPos)
		{
			defaultclass d;
			string testStr = "weekly 2 shopping /by 1000 on 1/1/2016";
			int result = d.getStartPosition(testStr);
			int expected = 0;
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(Test_getEndPos)
		{
			defaultclass d;
			string testStr = "weekly 2 shopping /by 1000 on 1/1/2016";
			int result = d.getEndPosition(testStr);
			int expected = 6;
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(Test_getRecurWord)
		{
			defaultclass d;
			string expectedStr = "yearly";
			string str = "5 yearly swimming /by 1000 tmr";
			int endPos = d.getEndPosition(str);
			string testStr = str.substr(endPos+1);
			string testResult = d.getRecurruingCommandWord(testStr);
			Assert::AreEqual(expectedStr,testResult);
		}
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
			storage store;
			string inputStr = "TASK NAME";
			d.addFloatTask(inputStr,Vec,&store);
			string output = Vec[0].returntext();
			Assert::AreEqual(inputStr,output);
		}
		TEST_METHOD(Test_addDeadlineTask)
		{
			defaultclass d;
			vector<task> vec;
			storage store;
			string inputStr = "swimming by the bay /by 1000 on 10/10/2015";
			string expected = "swimming by the bay by 1000 on 10/10/2015";
			d.addDeadlineTask(inputStr,vec,&store);
			string output = vec[0].displayDeadline(0);
			string result = output.substr(2);
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(Test_addTimedTask)
		{
			defaultclass d;
			vector<task> vec;
			storage store;
			string inputStr = "attend meeting <love from heart> /from 2400 on 1/2/2016 to 0600 on 2/2/2016";
			string expected = "attend meeting <love from heart> from 2400 on 1/2/2016 to 600 on 2/2/2016";
			d.addTimedTask(inputStr,vec,&store);
			string output = vec[0].displayTimed(0);
			string result = output.substr(2);
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(TEST_addRecurTask)
		{
			defaultclass d;
			vector<task> Vec;
			storage store;
			int recurPeriod = 2;
			string recurringCommandWord = "daily";
			string description = "daily TEST TEST /by 2400 on 1/1/2016";
			d.addRecurringTask(recurPeriod,recurringCommandWord,description,Vec,&store);
			string test1 = "1.TEST TEST by 2400 on 1/1/2016";
			string test2 = "2.TEST TEST by 2400 on 2/1/2016";
			string output1 = Vec[0].displayDeadline(0);
			string output2 = Vec[1].displayDeadline(1);
			Assert::AreEqual(test1,output1);
			Assert::AreEqual(test2,output2);
		}
		TEST_METHOD(TEST_addRecurTask_2)
		{
			defaultclass d;
			vector<task> Vec;
			storage store;
			int recurPeriod = 2;
			string recurringCommandWord = "weekly";
			string description = "weekly TEST WEEKLY /from 2400 on 1/1/2016 to 2300 on 2/1/2016";
			d.addRecurringTask(recurPeriod,recurringCommandWord,description,Vec,&store);
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
			storage store;
			int recurPeriod = 0;
			string recurringCommandWord = "yearly";
			string description = "yearly birthday /by 2400 on 25/4/2016";
			d.addRecurringTask(recurPeriod,recurringCommandWord,description,Vec,&store);
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
		/*TEST_METHOD(Test_executeCommand)
		{
			defaultclass d;
			string fileName;
			storage store;
			vector<task> vec;
			vector<undo> undoVec;
			undo currentUndo;
			string command = "add";
			string description = "float1";
			d.defaultexecuteCommand(fileName,&store,command,description,vec,undoVec,currentUndo);
			string expected1 = "float1";
			string output1 = vec[0].displayFloat(0);
			Assert::AreEqual(expected1,output1);
		}*/
		TEST_METHOD(Test_displayFloat)
		{
			defaultclass d;
			storage store;
			vector<task> vec;
			vector<task> tempVec;
			string inputStr1 = "TASK 1";
			string inputStr2 = "TASK 2";
			d.addFloatTask(inputStr1,vec,&store);
			d.addFloatTask(inputStr2,vec,&store);
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
			storage store;
			vector<task> vec;
			vector<task> tempVec;
			string inputStr1 = "TASK 1";
			string inputStr2 = "This should not appear /by 1000 today";
			string inputStr3 = "TASK 2";
			d.addFloatTask(inputStr1,vec,&store);
			d.addDeadlineTask(inputStr2,vec,&store);
			d.addFloatTask(inputStr3,vec,&store);
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
			storage store;
			vector<task> vec;
			vector<task> tempVec;
			string inputStr1 = "DAILY TASK /by 1000 on 1/1/2016";
			string inputStr2 = "Test Task";
			d.addDeadlineTask(inputStr1,vec,&store);
			d.addFloatTask(inputStr2,vec,&store);
			d.displayTask("fileName","deadline",vec,tempVec);
			int sizeOfDisplay = tempVec.size();
			Assert::AreEqual(1,sizeOfDisplay);
			string output1 = tempVec[0].displayDeadline(0);
			string expStr1 = "DAILY TASK by 1000 on 1/1/2016";
			string result1 = output1.substr(2);
			Assert::AreEqual(expStr1,result1);
		}
		TEST_METHOD(Test_display_deadline_recur)
		{
			defaultclass d;
			storage store;
			vector<task> vec;
			vector<task> tempVec;
			string inputStr1 = "Test Task";
			string inputStr2 = "TEST TASK /by 0600 on 1/1/2016";
			d.addRecurringTask(2,"yearly","yearly RECUR TASK /by 2400 on 2/2/2016",vec,&store);
			d.addFloatTask(inputStr1,vec,&store);
			d.addDeadlineTask(inputStr2,vec,&store);
			d.displayTask("fileName","deadline",vec,tempVec);
			int sizeOfDisplay = tempVec.size();
			Assert::AreEqual(3,sizeOfDisplay);
			string output1 = tempVec[0].displayDeadline(0);
			string output2 = tempVec[1].displayDeadline(1);
			string output3 = tempVec[2].displayDeadline(2);
			string expStr1 = "TEST TASK by 600 on 1/1/2016";
			string expStr2 = "RECUR TASK by 2400 on 2/2/2016";
			string expStr3 = "RECUR TASK by 2400 on 2/2/2017";
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
			storage store;
			vector<task> vec;
			vector<task> tempVec;
			d.addRecurringTask(3,"monthly","monthly MONTHLY RECUR /from 2400 on 1/1/2016 to 2400 on 2/1/2016",vec,&store);
			d.addFloatTask("gym",vec,&store);
			d.addDeadlineTask("DEADLINE TASK /by 1000 on 1/1/2016",vec,&store);
			d.addTimedTask("cs tutorial /from 1100 on 3/3/2016 to 1200 on 3/3/2016",vec,&store);
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
		TEST_METHOD(Test_delete_task)
		{
			defaultclass d,defaultMemory;
			vector<task> vec,tempVec;
			storage store;
			vector<undo> undoMemory;
			string fileName = "fileName";
			d.addFloatTask("float task I",vec,&store);
			d.addFloatTask("float task II",vec,&store);
			d.displayTask(fileName,"float",vec,tempVec);
			d.deleteTask(fileName,"2",vec,&store,undoMemory,tempVec,defaultMemory);
			int sizeVec = vec.size();
			Assert::AreEqual(1,sizeVec);
			string output = vec[0].displayFloat(0);
			string result = output.substr(2);
			string expected = "float task I";
			Assert::AreEqual(expected,result);
		}
		TEST_METHOD(Test_displayTask_All)
		{
			defaultclass d;
			storage store;
			vector<task> vec;
			vector<task> tempVec;
			d.addFloatTask("task I",vec,&store);
			d.addDeadlineTask("task II /by 1000 on 1/1/2016",vec,&store);
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
		TEST_METHOD(Test_clearTask)
		{
			defaultclass d;
			storage store;
			vector<task> vec;
			vector<undo> undoMemory;
			d.addFloatTask("task I",vec,&store);
			d.addDeadlineTask("task II /by 1000 on 1/1/2016",vec,&store);
			int sizeInitial = vec.size();
			Assert::AreEqual(2,sizeInitial);
			d.clearTasks("fileName",&store,vec,undoMemory);
			int sizeAfterClear = vec.size();
			Assert::AreEqual(0,sizeAfterClear);
		}





	};
}