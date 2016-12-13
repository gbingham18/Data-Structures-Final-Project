#pragma once
#ifndef EXITSTREET_H_
#define EXITSTEET_H_
#include "Street.h"
#include "Car.h"
#include <string>

class ExitStreet : public Street
{
private:

public:
	
	ExitStreet() {}

	ExitStreet(int length, int capacity) : Street(length, capacity){}

	void updateInner(int clock) {}

	void updateOuter(int clock){}
};




#endif