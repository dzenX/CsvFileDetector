/*
* file: Candidate.h
* Candidate class declaration
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#pragma once
#include "ObjAnalyzed.h"
class Candidate :
	public ObjAnalyzed
{
private:
	double confidence;
public:
	Candidate() : ObjAnalyzed() { };
	Candidate(int _frame_no, string _obj_class, BoundBox _box, double _confidence) :
		ObjAnalyzed(_frame_no, _obj_class, _box), confidence(_confidence) { };
	double getConfidence() { return confidence; }
	void print();
	~Candidate() = default;
};

