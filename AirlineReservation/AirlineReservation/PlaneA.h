#pragma once
#include <iostream>
#include <set>
#include <string>
#include "Airplane.h"
class PlaneA :
	public Airplane
{
public:
	PlaneA(std::string, std::string, std::string, std::string, std::string, int);
	virtual ~PlaneA();

	void displayAvailableSeats();
	std::string checkAvailability(std::string);

private:
	void createSeats();
};

