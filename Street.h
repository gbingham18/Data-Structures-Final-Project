#pragma once
#ifndef STREET_H_
#define STREET_H_
#include "Resident.h"
#include "Car.h"
#include "Intersection.h"
#include <string>
#include <queue>

class Street
{
private:
	friend class Simulation;
	friend class Building;
public:
	int capacity;
	int length;
	//std::string destination;
	std::priority_queue<Car> inwardQueue;
	std::priority_queue<Car> outwardQueue;
	//Street *intersectingStreet1;
	//Street *intersectingStreet2;

	/*
	Adds the given intersection to the street object
	To be called when all streets are created in simulation
	*/
	//void addIntersectingStreets(Street *s1, Street *s2)
	//{
	//	intersectingStreet1 = s1;
	//	intersectingStreet2 = s2;
	//}

	void updateInner(int clock)
	{
		while (inwardQueue.top().projectedArrivalTime <= clock)
		{
			if (inwardQueue.top().destination == this->destination)
			{
				//TODO: push into the building
			}
			else // coming to the intersection
			{
				Street nextStreet = intersection.streetToTake(inwardQueue.top().destination);
				if (nextStreet.inwardQueue.size < nextStreet.capacity) // street car needs to take has room
				{
					Car c = inwardQueue.top();
					c.currentPlaceEntryTime = clock;
					c.projectedArrivalTime = clock + (nextStreet.length / (1.0 * inwardQueue.top().drivingSpeed) * 60);
					nextStreet.inwardQueue.push(c);
					inwardQueue.pop();
				}
				else // street car needs to take does not have room
					break;
			}
		}
	}

	void updateOuter(int clock)
	{
		while (outwardQueue.top().projectedArrivalTime <= clock)
		{
			if (destination == "exit") // Leaving town
			{
				outwardQueue.top().driver->addDowntownTime(clock - outwardQueue.top().currentRouteEntryTime);
				outwardQueue.pop();
			}
			else // getting on the street to leave town
			{
				Street nextStreet = intersection.streetToTake("exit");
				if (nextStreet.outwardQueue.size < nextStreet.capacity)
				{
					Car c = outwardQueue.top();
					c.currentPlaceEntryTime = clock;
					c.projectedArrivalTime = clock + (nextStreet.length / (1.0 * outwardQueue.top().drivingSpeed) * 60);
					nextStreet.outwardQueue.push(c);
					outwardQueue.pop();
				}
				else
					break;
			}
		}
	}

	Street()
	{
		capacity = 0;
		length = 0;

	}

	Street(int length, int capacity, std::string destination)
	{
		this->length = length;
		this->capacity = capacity;
		this->destination = destination;
	}
};


#endif