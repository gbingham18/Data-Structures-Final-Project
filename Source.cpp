#include "Street.h"
#include "Building.h"
#include "Car.h"
#include "DestinationStreet.h"
#include "ExitStreet.h"
#include "Random.h"
#include "Resident.h"
#include "Simulation.h"

int main()
{
	Simulation simer;
	simer.enter_data();
	simer.run_simulation();
	simer.show_stats();
	simer.displayResidents();

}