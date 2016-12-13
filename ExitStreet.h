//#pragma once
#ifndef EXITSTREET_H_
#define EXITSTEET_H_
#include "Street.h"
#include "Car.h"
#include <string>

class ExitStreet : public Street
{
private:
	//DestinationStreet *bankStreet;
	//DestinationStreet *schoolStreet;


public: 
	void updateInner(int clock)
	{
		
	}

	void updateOuter(int clock)
	{
		while (outwardQueue.top().projectedArrivalTime <= clock)
		{
			outwardQueue.top().driver->addDowntownTime(clock - outwardQueue.top().getCurrRouteEntryTime());
			outwardQueue.pop();
		}
	}
};




#endif