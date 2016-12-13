#include "Street.h"
#include "Building.h"

int main() {


	Street a(5, 50, "school");
	Street b(5, 50, "bank");

	Building c(a, b);

}