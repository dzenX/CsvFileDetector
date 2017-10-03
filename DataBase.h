/*
* file: DatabBase.h
* DataBase class declaration
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#pragma once

#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "GrTruth.h"
#include "Candidate.h"

using std::vector;

//class of database of ground truth and candidates objects 
class DataBase
{
private:
	std::multimap<int, GrTruth*> GrTruthList; //map of ground truth objects
	std::multimap<int, Candidate*> CandidateList; //map of candidates
	std::multimap<int, Candidate*> Result; //map of detected candidates
	long int detected_gr_tr;
	long int detected_cnd;
public:
	DataBase() {
		detected_gr_tr = 0;
		detected_cnd = 0;
	};
	void loadGrTruth(const char* file); //load ground truth from file
	void loadCandidates(const char* file); //load candidates from file
	void viewGrTruth(); //show ground truth
	void viewCandidates(); //show candidates
	void detect(const char*); //detect candidates
	Candidate* chooseByConfidence(vector<Candidate*>); //choosing candidates of same ground object by confidence
	void viewNumOfDetected(); //views number of detected candidates and ground truth objects
	~DataBase() = default;
};

