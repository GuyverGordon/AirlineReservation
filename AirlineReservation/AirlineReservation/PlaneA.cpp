#include "PlaneA.h"



PlaneA::PlaneA(std::string flightNum, std::string departLoc, std::string arrivalLoc,
	std::string departTime, std::string arriveTime, int pnts) :
	Airplane(flightNum, departLoc, arrivalLoc, departTime, arriveTime, pnts)
{
	type = 'A';
	createSeats();
}

PlaneA::~PlaneA()
{
}

void PlaneA::displayAvailableSeats()
{
	std::cout << "---------------------------------\n";

	for (int i = 1; i <= 5; i++) {
		std::cout << "|  " << i << "A  |  " << i << "B  | X |  " << i << "C  |  " << i << "D  |\n";
		std::cout << "|      |      | X |      |      |\n";
		std::cout << "|  " << checkAvailability(std::to_string(i) + "A") << "  |  " << checkAvailability(std::to_string(i) + "B") << "  | X |  " <<
			checkAvailability(to_string(i) + "C") << "  |  " << checkAvailability(to_string(i) + "D") << "  |\n";
		std::cout << "---------------------------------\n";
	}

	std::cout << " ** = available\n";
}

void PlaneA::createSeats()
{
	for (int i = 1; i <= 5; i++) {
		for (int j = 65; j <= 68; j++) {
			std::string tempID = std::to_string(i) + (char)j;
			seatID.insert(tempID);
		}
	}
}

std::string PlaneA::checkAvailability(std::string id)
{
	std::map<std::string, Person>::iterator itMap = seat.find(id);

	//std::cout << *it << std::endl;
	//std::cout << (itMap == seat.end()) << std::endl;
	return (itMap == seat.end()) ? "**" : "  ";
}
