#pragma once
#ifndef EXITSTREET_H_
#define EXITSTEET_H_
#include "Street.h"
#include "DestinationStreet.h"
#include "Car.h"
#include <string>

class ExitStreet : public Street
{
private:
	DestinationStreet *bankStreet;
	DestinationStreet *schoolStreet;


	void updateInner(int clock)
	{
		Car c = inwardQueue.top();
		int x = c.getPAT();
		while (x <= clock)
		{
			DestinationStreet nextStreet;
			if (inwardQueue.top().destination == "school")
				nextStreet = *schoolStreet;
			else
				nextStreet = *bankStreet;
			if (nextStreet.inwardQueue.size() < nextStreet.capacity) // street car needs to take has room
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
};




#endif