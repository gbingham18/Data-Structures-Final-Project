//#pragma once
#ifndef INTERSECTION_H_
#define INTERSECTION_H_
#include "Street.h"
#include <string>


class Intersection
{
private:
	Street exitStreet;
	Street schoolStreet;
	Street bankStreet;
public:

	Intersection()
	{

	}

	Intersection(Street &eStreet, Street &sStreet, Street &bStreet)
	{
		exitStreet = eStreet;
		schoolStreet = sStreet;
		bankStreet = bStreet;
	}

	Street streetToTake(std::string destination)
	{
		if (destination == "exit")
			return exitStreet;
		if (destination == "school")
			return schoolStreet;
		return bankStreet;
	}
};


#endif
