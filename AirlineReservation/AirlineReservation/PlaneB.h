#pragma once
#include <iostream>
#include <set>
#include <string>
#include "Airplane.h"
class PlaneB :
	public Airplane
{
public:
	PlaneB(std::string, std::string, std::string, std::string, std::string, int);
	virtual ~PlaneB();

	void displayAvailableSeats();
	std::string checkAvailability(std::string);

private:
	void createSeats();
};