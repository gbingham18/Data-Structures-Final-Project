#pragma once
#ifndef CAR_H_
#define CAR_H_
#include "Resident.h"
#include <string>
#include "Simulation.h"

class Car
{
private:
	friend class Street;
	int drivingSpeed;
	int currentRouteEntryTime;
	int currentPlaceEntryTime;
	Resident* driver;
	std::string destination;
	int projectedArrivalTime;
public:

	/*
	Constructor for the car object
	*/
	Car(int clock, Resident *driver, std::string destination)
	{
		currentRouteEntryTime = clock;
		currentPlaceEntryTime = clock;
		this->driver = driver;
		this->destination = destination;
		drivingSpeed = 25 + rand.next_int(10);
	};

	/*
	Overrides the greater than operator using the comparison of when the Cars are supposed to exit their current queue
	*/
	bool operator>(const Car &other) const {
		if ( projectedArrivalTime < other.projectedArrivalTime)
			return true;
		else if (projectedArrivalTime == other.projectedArrivalTime && currentPlaceEntryTime < other.currentPlaceEntryTime)
			return true;
		else
			return false;
	}

	//DONT'T FORGET
	//TODO: Figure out if this is necessary
	/*~Car()
	{
		delete[] driver;
	};*/
};
#endif