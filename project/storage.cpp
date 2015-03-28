#include "storage.h"
#include "logic.h"
#include <vector>
#include <sstream>
#include <fstream> 

void storage::saveToSaveFile(const string fileName, const string savetext) {
	fstream textFile;
	
	textFile.open(fileName.c_str(), fstream::out);
	textFile << savetext;
	textFile.close();
}

