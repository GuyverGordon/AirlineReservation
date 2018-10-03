#include "Airplane.h"


Airplane::Airplane()
{
}

Airplane::Airplane(std::string flightNum, std::string departLoc, std::string arrivalLoc,
	std::string departTime, std::string arriveTime, int pnts)
{
	setFlightNumber(flightNum);
	setArrivalLocation(arrivalLoc);
	setDepartureLocation(departLoc);
	setDepartureTime(departTime);
	setArrivalTime(arriveTime);
	setPoints(pnts);
}


Airplane::~Airplane()
{
}

std::string Airplane::getSeatID(std::string first, std::string last)
{
	std::map<std::string, Person>::iterator it;

	for (it = seat.begin(); it != seat.end(); it++) {
		if (it->second.getFirstName() == first && it->second.getLastName() == last) {
			return it->first;
		}
	}

	return "XX";
}

Person Airplane::getSeat(std::string seatId)
{
	return seat.at(seatId);
}

void Airplane::addPassenger(std::string seatId, std::string firstName, std::string lastName)
{
	seat[seatId] = Person(firstName, lastName);
}

void Airplane::removePassenger(Person pssngr)
{
	std::map<std::string, Person>::iterator it;

	for (it = seat.begin(); it != seat.end(); it++) {
		if (it->second.getFirstName() == pssngr.getFirstName() && it->second.getLastName() == pssngr.getLastName()) {
			seat.erase(it);
			return;
		}
	}
}

bool Airplane::findPassenger(Person pssngr)
{
	std::map<std::string, Person>::iterator it;

	for (it = seat.begin(); it != seat.end(); it++) {
		if (it->second.getFirstName() == pssngr.getFirstName() && it->second.getLastName() == pssngr.getLastName()) {
			return true;
		}
	}

	return false;
}

void Airplane::getPassengerListBySeat()
{
	std::set<std::string>::iterator itSeatID;
	std::map<std::string, Person>::iterator itMap;

	for (itSeatID = seatID.begin(); itSeatID != seatID.end(); itSeatID++) {
		itMap = seat.find(*itSeatID);
		if (itMap != seat.end()) {
			std::cout << "Seat " << itMap->first << ": " << itMap->second.getName() << std::endl;
		}
	}
	
	if (isBooked()) {
		std::cout << "This flight is 100% booked!\n";
	}
}

void Airplane::getPassengerListByName()
{
	std::map<std::string, Person>::iterator itMap = seat.begin();
	vector<Person> passList;

	for (itMap = seat.begin(); itMap != seat.end(); itMap++) {
		passList.push_back(itMap->second);
	}

	sort(passList.begin(), passList.end());

	vector<Person>::iterator itPerson;
	for (itPerson = passList.begin(); itPerson != passList.end(); itPerson++) {
		cout << itPerson->getName() << std::endl;
	}
}

bool Airplane::isBooked()
{
	std::set<std::string>::iterator itSeatID;
	std::map<std::string, Person>::iterator itMap;

	for (itSeatID = seatID.begin(); itSeatID != seatID.end(); itSeatID++) {
		itMap = seat.find(*itSeatID);
		if (itMap == seat.end()) {
			return false;
		}
	}

	return true;
}

void Airplane::writePassengerList(ofstream &file)
{
	std::set<std::string>::iterator itSeatID;
	std::map<std::string, Person>::iterator itMap;

	for (itSeatID = seatID.begin(); itSeatID != seatID.end(); itSeatID++) {
		itMap = seat.find(*itSeatID);
		if (itMap != seat.end()) {
			file << itMap->first << " " << itMap->second.getName() << std::endl;
		}
	}
	//Mark the end of passenger list
	file << "done" << std::endl;
}
