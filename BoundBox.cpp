/*
* file: BoundBox.cpp
* BoundBox class implementation
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#include "BoundBox.h"

//copy constructor
BoundBox::BoundBox(const BoundBox & _box) {
	if (this == &_box)
		return;
	left = _box.left;
	top = _box.top;
	width = _box.width;
	height = _box.height;
	area = _box.area;
}

//return coords in string format to write them in file
std::string BoundBox::getCoords()
{
	std::string coords;
	coords += std::to_string(left);
	coords += ", ";
	coords += std::to_string(top);
	coords += ", ";
	coords += std::to_string(width);
	coords += ", ";
	coords += std::to_string(height);
	return coords;
}

//counts the relations of intersection and union areas
double BoundBox::ifBelongs(const BoundBox & belongs) {
	double detected = 0;
	long int a = 0;
	long int b = 0;
	if ((left > belongs.left) && (left < (belongs.left + belongs.width)))
		if ((left + width) < (belongs.left + belongs.width))
			a = width;
		else
			a = belongs.left + belongs.width - left;
	if ((belongs.left > left) && (belongs.left < (left + width)))
		if ((belongs.left + belongs.width) < (left + width))
			a = belongs.width;
		else
			a = left + width - belongs.left;
	if ((belongs.top > top) && (belongs.top < (top + height)))
		if ((belongs.top + belongs.height) < (top + height))
			b = belongs.height;
		else
			b = top + height - belongs.top;
	if ((top > belongs.top) && (top < (belongs.top + belongs.height)))
		if ((top + height) < belongs.top + belongs.height)
			b = height;
		else
			b = belongs.top + belongs.height - top;
	long int in_area = a*b;
	long int un_area = area + belongs.area - in_area;
	detected = (double)in_area / un_area;
	return detected;
}

//show Box
void BoundBox::print() {
	std::cout << std::to_string(left) << ", " << std::to_string(top) << ", " << std::to_string(width) << ", " << std::to_string(height) << "\n";
}
