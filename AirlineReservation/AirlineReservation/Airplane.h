#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "Person.h"

class Airplane
{
protected:
	std::string flightNumber, arrivalLocation, departureLocation, departureTime, arrivalTime;
	int points, numberOfPassengers;
	std::set<std::string> seatID;
	std::map<std::string, Person> seat;
	char type;
public:
	Airplane();
	Airplane(std::string, std::string, std::string, std::string, std::string, int);

	virtual ~Airplane();

	//Accessor
	std::string getFlightNumber() { return flightNumber; }
	std::string getArrivalLocation() { return arrivalLocation; }
	std::string getDepartureLocation() { return departureLocation; }
	std::string getDepartureTime() { return departureTime; }
	std::string getArrivalTime() { return arrivalTime; }
	int getPoints() { return points; }
	int getNumberOfPassengers() { return numberOfPassengers; }
	std::string getSeatID(std::string, std::string);
	Person getSeat(std::string);
	char getType() { return type; }

	//Mutator
	void setFlightNumber(std::string flightNum) { flightNumber = flightNum; }
	void setArrivalLocation(std::string arrivalLoc) { arrivalLocation = arrivalLoc; }
	void setDepartureLocation(std::string departLoc) { departureLocation = departLoc; }
	void setDepartureTime(std::string departTime) { departureTime = departTime; }
	void setArrivalTime(std::string arriveTime) { arrivalTime = arriveTime; }
	void setPoints(int pts) { points = pts; }

	//Other functions
	void addPassenger(std::string, std::string, std::string);
	void removePassenger(Person);
	bool findPassenger(Person);
	void getPassengerListBySeat();
	void getPassengerListByName();
	bool isBooked();
	void writePassengerList(ofstream &);
	virtual void displayAvailableSeats() = 0;
	virtual std::string checkAvailability(std::string) = 0;
};

