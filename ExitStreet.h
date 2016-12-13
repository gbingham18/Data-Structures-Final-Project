//#pragma once
#ifndef EXITSTREET_H_
#define EXITSTEET_H_
#include "Street.h"
#include "Car.h"
#include <string>

class ExitStreet : public Street
{
private:

public: 
	void updateInner(int clock) {}

	void updateOuter(int clock)
	{
		while (outwardQueue.top().getProjArrTime() <= clock)
		{
			outwardQueue.top().driver->addDowntownTime(clock - outwardQueue.top().getCurrRouteEntryTime());
			//TODO: Add the resident to the map again
			outwardQueue.pop();
		}
	}
};




#endif