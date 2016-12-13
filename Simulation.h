#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
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
	int visitorRate;
	DestinationStreet dStreets[4];
	ExitStreet eStreets[2];
	Building buildings[2];
	std::map<std::string, std::shared_ptr<Resident>> residents;
	const std::string destinations[2] = { "school", "bank" };

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
			int i = 0;
			input >> firstnames[i];
			i++;
		}
		input.close;

		input.open("surnames_of_273ville.txt");
		if (input.fail()) {
			std::cout << "File does not exist, exit program. \n";
		}
		while (!input.eof)
		{
			int i = 0;
			input >> lastnames[i /2];
			i++;
		}
		input.close;

		for (int i = 0; i < 2000; i++)
		{
			std::string name = firstnames[i] + " " + lastnames[i];
			residents.insert(std::make_pair(name, new Resident(name)));
		}
	}

public:

	void enter_data()
	{
		std::cout << "Welcome to the 273ville traffic simulation. \n";

		visitorRate = read_int("Enter a value between 1 - 60 for the visitor arrival rate (visitors/ hour).", 1, 60);
		int roadCapacity = read_int("Enter a value between 5 - 50 for the road capacity.", 5, 50);
		//TODO: Set RoadCapacity for ALL 6 roads
	}

	void run_simulation()
	{

		total_time = 7 * 24 * 60;
		for (clock = 0; clock < total_time; clock++)
		{
			for (int i = 0; i < 2; i++)
				eStreets[i].updateOuter(clock);
			for (int i = 0; i < 4; i++)
				dStreets[i].updateOuter(clock);
			for (int i = 0; i < 2; i++)
				buildings[i].update(clock);
			for (int i = 0; i < 4; i++)
				dStreets[i].updateInner(clock);
			//TODO: Push cars in
			if (true/* It is time to push a new car in           (clock % 60) % ((60 *1.0) / visitorRate) == 0*/)
			{
				ExitStreet s = eStreets[sim_rand.next_int(1)];
				if (s.inwardQueue.size() < s.capacity && !residents.empty())
				{
					s.inwardQueue.push(Car(clock, residents.begin()->second, destinations[sim_rand.next_int(1)]));
					residents.erase(residents.begin());
				}
			}
		}
	}


	void show_stats()
	{
		//TODO: Calculate average travel time for visitors;
		// Get sum of timeSpentDowntown members from each resident
		// ??Check if resident spent any time down town 
		// If resident's timeSpentDowntown > 0, add to the sum
		// divide by number of Residents who visited downtown.
		int totalDowntownTime = 0;
		int totalNumDestinations = 0;
		for (auto const& iter : residents)
		{
			totalDowntownTime += iter.second->getTimeSpentDowntown();
			totalNumDestinations += iter.second->getDestinations().size();
		}
		double avgTravelTime = totalDowntownTime / totalNumDestinations;
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

	void returnResident()

};











#endif
