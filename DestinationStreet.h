#pragma once
#ifndef DESTINATIONSTREET_H_
#define DESTINATIONSTREET_H_
#include "Street.h"
#include "ExitStreet.h"
#include "Building.h"
#include <string>


class DestinationStreet : public Street
{
private:
	std::string destination;
	ExitStreet *es;
	Building dest;
public:

};



#endif // !DESTINATIONSTREET_H_
