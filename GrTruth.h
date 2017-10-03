/*
* file: GrTruth.h
* GrTruth class declaration
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#pragma once
#include "ObjAnalyzed.h"
class GrTruth :
	public ObjAnalyzed
{
public:
	GrTruth() : ObjAnalyzed() { };
	GrTruth(int _frame_no, string _obj_class, BoundBox _box):
		ObjAnalyzed(_frame_no, _obj_class, _box) { };
	void print();
	bool operator< (GrTruth*);
	bool operator> (GrTruth*);
	long int getArea();
	~GrTruth() = default;
};

