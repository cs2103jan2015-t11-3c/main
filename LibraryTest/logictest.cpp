#include "stdafx.h"
#include "CppUnitTest.h"

//@author A0116006X

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibraryTest
{		
	TEST_CLASS(logictest)
	{
	public:
		
		TEST_METHOD(TestDeleteItem)
		{
			vector<task> toDoList;
			logic function;
			int size, actualsize = 9, index = 5;
			storage *store=storage::getInstance();

			for(int i = 0; i < 10; i++){
				task datainput("deleteTest");
				datainput.addFloatItem();
				toDoList.push_back(datainput);
			}

			function.deleteItem(index, toDoList);
			size = toDoList.size();
			Assert::AreEqual (actualsize, size);
		}

		TEST_METHOD(TestClearItem)
		{
			vector<task> toDoList;
			logic function;
			int actualsize = 0, size;
						
			for(int i = 0; i < 10; i++){
			task datainput("clearTest");
			datainput.addFloatItem();
			toDoList.push_back(datainput);
			}

			function.clearAll(toDoList);
			size = toDoList.size();
			Assert::AreEqual (actualsize, size);
		}

		TEST_METHOD(TestMarkCompleted)
		{
			vector<task> toDoList;
			logic function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);

			task datainputone("gym");
			datainputone.addFloatItem();
			toDoList.push_back(datainputone);

			task datainputtwo("CS2103 report");
			datainputtwo.addDeadlineItem(13, 4, 2015, 2300);
			toDoList.push_back(datainputtwo);

			task datainputthree("IE2150 slides");
			datainputthree.addDeadlineItem(17, 4, 2015, 1500);
			toDoList.push_back(datainputthree);

			task datainputfour("IE2130 poster");
			datainputfour.addDeadlineItem(17, 4, 2015, 1000);
			toDoList.push_back(datainputfour);

			task datainputfive("coach supper");
			datainputfive.addTimedItem(10, 4, 2015, 2000, 10, 4, 2015, 2300);
			toDoList.push_back(datainputfive);

			task datainputsix("CS2103 meeting");
			datainputsix.addTimedItem(11, 4, 2015, 1200, 12, 4, 2015, 1500);
			toDoList.push_back(datainputsix);

			task datainputseven("family dinner");
			datainputseven.addTimedItem(11, 4, 2015, 1800, 11, 4, 2015, 2100);
			toDoList.push_back(datainputseven);

			function.markCompleted(3, toDoList);
			Assert::AreEqual (true, (bool)toDoList[3].returnstatus());
		}
		
		TEST_METHOD(testSortText){
			vector<task> toDoList, temp;
			logic function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);

			task datainputone("gym");
			datainputone.addFloatItem();
			toDoList.push_back(datainputone);

			task datainputtwo("fix fridge");
			datainputtwo.addFloatItem();
			toDoList.push_back(datainputtwo);

			task datainputthree("fix fridge");
			datainputthree.addFloatItem();
			temp.push_back(datainputthree);

			task datainputfour("gym");
			datainputfour.addFloatItem();
			temp.push_back(datainputfour);

			task datainputfive("meeting");
			datainputfive.addFloatItem();
			temp.push_back(datainputfive);

			function.sortText(toDoList);
			for(unsigned int i = 0; i < temp.size(); i++){
				int check = toDoList[i].returntext().compare(temp[i].returntext());
				Assert::AreEqual(0, check);
			}
		}

		TEST_METHOD(testSortDate){
			vector<task> toDoList, temp;
			logic function;

			task datainputzero("family dinner");
			datainputzero.addTimedItem(12, 4, 2015, 1800, 12, 4, 2015, 2100);
			toDoList.push_back(datainputzero);

			task datainputone("CS2103 meeting");
			datainputone.addTimedItem(11, 4, 2015, 1200, 11, 4, 2015, 1500);
			toDoList.push_back(datainputone);

			task datainputtwo("CS2103 report");
			datainputtwo.addDeadlineItem(13, 4, 2015, 2300);
			toDoList.push_back(datainputtwo);

			task datainputthree("IE2150 slides");
			datainputthree.addDeadlineItem(17, 4, 2015, 1500);
			toDoList.push_back(datainputthree);


			task datainputfour("CS2103 meeting");
			datainputfour.addTimedItem(11, 4, 2015, 1200, 11, 4, 2015, 1500);
			temp.push_back(datainputfour);

			task datainputfive("family dinner");
			datainputfive.addTimedItem(12, 4, 2015, 1800, 12, 4, 2015, 2100);
			temp.push_back(datainputfive);

			task datainputsix("CS2103 report");
			datainputsix.addDeadlineItem(13, 4, 2015, 2300);
			temp.push_back(datainputsix);

			task datainputseven("IE2150 slides");
			datainputseven.addDeadlineItem(17, 4, 2015, 1500);
			temp.push_back(datainputseven);

			function.sortDates(toDoList);
			for(unsigned int i = 0; i < temp.size(); i++){
				int check = toDoList[i].returntext().compare(temp[i].returntext());
				Assert::AreEqual(0, check);
			}
		}

		TEST_METHOD(testSortEndTime){
			vector<task> toDoList, temp;
			logic function;

			task datainputzero("family dinner");
			datainputzero.addTimedItem(11, 4, 2015, 1800, 11, 4, 2015, 2100);
			toDoList.push_back(datainputzero);

			task datainputone("CS2103 meeting");
			datainputone.addTimedItem(11, 4, 2015, 1200, 11, 4, 2015, 1500);
			toDoList.push_back(datainputone);

			task datainputtwo("CS2103 report");
			datainputtwo.addDeadlineItem(11, 4, 2015, 2300);
			toDoList.push_back(datainputtwo);


			task datainputfour("CS2103 meeting");
			datainputfour.addTimedItem(11, 4, 2015, 1200, 11, 4, 2015, 1500);
			temp.push_back(datainputfour);

			task datainputfive("family dinner");
			datainputfive.addTimedItem(11, 4, 2015, 1800, 11, 4, 2015, 2100);
			temp.push_back(datainputfive);

			task datainputsix("CS2103 report");
			datainputsix.addDeadlineItem(11, 4, 2015, 2300);
			temp.push_back(datainputsix);

			function.sortEndTime(toDoList);
			for(unsigned int i = 0; i < temp.size(); i++){
				int check = toDoList[i].returntext().compare(temp[i].returntext());
				Assert::AreEqual(0, check);
			}
		}

		TEST_METHOD(testSearchTask){
			vector<task> toDoList, tempVec;
			logic function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);

			task datainputone("gym");
			datainputone.addFloatItem();
			toDoList.push_back(datainputone);

			task datainputtwo("CS2103 report");
			datainputtwo.addDeadlineItem(13, 4, 2015, 2300);
			toDoList.push_back(datainputtwo);

			task datainputthree("IE2150 meeting");
			datainputthree.addDeadlineItem(17, 4, 2015, 1500);
			toDoList.push_back(datainputthree);

			task datainputfour("IE2130 poster");
			datainputfour.addDeadlineItem(17, 4, 2015, 1000);
			toDoList.push_back(datainputfour);

			task datainputfive("coach supper");
			datainputfive.addTimedItem(10, 4, 2015, 2000, 10, 4, 2015, 2300);
			toDoList.push_back(datainputfive);

			task datainputsix("CS2103 meeting");
			datainputsix.addTimedItem(11, 4, 2015, 1200, 12, 4, 2015, 1500);
			toDoList.push_back(datainputsix);

			task datainputseven("family dinner");
			datainputseven.addTimedItem(11, 4, 2015, 1800, 11, 4, 2015, 2100);
			toDoList.push_back(datainputseven);

			function.searchWord(toDoList, "meeting", tempVec);
			Assert::AreEqual(3, (int)tempVec.size());

			function.searchTask(toDoList, tempVec, "17");
			Assert::AreEqual(2, (int)tempVec.size());
		}


		TEST_METHOD(testsearchword){
			vector<task> toDoList, tempVec;
			logic function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);

			task datainputone("gym");
			datainputone.addFloatItem();
			toDoList.push_back(datainputone);

			task datainputtwo("CS2103 report");
			datainputtwo.addDeadlineItem(13, 4, 2015, 2300);
			toDoList.push_back(datainputtwo);

			task datainputthree("IE2150 meeting");
			datainputthree.addDeadlineItem(17, 4, 2015, 1500);
			toDoList.push_back(datainputthree);

			task datainputfour("IE2130 poster");
			datainputfour.addDeadlineItem(17, 4, 2015, 1000);
			toDoList.push_back(datainputfour);

			task datainputfive("coach supper");
			datainputfive.addTimedItem(10, 4, 2015, 2000, 10, 4, 2015, 2300);
			toDoList.push_back(datainputfive);

			task datainputsix("CS2103 meeting");
			datainputsix.addTimedItem(11, 4, 2015, 1200, 12, 4, 2015, 1500);
			toDoList.push_back(datainputsix);

			task datainputseven("family dinner");
			datainputseven.addTimedItem(11, 4, 2015, 1800, 11, 4, 2015, 2100);
			toDoList.push_back(datainputseven);

			function.searchTask(toDoList, tempVec, "meeting");
			Assert::AreEqual(3, (int)tempVec.size());
		}

		TEST_METHOD(testSearchDigit){
			vector<task> toDoList, tempVec;
			logic function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);

			task datainputone("gym");
			datainputone.addFloatItem();
			toDoList.push_back(datainputone);

			task datainputtwo("CS2103 report");
			datainputtwo.addDeadlineItem(13, 4, 2015, 2300);
			toDoList.push_back(datainputtwo);

			task datainputthree("IE2150 meeting");
			datainputthree.addDeadlineItem(17, 4, 2015, 1500);
			toDoList.push_back(datainputthree);

			task datainputfour("IE2130 poster");
			datainputfour.addDeadlineItem(17, 4, 2015, 1000);
			toDoList.push_back(datainputfour);

			task datainputfive("coach supper");
			datainputfive.addTimedItem(10, 4, 2015, 2000, 10, 4, 2015, 2300);
			toDoList.push_back(datainputfive);

			task datainputsix("CS2103 meeting");
			datainputsix.addTimedItem(11, 4, 2015, 1200, 11, 4, 2015, 1500);
			toDoList.push_back(datainputsix);

			task datainputseven("family dinner");
			datainputseven.addTimedItem(11, 4, 2015, 1800, 11, 4, 2015, 2100);
			toDoList.push_back(datainputseven);

			function.searchDigit(toDoList, "17", tempVec);
			Assert::AreEqual(2, (int)tempVec.size());
		}

		

		TEST_METHOD(testCheckSameDay){
			logic function;
			bool result;

			result = function.checkIsSameDate(12, 12);
			Assert::AreEqual(true, result);

			result = function.checkIsSameDate(13, 12);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(testCheckSameMonth){
			logic function;
			bool result;

			result = function.checkIsSameMonth(2, 2);
			Assert::AreEqual(true, result);

			result = function.checkIsSameMonth(3, 2);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(testCheckSameYear){
			logic function;
			bool result;

			result = function.checkIsSameYear(2015, 2015);
			Assert::AreEqual(true, result);

			result = function.checkIsSameMonth(2017, 2015);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(testCheckStartAndEndDate){
			logic function;
			bool result;

			result = function.checkIfStartTimeIsEarlierThanEndTime(5, 5, 2015, 1400, 5, 5, 2015, 1200);
			Assert::AreEqual(true, result);

			result = function.checkIfStartTimeIsEarlierThanEndTime(5, 5, 2015, 1000, 5, 5, 2015, 1200);
			Assert::AreEqual(false, result);
		}
	};
}