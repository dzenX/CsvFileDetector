/*
* file: Candidate.cpp
* Candidate class implementation
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#include "Candidate.h"

//prints to console data of candidate class
void Candidate::print() {
	std::cout << std::to_string(getFrameNo()) << ", " << getObjClass() << ", " << std::to_string(confidence) << ", ";
	box.print();
	std::cout << "\n";
}
