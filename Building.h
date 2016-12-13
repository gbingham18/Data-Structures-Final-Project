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
		while (visitors.top().projectedArrivalTime <= clock) // Send cars that are ready to leave away
		{
			DestinationStreet streetToTake = *connectedStreets[sim_rand.next_int(1)];
			if (streetToTake.outwardQueue.size < streetToTake.capacity)
			{
				Car c = visitors.top();
				c.driver->addDestination(visitors.top().destination); // Add the destination to the residents multiset
				c.driver->addDowntownTime(clock - c.getCurrRouteEntryTime()); // Adds the time the resident has spent downtown
				c.setCurrRouteEntryTime(clock); // Resets that counter
				c.projectedArrivalTime = clock + (streetToTake.length / (1.0 * visitors.top().drivingSpeed) * 60);
				streetToTake.outwardQueue.push(c);
				visitors.pop();
			}
			else
				break;
		}

		for (int i = 0; i < 2; i++) // Bring in cars that are ready to come in
		{
			while (connectedStreets[i]->inwardQueue.top().getProjArrTime <= clock)
			{
				Car c = connectedStreets[i]->inwardQueue.top();
				c.setCurrPlaceEntryTime(clock);
				c.setProjArrTime(clock + this->minTimeSpent + sim_rand.next_int(this->timeSpentVariation));
				connectedStreets[i]->inwardQueue.pop();
				this->visitors.push(c);
			}
		}
	}
};
#endif _BUILDING_H_