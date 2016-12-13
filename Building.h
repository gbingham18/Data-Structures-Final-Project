#pragma once
#ifndef BUILDING_H_
#define BUILDING_H_
#include "Car.h"
#include "Street.h"
#include "Random.h"
#include "Resident.h"
#include <queue>
#include <string>

class Building
{
	friend class Street;
private:
	std::priority_queue<Car> visitors;
	Street connectedStreets[2];	
public:

	Building(Street &s1, Street &s2)
	{
		connectedStreets[0] = s1;
		connectedStreets[1] = s2;
	}

	void update(int clock)
	{
		while (visitors.top().projectedArrivalTime <= clock)
		{
			Street streetToTake = connectedStreets[sim_rand.next_int(1)];
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
};
#endif _BUILDING_H_