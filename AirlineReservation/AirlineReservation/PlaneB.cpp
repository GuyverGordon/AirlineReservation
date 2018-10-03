#include "PlaneB.h"

PlaneB::PlaneB(std::string flightNum, std::string departLoc, std::string arrivalLoc,
	std::string departTime, std::string arriveTime, int pnts) :
	Airplane(flightNum, departLoc, arrivalLoc, departTime, arriveTime, pnts)
{
	type = 'B';
	createSeats();
}

PlaneB::~PlaneB()
{
}

void PlaneB::displayAvailableSeats()
{
	for (int i = 1; i <= 5; i++) {
		std::cout << "--------------------------\n";
		std::cout << "|  " << i << "A  | X |  " << i << "B  |  " << i << "C  |\n";
		std::cout << "|      | X |      |      |\n";
		std::cout << "|  " << checkAvailability(std::to_string(i) + "A") << "  | X |  " << checkAvailability(std::to_string(i) + "B") << "  |  " <<
			checkAvailability(std::to_string(i) + "C") << "  |\n";
		std::cout << "--------------------------\n";
	}

	std::cout << " ** = available\n";
}

void PlaneB::createSeats()
{
	for (int i = 1; i <= 5; i++) {
		for (int j = 65; j <= 67; j++) {
			std::string tempID = std::to_string(i) + (char)j;
			seatID.insert(tempID);
		}
	}
}

std::string PlaneB::checkAvailability(std::string id)
{
	std::map<std::string, Person>::iterator itMap = seat.find(id);

	return (itMap == seat.end()) ? "**" : "  ";
}
