/*
* file: BoundBox.h
* BoundBox class declaration
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#pragma once
#include <iostream>
#include <string>
//file of declaration of Bounding Box
class BoundBox
{
private:
	int left, top, width, height;
	long int area;
public:
	BoundBox() { left, top, width, height = -1; area = -1; };
	BoundBox(const BoundBox& _box);
	BoundBox(int _left, int _top, int _width, int _height) 
		:left(_left), top(_top), width(_width), height(_height) { area = width * height; }
	long int getArea() { return area; }
	std::string getCoords();
	//looks for intersection of bounding boxes
	double ifBelongs(const BoundBox& belongs);
	void print();
	~BoundBox() = default;
};

