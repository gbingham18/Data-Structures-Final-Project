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
		while (es->inwardQueue.top().getProjArrTime() <= clock) // while the first car in the ExitStreet queue is ready to leave
		{
			Car c = es->inwardQueue.top();
			if (c.getDest == destination) // Check if that car is coming to this street
			{
				c.setCurrPlaceEntryTime(clock);
				c.setProjArrTime( clock + (this->length / (1.0 * c.getDrivingSpeed) * 60));
				this->inwardQueue.push(c);
				es->inwardQueue.pop();
			}
			else
				break; // If not, leave the while loop
		}
	}

	void updateOuter(int clock)
	{
		while (outwardQueue.top().getProjArrTime() <= clock) // While the first car in thsi queue is ready to leave
		{
			if (es->outwardQueue.size < es->capacity) // If theres room in the exit queue
			{
				Car c = outwardQueue.top();
				c.setCurrPlaceEntryTime(clock);
				c.setProjArrTime(clock + (es->length / (1.0 * c.getDrivingSpeed) * 60));
				es->outwardQueue.push(c);
				outwardQueue.pop();
			}
			else
				break; // If no room, leave the while loop
		}
	}
};



#endif
