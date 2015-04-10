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
			int day = 10;
			int month = 4;
			int year = 2015;
			bool testResult;
			testResult = d.checkIfIsToday(day,month,year);
			Assert::AreEqual(testResult,true);
		}
		TEST_METHOD(TEST_checkIfIsToday_year)
		{
			defaultclass d;
			int day = 10;
			int month = 4;
			int year = 15;
			bool testResult;
			testResult = d.checkIfIsToday(day,month,year);
			Assert::AreEqual(testResult,false);
		}
		TEST_METHOD(TEST_checkIfIsTmr)
		{
			defaultclass d;
			int day = 11;
			int month = 4;
			int year = 2015;
			bool testResult;
			testResult = d.checkIfIsTomorrow(day,month,year);
			Assert::AreEqual(testResult,true);
		}
		TEST_METHOD(TEST_addFloatTask)
		{
			defaultclass d;
			parser p;
			vector<task> Vec;
			storage store;
			string inputStr = "TASK NAME";
			d.addFloatTask(inputStr,Vec,&store);
			string output = Vec[0].returntext();
			Assert::AreEqual(inputStr,output);
		}





	};
}