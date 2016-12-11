#pragma once
#ifndef STREET_H_
#define STREET_H_
#include "Resident.h"
#include "Car.h"
#include <string>
#include <queue>

class Street
{
private:
	friend class Simulation;
	int capacity;
	int length;
	std::string destination;
	std::priority_queue<Car> inwardQueue;
	std::priority_queue<Car> outwardQueue;
	Street intersectingStreets [2];

	Street(int length, int capacity, std::string destination)
	{
		this->length = length;
		this->capacity = capacity;
		this->destination = destination;
	}

	void addIntersectingStreets(Street street1, Street street2)
	{
		intersectingStreets
	}
public:

};


#endif