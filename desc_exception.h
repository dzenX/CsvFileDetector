/*
* file: desc_exception.h
* declaration & implementation of class of exception with string message
* written: 01/10/2017
* last modified: 03/10/2017
* by N. Skilkov
*/

#pragma once
//#include "vcruntime_exception.h"
#include <string>


//this class was created coz gcc compiler doesn't support exception constructor with string value
class descriptive_exception : public std::exception {
public:
	descriptive_exception(std::string const &message) : msg_(message) { }
	virtual char const *what() const noexcept { return msg_.c_str(); }

private:
	std::string msg_;
};

