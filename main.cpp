/*
* file: main.cpp
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#include "DataBase.h"

int main() {
	DataBase db;
	try {
		db.loadGrTruth("od_gt.csv");
		db.loadCandidates("od_cnd.csv");
		db.detect("res.csv");
		db.viewNumOfDetected();
	}
	catch (descriptive_exception ex) {
		std::cout << ex.what() << "\n";
	}
	//db.viewGrTruth();
	//db.viewCandidates();
	system("pause");
	return 0;
}