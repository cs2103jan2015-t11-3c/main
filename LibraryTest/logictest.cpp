#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>


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
			storage store;

			for(int i = 0; i < 10; i++){
				task datainput("deleteTest");
				datainput.addItemtypeone();
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
			datainput.addItemtypeone();
			toDoList.push_back(datainput);
			}

			function.clearAll(toDoList);
			size = toDoList.size();
			Assert::AreEqual (actualsize, size);
		}
	};
}