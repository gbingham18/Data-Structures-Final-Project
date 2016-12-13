#ifndef SIMULATION_H_
#define SIMULATION_H_
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <memory>
#include "Random.h"
#include "Street.h"
#include "Building.h"
#include "Resident.h"
#include "Car.h"

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
	std::map<std::string, Resident> residents;
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

	/*
	Sends a car into downtown via one of the two exit streets
	*/
	void sendCar(ExitStreet dest)
	{
		if (dest.inwardQueue.size() < dest.capacity && !residents.empty())
		{
			dest.inwardQueue.push(Car(clock, residents.begin()->second, destinations[sim_rand.next_int(1)]));
			residents.erase(residents.begin());
		}
	}


	/*
	Checks for cars ready to lave downtown and removes them from their current queue if so
	*/
	void recieveCars(ExitStreet sender)
	{
		while (sender.outwardQueue.top().getProjArrTime() <= clock)
		{
			Car c = sender.outwardQueue.top();
			c.reportDTTime(clock);
			residents.insert(std::make_pair(c.getDriver().getName(), c.getDriver()));
			sender.outwardQueue.pop();
		}
	}

	/*
	Called at the end of the simulation to put back the residents that were still in the queus representing being downtown
	*/
	void putBackResidents(std::vector<Resident> people)
	{
		for (int i = 0; i < people.size(); i++)
		{
			residents.insert(std::make_pair(people[i].getName(), people[i]));
		}
	}

public:

	/*
	Reads residents from file and puts them all in a map
	*/
	void getResidents()
	{
		std::string firstnames[2000];
		std::string lastnames[2000];
		std::ifstream input;
		input.open("residents_of_273ville.txt");
		if (input.fail()) {
			std::cout << "File does not exist, exit program. \n";
		}
		while (!input.eof())
		{
			int i = 0;
			input >> firstnames[i];
			i++;
		}
		input.close();

		input.open("surnames_of_273ville.txt");
		if (input.fail()) {
			std::cout << "File does not exist, exit program. \n";
		}
		while (!input.eof())
		{
			int i = 0;
			input >> lastnames[i / 2];
			i++;
		}
		input.close();

		for (int i = 0; i < 2000; i++)
		{
			std::string name = firstnames[i] + " " + lastnames[i];
			residents.insert(std::make_pair(name, Resident(name)));
		}
	}

	/*
	Prompts the user for data about the flow of traffic into downtown and the street capacities. then creates all the
	street and building objects to this spec
	*/
	void enter_data()
	{
		std::cout << "Welcome to the 273ville traffic simulation. \n";

		visitorRate = read_int("Enter a value between 1 - 60 for the visitor arrival rate (visitors/ hour): ", 1, 60);
		int roadCapacity[6];
		std::string names[6] = { "Jackson", " Travis", "Amber", "Tulip", "James", "Birch" };
		for (int i = 0; i < 6; i++)
		{
			roadCapacity[i] = read_int("Enter a value between 5 - 50 for the road capacity of " + names[i] +": ", 5, 50);
		}
		eStreets[0] = ExitStreet(3, roadCapacity[0]);
		eStreets[1] = ExitStreet(3, roadCapacity[1]);
		dStreets[0] = DestinationStreet(6, roadCapacity[2], "bank", &eStreets[0]);
		dStreets[1] = DestinationStreet(3, roadCapacity[3], "school", &eStreets[0]);
		dStreets[2] = DestinationStreet(4, roadCapacity[4], "bank", &eStreets[1]);
		dStreets[3] = DestinationStreet(5, roadCapacity[5], "school", &eStreets[1]);
		buildings[0] = Building(dStreets[0], dStreets[2], 10, 20);
		buildings[1] = Building(dStreets[1], dStreets[3], 5, 10);
	}

	/*
	runs the simulation for time equivalent to a week 
	*/
	void run_simulation()
	{
		total_time = 7 * 24 * 60;
		for (clock = 0; clock < total_time; clock++)
		{
			for (int i = 0; i < 2; i++)
				this->recieveCars(eStreets[i]);
			for (int i = 0; i < 4; i++)
				dStreets[i].updateOuter(clock);
			for (int i = 0; i < 2; i++)
				buildings[i].update(clock);
			for (int i = 0; i < 4; i++)
				dStreets[i].updateInner(clock);
			//TODO: Push cars in
			double minsBetweenEnters = 1.0 * 60 / visitorRate;
			std::vector<int> times;
			for (int i = 0; i < visitorRate; i++)
			{
				times.push_back(floor(i* minsBetweenEnters));
			}
			if (std::find(times.begin(), times.end(), (clock % 60)) != times.end())
			{
				ExitStreet s = eStreets[sim_rand.next_int(1)];
				sendCar(s);
			}
		}
		std::vector<Resident> toBePutBack;
		for (int i = 0; i < 4; i++)
		{
			toBePutBack = buildings[i /2].getAllResidents();
			putBackResidents(toBePutBack);
			toBePutBack = eStreets[i / 2].getAllResidents();
			putBackResidents(toBePutBack);
			toBePutBack = dStreets[i].getAllResidents();
			putBackResidents(toBePutBack);
		}

		std::cout << "The simulation of one full week is complete!" << std::endl;
	}


	/*
	Displays the stats of the simulation, inlcluding the average travel time
	*/
	void show_stats()
	{
		int totalDowntownTime = 0;
		int totalNumDestinations = 0;
		for (auto const& iter : residents)
		{
			totalDowntownTime += iter.second.getTimeSpentDowntown();
			totalNumDestinations += iter.second.getDestinations().size();
		}
		double avgTravelTime = totalDowntownTime / totalNumDestinations;
		std::cout << "There were " << totalNumDestinations << " trips made into town this week.\n";
		std::cout << "Each trip was an average of " << avgTravelTime << " minutes, for a grand total of "
			<< totalDowntownTime << " minutes spent downtown!" << std::endl;
	}

	/*
	If the user desires, displays all the names of the people who went downtown, and can give details about a specific person
	*/
	void displayResidents()
	{
		int key = -1;
		do
		{
			std::string prompt = "Enter a number between 0 and 2 \n[0]: List all visitors to town\n[1]: Display record of specific resident\n[2]: Exit program\n\n";
			int response = read_int(prompt, 0, 2);
			if (response == 0)
			{
				for (auto const& iter : residents)
				{
					if (!iter.second.getDestinations().empty())
						std::cout << iter.first;
				}
			}
			if (response == 1)
			{
				std::cout << "Enter the name of the resident you would like to see information for:\n";
				std::string name;
				std::cin >> name;
				try
				{
					Resident r = residents.at(name);
					std::cout << r.getName() << " visited " << r.getDestinations().size() << " locations:\n";
					for (auto const& iter : r.getDestinations())
						std::cout << iter << std::endl;
				}
				catch (std::out_of_range &e)
				{
					std::cerr << "Exception: The name entered does not exist! \n";
				}
			}
		} while (key != 2);
	}

	/*
	constructor
	*/
	Simulation()
	{

	}
};











#endif
