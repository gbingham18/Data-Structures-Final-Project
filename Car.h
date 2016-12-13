//#pragma once
#ifndef CAR_H_
#define CAR_H_
#include "Resident.h"
#include "Random.h"
#include <string>
#include <memory>

extern Random sim_rand;

class Car
{
private:
	int drivingSpeed;
	int currentRouteEntryTime;
	int currentPlaceEntryTime;
	Resident driver;
	int projectedArrivalTime;
	std::string destination;
public:
	/*
	Constructor for the car object
	*/
	Car(int clock, Resident driver, std::string destination)
	{
		currentRouteEntryTime = clock;
		currentPlaceEntryTime = clock;
		this->driver = driver;
		this->destination = destination;
		drivingSpeed = 25 + sim_rand.next_int(10);
	};

	Car()
	{
		currentPlaceEntryTime = 0;
		currentRouteEntryTime = 0;
		projectedArrivalTime = 0;
		destination = "no";

	}

	/*
	Overrides the greater than operator using the comparison of when the Cars are supposed to exit their current queue
	*/
	bool operator<(const Car &other) const
	{
		if ( projectedArrivalTime > other.projectedArrivalTime)
			return true;
		else if (projectedArrivalTime == other.projectedArrivalTime && currentPlaceEntryTime > other.currentPlaceEntryTime)
			return true;
		else
			return false;
	}

	int getProjArrTime() const
	{
		return this->projectedArrivalTime;
	}

	int getCurrPlaceEntryTime() const
	{
		return this->currentPlaceEntryTime;
	}

	int getCurrRouteEntryTime() const
	{
		return this->currentRouteEntryTime;
	}
	
	int getDrivingSpeed() const
	{
		return this->drivingSpeed;
	}

	std::string getDest() const
	{
		return this->destination;
	}

	void setCurrPlaceEntryTime(int value)
	{
		this->currentPlaceEntryTime = value;
	}

	void setProjArrTime(int value)
	{
		this->projectedArrivalTime = value;
	}

	void setCurrRouteEntryTime(int value)
	{
		currentRouteEntryTime = value;
	}

	void reportDTTime(int clock)
	{
		driver.addDowntownTime(clock - this->currentRouteEntryTime);
	}

	void reportDestination()
	{
		driver.addDestination(destination);
	}

	Resident getDriver()
	{
		return driver;
	}

	//DONT'T FORGET
	//TODO: Figure out if this is necessary
	/*~Car()
	{
		delete[] driver;
	};*/
};
#endif