#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LibraryTest
{		
	TEST_CLASS(undotest)
	{
	public:
		TEST_METHOD(testConvertToUndoClass){
			vector<undo> undomemory;
			vector<task> toDoList, temp;
			int result;
			undo function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);
			undomemory.push_back(function.converttoundoclass(undomemory, toDoList));

			task datainputone("smoke");
			datainputone.addFloatItem();
			toDoList.push_back(datainputone);
			undomemory.push_back(function.converttoundoclass(undomemory, toDoList));

			temp = undomemory[1].returnmemory();
			result = temp.size();

			Assert::AreEqual(2, result);
		}

		TEST_METHOD(testReturnMemory){
			vector<undo> undomemory;
			vector<task> toDoList, temp;
			undo function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);
			undomemory.push_back(function.converttoundoclass(undomemory, toDoList));

			temp = undomemory[0].returnmemory();
			Assert::AreEqual(1, (int)temp.size());
		}

		TEST_METHOD(testReturnNum){
			vector<undo> undomemory;
			vector<task> toDoList;
			int temp;
			undo function;

			task datainputzero("meeting");
			datainputzero.addFloatItem();
			toDoList.push_back(datainputzero);
			undomemory.push_back(function.converttoundoclass(undomemory, toDoList));

			temp = undomemory[0].returnnum();
			Assert::AreEqual(0, temp);
		}
	};
}

			