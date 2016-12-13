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
	Street streets[6];
	Building buildings[2];

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

	void getResidents()
	{
		std::string firstnames[2000];
		std::string lastnames[2000];
		std::ifstream input;
		input.open("residents_of_273ville.txt");
		if (input.fail()){
			std::cout << "File does not exist, exit program. \n";
		}
		while (!input.eof)
		{
			input >> firstnames;
		}
		input.close;
		for (int i = 0; i < 2; i++)
		{
			input.open("surnames_of_273ville.txt");
			if (input.fail()) {
				std::cout << "File does not exist, exit program. \n";
			}
			while (!input.eof)
			{
				input >> lastnames;
			}
			input.close;
		}
	}

public:

	void enter_data()
	{
		std::cout << "Welcome to the 273ville traffic simulation. \n";

		int visitorRate = read_int("Enter a value between 1 - 60 for the visitor arrival rate (visitors/ hour).", 1, 60);
		int roadCapacity = read_int("Enter a value between 20 - 100 for the road capacity.", 20, 100);
		//TODO: Set RoadCapacity for ALL 6 roads
	}

	void run_simulation()
	{

		total_time = 7 * 24 * 60;
		for (clock = 0; clock < total_time; clock++)
		{
			for (int i = 0; i < 6; i++)
			{
				streets[i].updateOuter(clock);
				buildings[i / 3].update(clock);
				streets[i].updateInner(clock);
			}
		}
	}

	void recordVisits()
	{
		//TODO: Keep record of everyone who visits down town
		// Use get functions in Resident class
	}
	void show_stats()
	{
		//TODO: Calculate average travel time for visitors;
		// Get sum of timeSpentDowntown members from each resident
		// ??Check if resident spent any time down town 
		// If resident's timeSpentDowntown > 0, add to the sum
		// divide by number of Residents who visited downtown.
	}

	void displayResidents()
	{
		//TODO: display a menu with options to list the names of all residents that visited downtown
		// and retrieve the record of a resident by “name”.
		

		//Create map of strings to residents (shared_ptr residents).
	}
	Simulation()
	{

	}

};











#endif
