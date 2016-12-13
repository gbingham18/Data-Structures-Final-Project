#ifndef RESIDENT_H_
#define RESIDENT_H_
#include <string>
#include <set>

class Resident
{
private:
	std::string name;
	int timeSpentDowntown;
	std::multiset<std::string> destinations;
public:
	/*
	Constructor for the Resident object
	*/
	Resident()
	{
		name = "Default Resident";
		timeSpentDowntown = 0;
	}

	Resident(std::string name)
	{
		this->name = name;
	}

	/*
	Adds the given destination to the multiset of places the resident has visited;
	to be called when the resident arrives at the destination downtown.
	*/
	void addDestination(std::string destination)
	{
		destinations.insert(destination);
	}

	/*
	Increments the total time the resident has spent downtown by the given amount;
	to be called both when the resident arrives at their downtown destination and
	when the resident completes a trip downtown
	*/
	void addDowntownTime(int time)
	{
		timeSpentDowntown += time;
	}

	std::multiset<std::string> getDestinations()
	{
		return destinations;
	}

	int getTimeSpentDowntown()
	{
		return timeSpentDowntown;
	}
};
#endif