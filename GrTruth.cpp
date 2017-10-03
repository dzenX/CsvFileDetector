/*
* file: GrTruth.cpp
* GrTruth class implementation
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#include "GrTruth.h"

//prints to console data of GrTruth class
void GrTruth::print() {
	std::cout << std::to_string(getFrameNo()) << ", "<< getObjClass() << ", ";
	box.print();
	std::cout << "\n";
}
//reload op for sort
bool GrTruth::operator<(GrTruth * compared) {
	return (box.getArea() < compared->box.getArea());
}

bool GrTruth::operator>(GrTruth * compared) {
	return (box.getArea() > compared->box.getArea());
}

//returns area of bound box
long int GrTruth::getArea() {
	return box.getArea();
}
