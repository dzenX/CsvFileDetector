/*
* file: ObjAnalyzed.cpp
* ObjAnalyzed class declaration
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#include "ObjAnalyzed.h"

bool ObjAnalyzed::allowToCompare(const ObjAnalyzed * compared)
{
	if ((frame_no == compared->frame_no) && (obj_class == compared->obj_class))
		return true;
	return false;
}

bool ObjAnalyzed::detector(ObjAnalyzed * cnd)
{
	cnd->detection_co = box.ifBelongs(cnd->box);
	if (cnd->detection_co > 0.5)
		return true;
	return false;
}

