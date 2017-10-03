/*
* file: ObjAnalyzed.h
* ObjAnalyzed class declaration
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#pragma once

#include <iostream>
#include <string>
#include "BoundBox.h"
#include "desc_exception.h"

using std::string;

class ObjAnalyzed
{
protected:
	int frame_no;
	string obj_class;
	BoundBox box;
	double detection_co;
public:
	ObjAnalyzed() = default;
	ObjAnalyzed(int _frame_no, string _obj_class, BoundBox _box) :frame_no(_frame_no), obj_class(_obj_class), box(_box) {};
	int getFrameNo() { return frame_no; }
	string getObjClass() { return obj_class; }
	bool allowToCompare(const ObjAnalyzed* compared);//looking for matching frame_no and class
	bool detector(ObjAnalyzed* cnd);//looks for mathcing of ground truth and candidate objects
	void setDetectionCo(double det) { detection_co = det; };
	double getDetectionCo() { return detection_co; }
	string getCoords() { return box.getCoords(); } //get coors in string format to write in file
	~ObjAnalyzed() = default;
};

