// #pragma once

#ifndef DESTINATIONSTREET_H_
#define DESTINATIONSTREET_H_
#include "Street.h"
#include "Car.h"
#include "ExitStreet.h"
#include <string>


class DestinationStreet : public Street
{
private:
	std::string destination;
	ExitStreet *es;
	Building dest;
public:
	DestinationStreet()
	{
		destination = "yee";
	}

	void updateInner(int clock)
	{
		while (inwardQueue.top().getProjArrTime() <= clock) // Car has reached the end of the street
		{
			Car c = inwardQueue.top();
			c.setCurrPlaceEntryTime(clock);
			c.setProjArrTime(/*TODO*/);
			dest.addVisitor(c);
			inwardQueue.pop();
		}
	}

	void updateOuter(int clock)
	{
		while (outwardQueue.top().getProjArrTime() <= clock)
		{
			if (es->outwardQueue.size < es->capacity)
			{
				Car c = outwardQueue.top();
				c. = clock;
				c.projectedArrivalTime = clock + (nextStreet.length / (1.0 * outwardQueue.top().drivingSpeed) * 60);
				nextStreet.outwardQueue.push(c);
				outwardQueue.pop();
			}
			else
				break;
		}
	}
};



#endif
