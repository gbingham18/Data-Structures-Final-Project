//#pragma once
#ifndef BUILDING_H_
#define BUILDING_H_
#include "Car.h"
#include "DestinationStreet.h"
#include "Random.h"
#include "Resident.h"
#include <queue>
#include <string>

class Building
{
	friend class Street;
private:
	std::priority_queue<Car> visitors;
	DestinationStreet *connectedStreets[2];
	int minTimeSpent;
	int timeSpentVariation;
public:

	Building()
	{

	}

	Building(DestinationStreet &s1, DestinationStreet &s2, int minTimeSpent, int maxTimeSpent)
	{
		connectedStreets[0] = &s1;
		connectedStreets[1] = &s2;
		this->minTimeSpent = minTimeSpent;
		this->timeSpentVariation = maxTimeSpent - minTimeSpent;
	}

	void update(int clock)
	{
		while (visitors.top().projectedArrivalTime <= clock)
		{
			DestinationStreet streetToTake = *connectedStreets[sim_rand.next_int(1)];
			if (streetToTake.outwardQueue.size < streetToTake.capacity)
			{
				Car c = visitors.top();
				c.driver->addDestination(visitors.top().destination);
				c.destination = std::string("exit");
				c.projectedArrivalTime = clock + (streetToTake.length / (1.0 * visitors.top().drivingSpeed) * 60);
				streetToTake.outwardQueue.push(c);
				visitors.pop();
			}
			else
				break;
		}
	}

	void addVisitor(Car c)
	{
		visitors.push(c);
	}

	int getMinTimeSpent()
	{
		return minTimeSpent;
	}

	int getTimeSpentVariation()
	{
		return timeSpentVariation;
	}
};
#endif _BUILDING_H_