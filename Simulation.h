#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <iostream>
#include <fstream>
#include <string>
#include "Random.h"
#include "Street.h"
#include "Building.h"
#include "Resident.h"
#include "Car.h"
#include "Intersection.h"

Random sim_rand;

class Simulation
{
private:
	int total_time;
	int clock;
	Resident residents[2000]; //Use shared pointers

	int read_int(const std::string &prompt, int low, int high)
	{
		if (low >= high) // invalid range
			throw std::invalid_argument("invalid range specified");

		std::cin.exceptions(std::ios_base::failbit);
		int num = 0;
		while (true) {
			try {
				while (true) {
					std::cout << prompt;
					std::cin >> num;
					if (num >= low && num <= high) { // within the specified range
						std::cout << std::endl;
						return num;
					}
				}
			}
			catch (std::ios_base::failure) {
				std::cout << "Bad numeric string -- try again\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<int>::max(), '\n');
			}
		}
	}

public:

	Simulation()
	{

	}

	void runSimulation()
	{

	}

};











#endif
