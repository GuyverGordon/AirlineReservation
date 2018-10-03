/*
Name: Jonathan Oesch
Date: November 9, 2017
Program: Airline Reservation -- FINAL
Description: A program to manage booking airline flights.

Modifications:
*/
#define _WIN32_WINNT 0x0500

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <Windows.h>
#include <vector>
#include "Person.h"
#include "Airplane.h"
#include "PlaneA.h"
#include "PlaneB.h"

//To track days of the week
enum Day { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

//Global Constants
const int NUM_OF_CITIES = 7;

//Function Prototypes
void testAirplane();		//tests Airplane, PlaneA, PlaneB

void createCities(std::map<std::string, std::string> &);		//creates city with city codes

void createSchedule(std::shared_ptr<vector<std::shared_ptr<Airplane>>>);		//creates flight schedule

bool sortByDeparture(std::shared_ptr<Airplane>, std::shared_ptr<Airplane>);		//sorts flight schedule by departure city

void loadData(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> &);		//Loads previous data from file

int showMainMenu();			//Displays main menu and returns choice

void clearCin();		//Clears cin buffer

void bookReservation(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> &,
	std::map<std::string, std::string>, std::shared_ptr<vector<std::shared_ptr<Airplane>>>);		//Reserves a person to a flight

int showDecisions(Day, std::string, std::map<std::string, std::string>,
	std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>);			//Displays options when flight booked

std::string showCities(std::map<std::string, std::string>);		//Displays available cities and returns string choice

Day getDay();		//Displays list of days returns choice Day

void checkAvailableFlights(Day, std::string, std::map<Day,
	std::shared_ptr<vector<std::shared_ptr<Airplane>>>>, std::shared_ptr<std::vector<std::shared_ptr<Airplane>>>);	//Stores list of available flights

std::string pickFlight(std::shared_ptr<std::vector<std::shared_ptr<Airplane>>>);		//Displays available flights and returns integer flight number of chosen flight

std::string pickSeat(Day, std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>, std::string, int);			//Displays available seats

bool isUnavailable(Day, std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>, int, int);		//checks to see if any seat in the row is available

bool confirmInformation(std::string, std::string, Day, std::string, int, std::string, std::map<Day,
	std::shared_ptr<vector<std::shared_ptr<Airplane>>>>);												//Confirms user input

std::string convertDay(Day);		//Converts enum Day to string

int findFlight(std::shared_ptr<vector<std::shared_ptr<Airplane>>>, std::string);		//Returns index for flight schedule

void showBoardingPass(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>, int,
	std::string, std::map<std::string, std::string>, Day);												//Displays passenger's boarding pass

void cancelReservation(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> &,
	std::map<std::string, std::string>, std::shared_ptr<vector<std::shared_ptr<Airplane>>>);		//Cancels a reservation to a flight

std::string getFlightNumber(std::shared_ptr<vector<std::shared_ptr<Airplane>>>, std::map<std::string, std::string>);		//Prompt user for flight number

void showFlightSchedule(std::shared_ptr<vector<std::shared_ptr<Airplane>>>, std::map<std::string, std::string>);		//Displays list of flights

bool isNotFlightNum(std::string, std::shared_ptr<vector<std::shared_ptr<Airplane>>>);			//compares user response to list of flight numbers

std::string getName(std::string);		//Prompts user for appropriate name

bool foundReservation(Day, std::string, std::string, std::string,
	std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>);			//searches for passenger on flight

bool promptToTryAgain();		//allow user to try again or quit

void viewInformation(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>,
	std::shared_ptr<vector<std::shared_ptr<Airplane>>>, std::map<std::string, std::string>);	//View requested information

int showViewMenu();			//Displays view menu

void viewCities(std::map<std::string, std::string>);		//Displays available cities

void viewPassengerBoardingPass(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>,
	std::shared_ptr<vector<std::shared_ptr<Airplane>>>, std::map<std::string, std::string>);		//Displays selected passenger boarding pass

void showBoardingPass(Day, std::string, std::string, std::string,
	std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>);			////Displays passenger's boarding pass

void viewPassengerList(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>, std::map<std::string, std::string>);			//Displays list of passengers by name or by seat

int showPassListMenu();			//Displays menu for viewing passenger list

void saveData(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>>);		//Saves current data to file

void showEndMessage();			//Displays exit program message

int main() {
	//code to extend console window -- code gotten from http://www.cplusplus.com/forum/beginner/1481/
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, 800, 700, TRUE);

	//---------------------------------------------------------------------------------------------------
	//testAirplane();
	//---------------------------------------------------------------------------------------------------

	//Create cities;
	std::map<std::string, std::string> city;
	createCities(city);

	//Create Flight Schedule;
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightSchedule = std::make_shared<vector<std::shared_ptr<Airplane>>>();
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightScheduleSun = std::make_shared<vector<std::shared_ptr<Airplane>>>();
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightScheduleMon = std::make_shared<vector<std::shared_ptr<Airplane>>>();
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightScheduleTue = std::make_shared<vector<std::shared_ptr<Airplane>>>();
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightScheduleWed = std::make_shared<vector<std::shared_ptr<Airplane>>>();
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightScheduleThu = std::make_shared<vector<std::shared_ptr<Airplane>>>();
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightScheduleFri = std::make_shared<vector<std::shared_ptr<Airplane>>>();
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightScheduleSat = std::make_shared<vector<std::shared_ptr<Airplane>>>();
		
	createSchedule(flightSchedule);
	createSchedule(flightScheduleSun);
	createSchedule(flightScheduleMon);
	createSchedule(flightScheduleTue);
	createSchedule(flightScheduleWed);
	createSchedule(flightScheduleThu);
	createSchedule(flightScheduleFri);
	createSchedule(flightScheduleSat);
	
	std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> weekFlightSchedule;

	int temp = SUNDAY;
	weekFlightSchedule[(Day)temp++] = flightScheduleSun;
	weekFlightSchedule[(Day)temp++] = flightScheduleMon;
	weekFlightSchedule[(Day)temp++] = flightScheduleTue;
	weekFlightSchedule[(Day)temp++] = flightScheduleWed;
	weekFlightSchedule[(Day)temp++] = flightScheduleThu;
	weekFlightSchedule[(Day)temp++] = flightScheduleFri;
	weekFlightSchedule[(Day)temp++] = flightScheduleSat;

	//Load previous data
	loadData(weekFlightSchedule);

	//Main Menu
	int menu;

	do {
		system("cls");
		menu = showMainMenu();

		switch (menu) {
		case 1:					//Book a Reservation
			bookReservation(weekFlightSchedule, city, flightSchedule);
			break;
		case 2:					//Cancel a Reservation
			cancelReservation(weekFlightSchedule, city, flightSchedule);
			break;
		case 3:					//View Flight / Passenger Information
			viewInformation(weekFlightSchedule, flightSchedule, city);
		}
	} while (menu != 4);		//Exit

								//Save current Data

	system("cls");
	saveData(weekFlightSchedule);

	showEndMessage();

	system("pause");
	return 0;
}																				//end main

//This function tests the Airplane class as well as the PlaneA and PlaneB class (derived from Airplane)
void testAirplane() {
	std::cout << "Testing Airplane Classes ... \n";
	std::cout << "Creating PlaneA object ...\n";
	std::shared_ptr<Airplane> tstPlaneA = std::make_shared<PlaneA>("101", "Here", "There", "3:40pm", "5:30pm", 500);
	std::cout << "Test Plane A:\n";
	std::cout << "Flight number: " << tstPlaneA->getFlightNumber() << std::endl;
	std::cout << "Arrival Location: " << tstPlaneA->getArrivalLocation() << std::endl;
	std::cout << "Destination Location: " << tstPlaneA->getDepartureLocation() << std::endl;
	std::cout << "Arrival Time: " << tstPlaneA->getArrivalTime() << std::endl;
	std::cout << "Destination Time: " << tstPlaneA->getDepartureTime() << std::endl;
	std::cout << "Points for flight: " << tstPlaneA->getPoints() << std::endl;
	std::cout << "Is the plane booked? " << tstPlaneA->isBooked() << std::endl << std::endl;

	std::cout << "Populating PlaneA ... \n";
	tstPlaneA->addPassenger("1A", "Test", "Dummy");
	tstPlaneA->addPassenger("2B", "Mario", "Mario");
	tstPlaneA->addPassenger("3C", "Samus", "Aaron");
	tstPlaneA->getPassengerListBySeat();
	std::cout << std::endl;
	tstPlaneA->getPassengerListByName();
	tstPlaneA->displayAvailableSeats();
	std::cout << std::endl;

	std::cout << "Removing Passenger (Mario Mario)... \n";
	tstPlaneA->removePassenger(Person("Mario", "Mario"));
	tstPlaneA->getPassengerListByName();
	std::cout << std::endl << std::endl;

	std::cout << "Creating PlaneB object ... \n";
	std::shared_ptr<Airplane> tstPlaneB = std::make_shared<PlaneB>("102", "ATL", "ALB", "5:40pm", "8:40pm", 1000);
	std::cout << "Flight number: " << tstPlaneB->getFlightNumber() << std::endl;
	std::cout << "Arrival Location: " << tstPlaneB->getArrivalLocation() << std::endl;
	std::cout << "Destination Location: " << tstPlaneB->getDepartureLocation() << std::endl;
	std::cout << "Arrival Time: " << tstPlaneB->getArrivalTime() << std::endl;
	std::cout << "Destination Time: " << tstPlaneB->getDepartureTime() << std::endl;
	std::cout << "Points for flight: " << tstPlaneB->getPoints() << std::endl;
	std::cout << "Is the plane booked? " << tstPlaneB->isBooked() << std::endl << std::endl;

	std::cout << "Populating PlaneB ... \n";
	tstPlaneB->addPassenger("1A", "Test", "Dummy");
	tstPlaneB->addPassenger("2B", "Mario", "Mario");
	tstPlaneB->addPassenger("3C", "Samus", "Aaron");
	tstPlaneB->getPassengerListBySeat();
	std::cout << std::endl;
	tstPlaneB->getPassengerListByName();
	tstPlaneB->displayAvailableSeats();
	std::cout << std::endl;
}																				//end testAirplane

//This function creates and matches the city codes with the corresponding cities
void createCities(std::map<std::string, std::string> &map) {
	map["ATL"] = "Atlanta";
	map["ORL"] = "Orlando";
	map["DFW"] = "Dallas/Fort Worth";
	map["NYC"] = "New York City";
	map["HAW"] = "Hawaii";
	map["CHI"] = "Chicago";
	map["LAX"] = "Los Angeles";
}																				//end createCities

//This function creates the flight schedule that occurs everyday
void createSchedule(std::shared_ptr<vector<std::shared_ptr<Airplane>>> schedule) {
	schedule->push_back(std::make_shared<PlaneA>("602", "HAW", "LAX", "04:15", "15:15", 1000));
	schedule->push_back(std::make_shared<PlaneB>("1201", "NYC", "DFW", "09:00", "11:30", 500));
	schedule->push_back(std::make_shared<PlaneB>("1202", "NYC", "DFW", "12:00", "14:30", 500));
	schedule->push_back(std::make_shared<PlaneB>("1203", "NYC", "DFW", "16:00", "18:30", 500));
	schedule->push_back(std::make_shared<PlaneA>("902", "NYC", "CHI", "10:12", "12:12", 500));
	schedule->push_back(std::make_shared<PlaneA>("903", "NYC", "CHI", "18:24", "20:24", 500));
	schedule->push_back(std::make_shared<PlaneB>("202", "NYC", "ORL", "11:30", "01:00", 700));
	schedule->push_back(std::make_shared<PlaneA>("204", "NYC", "ORL", "17:30", "19:00", 700));
	schedule->push_back(std::make_shared<PlaneB>("1204", "DFW", "NYC", "09:00", "11:30", 500));
	schedule->push_back(std::make_shared<PlaneB>("1205", "DFW", "NYC", "12:00", "14:30", 500));
	schedule->push_back(std::make_shared<PlaneB>("1206", "DFW", "NYC", "16:00", "18:30", 700));
	schedule->push_back(std::make_shared<PlaneB>("302", "DFW", "ORL", "12:30", "15:30", 700));
	schedule->push_back(std::make_shared<PlaneA>("304", "DFW", "ORL", "14:30", "17:30", 700));
	schedule->push_back(std::make_shared<PlaneB>("306", "DFW", "ORL", "19:30", "22:30", 700));
	schedule->push_back(std::make_shared<PlaneB>("904", "CHI", "NYC", "09:00", "11:00", 500));
	schedule->push_back(std::make_shared<PlaneA>("905", "CHI", "NYC", "19:00", "21:00", 500));
	schedule->push_back(std::make_shared<PlaneB>("601", "ORL", "HAW", "14:30", "01:30", 2000));
	schedule->push_back(std::make_shared<PlaneB>("201", "ORL", "NYC", "08:30", "10:30", 700));
	schedule->push_back(std::make_shared<PlaneA>("203", "ORL", "NYC", "14:30", "16:00", 700));
	schedule->push_back(std::make_shared<PlaneA>("205", "ORL", "NYC", "19:30", "21:20", 700));
	schedule->push_back(std::make_shared<PlaneB>("301", "ORL", "DFW", "09:30", "12:00", 700));
	schedule->push_back(std::make_shared<PlaneB>("303", "ORL", "DFW", "13:30", "16:00", 700));
	schedule->push_back(std::make_shared<PlaneB>("305", "ORL", "DFW", "17:30", "20:00", 700));
	schedule->push_back(std::make_shared<PlaneA>("101", "ORL", "ATL", "09:00", "09:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("103", "ORL", "ATL", "11:00", "11:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("105", "ORL", "ATL", "13:00", "13:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("107", "ORL", "ATL", "15:00", "15:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("109", "ORL", "ATL", "17:00", "17:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("100", "ATL", "ORL", "08:00", "08:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("102", "ATL", "ORL", "10:00", "10:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("104", "ATL", "ORL", "12:00", "12:31", 500));
	schedule->push_back(std::make_shared<PlaneA>("106", "ATL", "ORL", "14:00", "14:32", 500));
	schedule->push_back(std::make_shared<PlaneA>("108", "ATL", "ORL", "16:00", "16:30", 500));
	sort(schedule->begin(), schedule->end(), sortByDeparture);
}																				//end createSchedule

//This functions allows the flight schedule to be sorted by departure city for easier viewing
bool sortByDeparture(std::shared_ptr<Airplane> lPlane, std::shared_ptr<Airplane> rPlane) {
	return lPlane->getDepartureLocation() < rPlane->getDepartureLocation();
}																				//end sortByDeparture

//This function fills data into flight schedule map from file
void loadData(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> &schedule) {
	std::cout << "Loading data ...\n";
	std::ifstream dataFile("scheduleData.dat");

	//If file not found, allow user to continue with the program (to possible refill reservations by hand if applicable) or terminate the program
	if (dataFile.fail()) {
		char choice;
		std::cout << "Error -- File not found ...";
		std::cout << "Do you want to continue (enter y for yes or n for no)? ";
		std::cin >> choice;
		clearCin();
		
		while (tolower(choice) != 'y' && tolower(choice) != 'n') {
			std::cout << "Please enter y for yes or n for no\n";
			std::cout << "Do you want to continue (enter y for yes or n for no)? ";
			std::cin >> choice;
			clearCin();
		}

		if (tolower(choice) == 'y')
			return;
		else
			exit(1);
	}

	int day, vectorIndex;
	std::string stringCheck, seat, first, last;

	dataFile >> day;

	//If the file does not contain anything, allow the user to continue with the program or terminate the program (so it does not save and rewrite the file at normal exit)
	if (dataFile.eof()) {
		char choice;
		std::cout << "Error -- File seems to be empty ...";
		std::cout << "Do you want to continue (enter y for yes or n for no)? ";
		std::cin >> choice;
		clearCin();

		while (tolower(choice) != 'y' && tolower(choice) != 'n') {
			std::cout << "Please enter y for yes or n for no\n";
			std::cout << "Do you want to continue (enter y for yes or n for no)? ";
			std::cin >> choice;
			clearCin();
		}

		if (tolower(choice) == 'y')
			return;
		else
			exit(1);
	}

	int count = 0;
	while (count < 33) {
		dataFile >> vectorIndex;
		do {
			dataFile >> stringCheck;
			if (stringCheck != "done") {
				seat = stringCheck;
				dataFile >> first >> last;
				schedule.at(Day(day)).get()->at(vectorIndex)->addPassenger(seat, first, last);
			}
		} while (stringCheck != "done");
		count++;
	}

	while (dataFile >> day) {
		count = 0;

		while (count < 33) {
			dataFile >> vectorIndex;
			do {
				dataFile >> stringCheck;
				if (stringCheck != "done") {
					seat = stringCheck;
					dataFile >> first >> last;
					schedule.at(Day(day)).get()->at(vectorIndex)->addPassenger(seat, first, last);
				}
			} while (stringCheck != "done");
			count++;
		}
	}
	
	std::cout << "Data successfully loaded ... \n";
}																				//end loadData

//This function displays the main menu.  It returns an integer choice.
int showMainMenu() {
	int choice;

	std::cout << "  GTC AIRLINES EXPRESS\n";
	std::cout << "---------------------------------------\n";
	std::cout << " 1. Book A Reservation\n";
	std::cout << " 2. Cancel A Reservation\n";
	std::cout << " 3. View Flight/Passenger Information\n";
	std::cout << " 4. Exit\n";
	std::cout << "---------------------------------------\n";
	std::cout << "Please make a selection: ";
	std::cin >> choice;

	while (cin.fail() || choice < 1 || choice > 4) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- Invalid value\n";
		std::cout << "Please make a selection (1 - 4): ";
		std::cin >> choice;
	}

	return choice;
}																				//end showMainMenu

//This function clears out the cin buffer
void clearCin() {
	cin.clear();                              //clear errors/bad flags on cin

	cin.ignore(cin.rdbuf()->in_avail(), '\n');		//precise amount of ignoring
	cin.rdbuf()->in_avail();								//returns the exact number of characters in the cin buffer.
}																				//end clearCin()

//This function enters a flight reservation.!!!
void bookReservation(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> &schedule,
	std::map<std::string, std::string> city, std::shared_ptr<vector<std::shared_ptr<Airplane>>> mstrSchedule) {
	std::string fName, lName, departingCity, arrivingCity, seat, flightNum;
	Day day;
	int flightIndex;
	bool confirm = false, needDifferentDay = false, needDifferentCity = false;

	do {
		system("cls");

		std::cout << "Book Reservation\n";
		std::cout << "----------------\n";

		//Get Name
		std::cout << "Please enter your first name: ";
		std::cin >> fName;
		std::cout << "Please enter your last name: ";
		std::cin >> lName;

		do {
			system("cls");

			if (needDifferentCity)
				needDifferentCity = false;

			//Get departing and arriving city
			arrivingCity = showCities(city);
			if (arrivingCity == "QUIT")
				return;
			
			do {
				system("cls");

				if (needDifferentDay)
					needDifferentDay = false;

				//Get day of the week
				day = getDay();

				//Gather available flights for that day
				std::shared_ptr<std::vector<std::shared_ptr<Airplane>>> subset = std::make_shared<std::vector<std::shared_ptr<Airplane>>>();
				checkAvailableFlights(day, arrivingCity, schedule, subset);																		

				if (!subset->empty()) {
					system("cls");

					//Get flight number of desired flight
					flightNum = pickFlight(subset);
					flightIndex = findFlight(mstrSchedule, flightNum);

					system("cls");

					//Select desired seat on flight
					seat = pickSeat(day, schedule, flightNum, flightIndex);

					system("cls");

					//Confirm input
					confirm = confirmInformation(fName, lName, day, flightNum, flightIndex, seat, schedule);
				}
				else {
					system("cls");
					int decision = showDecisions(day, arrivingCity, city, schedule);

					switch (decision) {
					case 1:			//Select different day
						needDifferentDay = true;
						break;
					case 2:			//Select different city
						needDifferentCity = true;
						break;
					case 3:			//Cancel
						return;
					}
				}
			} while (needDifferentDay);
		} while (needDifferentCity);

		if (confirm) {
			//Book passenger
			schedule.at(day).get()->at(flightIndex)->addPassenger(seat, fName, lName);
			std::cout << fName << " " << lName << " has successfully booked this flight!\n";
			system("pause");
		}
	} while (!confirm);

	//Display passenger's boarding pass
	system("cls");
	showBoardingPass(schedule, flightIndex, seat, city, day);
}																				//end bookReservation

//This function displays a menu to allow the user to decide to pick a different city, day or cancel booking a reservation
int showDecisions(Day day, std::string arrivingCity, std::map<std::string, std::string> city, std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule) {
	int choice;

	std::cout << "Unfortunately, every flight for that day for that location has been booked.\n";
	std::cout << "However, there are a few options for you:\n";
	std::cout << "1. Select A Different Day\n";
	std::cout << "2. Select A Different Destination\n";
	std::cout << "3. Cancel Booking\n";
	std::cout << "Please make a selection: ";
	std::cin >> choice;

	while (cin.fail() || choice < 1 || choice > 3) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- Invalid value\n";
		std::cout << "Please make a selection (1 - 3): ";
		std::cin >> choice;
	}

	return choice;
}																				//end showDecisions

//This function displays all the available cities.  Returns string choice.
std::string showCities(std::map<std::string, std::string> city) {
	std::map<std::string, std::string>::iterator itCity = city.begin();
	int choice;

	std::cout << "Where do you want to go?\n";

	for (int i = 1; i <= NUM_OF_CITIES; i++) {
		std::cout << i << ". " << itCity->first << " -- " << itCity->second << std::endl;
		itCity++;
	}
	std::cout << NUM_OF_CITIES + 1 << ". Return to Main Menu\n";
	std::cout << "Please make a selection: ";
	cin >> choice;

	while (cin.fail() || choice < 1 || choice > NUM_OF_CITIES + 1) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- invalid value\n";
		std::cout << "Please make a selection (1 - " << NUM_OF_CITIES << "): ";
		cin >> choice;
	}

	if (choice == NUM_OF_CITIES + 1)
		return "QUIT\n";

	//reset iterator
	itCity = city.begin();

	//cycle through to user's choice
	if (choice > 1) {
		for (int i = 1; i < choice; i++) {
			itCity++;
		}
	}

	return itCity->first;
}																				//end showCities
//This function displays the days of the week.  Returns choice Day.
Day getDay() {
	int choice;
	std::cout << "Please pick the day of the flight:\n";
	std::cout << SUNDAY + 1 << ". Sunday\n";
	std::cout << MONDAY + 1 << ". Monday\n";
	std::cout << TUESDAY + 1 << ". Tuesday\n";
	std::cout << WEDNESDAY + 1 << ". Wednesday\n";
	std::cout << THURSDAY + 1 << ". Thursday\n";
	std::cout << FRIDAY + 1 << ". Friday\n";
	std::cout << SATURDAY + 1 << ". Saturday\n";
	std::cout << "Please make a selection: ";
	cin >> choice;

	while (cin.fail() || choice < SUNDAY + 1 || choice > SATURDAY + 1) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- invalid value\n";
		std::cout << "Please make a selection ( " << SUNDAY + 1 << " - " << SATURDAY + 1 << ": ";
		cin >> choice;
	}

	return (Day)(choice - 1);
}																				//end getDay

//This function searches through the flight schedule and writes the matches to a subset
void checkAvailableFlights(Day day, std::string arrive, std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule,
	std::shared_ptr<std::vector<std::shared_ptr<Airplane>>> subsetSchedule) {
	std::cout << "Checking available flights ... \n";

	//Get iterator for vector of flights
	/*vector<std::shared_ptr<Airplane>>::iterator itFlights;

	for (itFlights = schedule.at(day)->begin(); itFlights != schedule.at(day)->end(); itFlights++) {
		if (arrive == itFlights->get()->getArrivalLocation() && !itFlights->get()->isBooked()) {
			subsetSchedule->push_back(*itFlights);
		}
	}*/

	for (int i = 0; i < schedule.at(day).get()->size(); i++) {
		if (arrive == schedule.at(day).get()->at(i)->getArrivalLocation() && !schedule.at(day).get()->at(i)->isBooked()) {
			subsetSchedule->push_back(schedule.at(day).get()->at(i));
		}
	}

}																				//end checkAvailableFlights

//This function displays a list of available flights and returns the flight number of the chosen flight
std::string pickFlight(std::shared_ptr<std::vector<std::shared_ptr<Airplane>>> subsetSchedule) {
	std::vector<std::shared_ptr<Airplane>>::iterator itList;
	int count = 1, choice;

	std::cout << "Please pick a flight\n";

	for (itList = subsetSchedule->begin(); itList != subsetSchedule->end(); itList++) {
		std::cout << count << ". Flight #" << itList->get()->getFlightNumber() << ", Leaving from: " << itList->get()->getDepartureLocation() <<
			", Arriving at: " << itList->get()->getArrivalLocation() << std::endl;
		std::cout << "  Leaving at " << itList->get()->getDepartureTime() << ", Arriving at " << itList->get()->getArrivalTime() << std::endl << std::endl;
		count++;
	}

	std::cout << "Please make a selection: ";
	std::cin >> choice;

	while (cin.fail() || choice < 1 || choice >= count) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- invalid value\n";
		std::cout << "Please make a selection (1 - " << count - 1 << ": ";
		std::cin >> choice;
	}

	//reset iterator
	itList = subsetSchedule->begin();

	if (choice > 1) {
		for (int i = 1; i < choice; i++)
			itList++;
	}

	return itList->get()->getFlightNumber();
}																				//end pickFlight

//This function displays all the available seats and returns choice string seat
std::string pickSeat(Day day, std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule, std::string flightNum, int index) {
	int row;
	char seat;
	bool seatTaken = false;

	do {
		std::cout << "Pick a seat\n";
		schedule.at(day)->at(index)->displayAvailableSeats();
		std::cout << "Please enter the row number you would like to sit: ";
		cin >> row;

		while (cin.fail() || row < 1 || row > 5 || isUnavailable(day, schedule, row, index)) {
			if (cin.fail())
				clearCin();

			if (isUnavailable(day, schedule, row, index)) {
				std::cout << "Error -- row unavailable.  Please select another row.\n";
				std::cout << "Please enter the row number you would like to sit: ";
			}
			else {
				std::cout << "Error -- Invalid value\n";
				std::cout << "Please enter the row number (1 - 5) you would like to sit: ";
			}

			cin >> row;
		}

		std::cout << "Please enter the seat letter you want to sit: ";
		std::cin >> seat;
		clearCin();

		if (schedule.at(day)->at(index)->getType() == 'A') {
			while (toupper(seat) != 'A' && toupper(seat) != 'B' && toupper(seat) != 'C' && toupper(seat) != 'D') {
					
				std::cout << "Error -- invalid seat.  Seats are labeled A, B, C or D.\n";
				std::cout << "Please enter the seat letter you want to sit: ";
				std::cin >> seat;
				clearCin();
			}
		}
		else {
			while (toupper(seat) != 'A' && toupper(seat) != 'B' && toupper(seat) != 'C') {
				
				std::cout << "Error -- invalid seat.  Seats are labeled A, B, or C.\n";
				std::cout << "Please enter the seat letter you want to sit: ";
				std::cin >> seat;
				clearCin();
			}
		}

		if (schedule.at(day)->at(index)->checkAvailability(to_string(row)+ string(1, (toupper(seat)))) != "**") {
			seatTaken = true;
			system("cls");
			std::cout << "That is seat is already taken, please select a different seat\n\n";
		}

	} while (seatTaken);
	std::string seatCol = string(1, toupper(seat));

	return to_string(row) + seatCol;
}																				//end pickSeat

//This function searches through the row of a plane.  Returns false if any seat returns "**" meaning available.  Else returns true.
bool isUnavailable(Day day, std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule, int row, int index) {
	char seatId = 'A';

	if (schedule.at(day)->at(index)->getType() == 'A') {
		while (seatId < 'E') {
			if (schedule.at(day)->at(index)->checkAvailability(to_string(row) + to_string(toupper(seatId))) == "**")
				return false;

			seatId++;
		}
	}
	else {
		while (seatId < 'D') {
			if (schedule.at(day)->at(index)->checkAvailability(to_string(row) + to_string(toupper(seatId))) == "**")
				return false;

			seatId++;
		}
	}

	return true;
}																				//end isUnavailable

//This function displays all of the user's input and prompts user for confirmation. Returns true if 'y' or false if 'n'.
bool confirmInformation(std::string firstName, std::string lastName, Day day, std::string flightNum, int index, std::string seat,
	std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule) {

	char answer;

	std::cout << "Name: " << firstName << " " << lastName << std::endl;
	std::cout << "Day of Flight: " << convertDay(day) << std::endl;
	std::cout << "Flight Number: " << flightNum << std::endl;
	std::cout << "From: " << schedule.at(day)->at(index)->getDepartureLocation() << " " << schedule.at(day)->at(index)->getDepartureTime() <<
		" To: " << schedule.at(day)->at(index)->getArrivalLocation() << " " << schedule.at(day)->at(index)->getArrivalTime() << std::endl;
	std::cout << "Seat: " << seat << std::endl;
	std::cout << "Is this information correct (enter y for yes or n for no)? ";
	std::cin >> answer;
	clearCin();
	std::cout << std::endl;

	while (tolower(answer) != 'y' && tolower(answer) != 'n') {
		std::cout << "Error -- Invalid selection\n";
		std::cout << "Is this information correct (enter y for yes or n for no)? ";
		std::cin >> answer;
		clearCin();
		std::cout << std::endl;
	}

	return tolower(answer) == 'y';
}																				//end confirmInformation

//This function converts the enum Day to a string and returns it
std::string convertDay(Day day) {
	switch (day) {
	case SUNDAY:
		return "Sunday";
	case MONDAY:
		return "Monday";
	case TUESDAY:
		return "Tuesday";
	case WEDNESDAY:
		return "Wednesday";
	case THURSDAY:
		return "Thursday";
	case FRIDAY:
		return "Friday";
	case SATURDAY:
		return "Saturday";
	}
}																				//end convertDay

//This function searches for and returns the index number that matches the flight with the flight number.
int findFlight(std::shared_ptr<vector<std::shared_ptr<Airplane>>> subsetSchedule, std::string flightNum) {
	for (int i = 0; i < subsetSchedule.get()->size(); i++) {
		if (flightNum == subsetSchedule.get()->at(i)->getFlightNumber())
			return i;
	}

	return -1;		//error
}																				//end findFlight

//This function displays the passenger's boarding pass.
void showBoardingPass(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule, int index, std::string seat,
	std::map<std::string, std::string> city, Day day) {
	system("cls");

	std::cout << " ---------------\n";
	std::cout << "| BOARDING PASS |\n";
	std::cout << "|------------------------------------------------------------------------------\n";
	std::cout << "| Name: " << schedule.at(day)->at(index)->getSeat(seat).getName() << std::endl;
	std::cout << "| Day of Flight: " << convertDay(day) << std::endl;
	std::cout << "| Flight Number: " << schedule.at(day)->at(index)->getFlightNumber() << std::endl;
	std::cout << "| From: " << schedule.at(day)->at(index)->getDepartureLocation() << " " << schedule.at(day)->at(index)->getDepartureTime() <<
		" To: " << schedule.at(day)->at(index)->getArrivalLocation() << " " << schedule.at(day)->at(index)->getArrivalTime() << std::endl;
	std::cout << "| Seat: " << seat << std::endl;
	std::cout << "| Points gained: " << schedule.at(day)->at(index)->getPoints() << std::endl;
	std::cout << " ------------------------------------------------------------------------------\n";
	system("pause");
}																				//end showBoardingPass

//This function cancels a reservation.
void cancelReservation(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> &schedule,
	std::map<std::string, std::string> city, std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightSched) {
	bool again = false;

	do {
		system("cls");

		std::cout << "Cancel Reservation\n";
		std::cout << "------------------\n";
		std::string firstName = getName("first");
		std::string lastName = getName("last");
		Day day = getDay();
		std::string flightNum = getFlightNumber(flightSched, city);

		if (foundReservation(day, flightNum, firstName, lastName, schedule)) {
			schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->removePassenger(Person(firstName, lastName));

			if (again)
				again = false;

			std::cout << "Reservation has been canceled ...\n";
			system("pause");
		}
		else {
			std::cout << "Sorry, the passenger was not found on that flight during that day... you may try again if you wish\n";
			again = promptToTryAgain();
		}
	} while (again);
}																				//end cancelReservation

//This function prompts the user to enter the flight number
std::string getFlightNumber(std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightSchedule, std::map<std::string, std::string> city) {
	int number;
	showFlightSchedule(flightSchedule, city);
	std::cout << "Please enter the flight number of your flight: ";
	cin >> number;

	while (cin.fail() || isNotFlightNum(to_string(number), flightSchedule)) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- that was not one of the listed flight numbers.\n";
		std::cout << "Please enter the flight number of your flight: ";
		cin >> number;
	}

	return to_string(number);
}																				//end getFlightNumber

//This function displays a list of flights for reference.
void showFlightSchedule(std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightSched, std::map<std::string, std::string> city) {
	system("cls");
	
	std::cout << "  List of flights\n";
	std::cout << "-------------------\n";

	for (int i = 0; i < flightSched->size(); i++) {
		std::cout << flightSched->at(i)->getFlightNumber() << " -- From: " << flightSched->at(i)->getDepartureLocation() <<
			" " << flightSched->at(i)->getDepartureTime() << " To: " << flightSched->at(i)->getArrivalLocation() << " " <<
			flightSched->at(i)->getArrivalTime() << std::endl;

		if (i < flightSched->size() - 1 && (flightSched->at(i)->getDepartureLocation() != flightSched->at(i + 1)->getDepartureLocation() ||
			flightSched->at(i)->getArrivalLocation() != flightSched->at(i + 1)->getArrivalLocation())) {
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	system("pause");
	std::cout << std::endl;
}																				//end showFlightSchedule

//This function compares parameter string with list of flight numbers; returns true if string does NOT match
bool isNotFlightNum(std::string num, std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightSched) {
	for (int i = 0; i < flightSched->size(); i++) {
		if (num == flightSched->at(i)->getFlightNumber())
			return false;
	}

	return true;
}																				//end isNotFlightNum

//This function prompts user to enter either his/her first or last name
std::string getName(std::string position) {
	std::string answer;

	std::cout << "Please enter your " << position << " name: ";
	std::cin >> answer;

	return answer;
}																				//end getName

//This function searches for a specific passenger on a specific flight; returns true if found.
bool foundReservation(Day day, std::string flightNum, std::string firstName,
	std::string lastName, std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule) {
	return (schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->findPassenger(Person(firstName, lastName)));
}																				//end foundReservation

//This function asks the user if they want to try to enter data again; returns true if 'y'
bool promptToTryAgain() {
	char answer;
	std::cout << "Would you like to try again (enter y for yes or n for no)? ";
	std::cin >> answer;
	clearCin();

	while (cin.fail() || tolower(answer) != 'y' && tolower(answer) != 'n') {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- Invalid selection\n";
		std::cout << "Would you like to try again (enter y for yes or n for no)? ";
		std::cin >> answer;
		clearCin();
	}

	return tolower(answer) == 'y';
}																				//end promptToTryAgain

//This function displays a viewing subMenu.
void viewInformation(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule,
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightSchedule, std::map<std::string, std::string> city) {
	int menu;

	do {
		system("cls");
		menu = showViewMenu();

		switch (menu) {
		case 1:			//View Flight Schedule
			showFlightSchedule(flightSchedule, city);
			break;
		case 2:			//Display Available Cities
			viewCities(city);
			break;
		case 3:			//View Passenger Boarding Pass
			viewPassengerBoardingPass(schedule, flightSchedule, city);
			break;
		case 4:			//View Passenger List
			viewPassengerList(schedule, city);
		}
	} while (menu != 5);
}																				//end viewInformation

//This function displays the view menu and returns integer choice.
int showViewMenu() {
	int choice;

	std::cout << "  View Flight / Passenger Information\n";
	std::cout << "---------------------------------------\n";
	std::cout << "1. View Flight Schedule\n";
	std::cout << "2. Display Available Cities\n";
	std::cout << "3. View Passenger Boarding Pass\n";
	std::cout << "4. View Passenger List\n";
	std::cout << "5. Back to Main Menu\n";
	std::cout << "Please make a selection: ";
	std::cin >> choice;

	while (cin.fail() || choice < 1 || choice > 5) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- Invalid value\n";
		std::cout << "Please make a selection (1 - 5): ";
		std::cin >> choice;
	}

	return choice;
}																				//end showViewMenu

//This function displays the list of cities available.
void viewCities(std::map<std::string, std::string> city) {
	std::map<std::string, std::string>::iterator itCity;
	system("cls");

	std::cout << "  List of Available cities\n";
	std::cout << "----------------------------\n";
	for (itCity = city.begin(); itCity != city.end(); itCity++) {
		std::cout << itCity->first << " -- " << itCity->second << std::endl;
	}

	system("pause");
}																				//end viewCities

//This function asks user for identification and if passenger is found, displays boarding pass
void viewPassengerBoardingPass(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule,
	std::shared_ptr<vector<std::shared_ptr<Airplane>>> flightSchedule, std::map<std::string, std::string> city) {
	bool again = false;

	do {
		system("cls");

		std::cout << "View Passenger Boarding Pass\n";
		std::cout << "----------------------------\n";
		std::string firstName = getName("first");
		std::string lastName = getName("last");
		Day day = getDay();
		std::string flightNum = getFlightNumber(flightSchedule, city);

		if (foundReservation(day, flightNum, firstName, lastName, schedule)) {
			showBoardingPass(day, flightNum, firstName, lastName, schedule);

			if (again)
				again = false;
		}
		else {
			std::cout << "Sorry, the passenger was not found on that flight during that day... you may try again if you wish\n";
			again = promptToTryAgain();
		}
	} while (again);
}																				//end viewPassengerBoardingPass

//This function displays the passenger's boarding pass.
void showBoardingPass(Day day, std::string flightNum, std::string firstName, std::string lastName,
	std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule) {
	system("cls");

	std::cout << " ---------------\n";
	std::cout << "| BOARDING PASS |\n";
	std::cout << "|------------------------------------------------------------------------------\n";
	std::cout << "| Name: " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getSeat(schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getSeatID(firstName, lastName)).getName() <<
		std::endl;
	std::cout << "| Day of Flight: " << convertDay(day) << std::endl;
	std::cout << "| Flight Number: " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getFlightNumber() << std::endl;
	std::cout << "| From: " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getDepartureLocation() << " " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getDepartureTime() <<
		" To: " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getArrivalLocation() << " " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getArrivalTime() << std::endl;
	std::cout << "| Seat: " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getSeatID(firstName, lastName) <<
		std::endl;
	std::cout << "| Points gained: " << schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getPoints() << std::endl;
	std::cout << " ------------------------------------------------------------------------------\n";
	system("pause");
}																				//end showBoardingPass

//This function displays a flight's passenger list by name or by seat
void viewPassengerList(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule, std::map<std::string, std::string> city) {
	system("cls");

	std::cout << "View Passenger List\n";
	std::cout << "-------------------\n";

	Day day = getDay();
	std::string flightNum = getFlightNumber(schedule.at(day), city);

	system("cls");
	int passList = showPassListMenu();

	system("cls");
	if (passList == 1)		//by Name
		schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getPassengerListByName();
	else {			//by Seat
		schedule.at(day).get()->at(findFlight(schedule.at(day), flightNum))->getPassengerListBySeat();
	}

	system("pause");
}																				//end viewPassengerList

//This function displays menu to decide if user wants to view passenger list by name or by seat.
int showPassListMenu() {
	int choice;

	std::cout << "Show Passenger List\n";
	std::cout << "1. By Name\n";
	std::cout << "2. By Seat\n";
	std::cout << "Please make a selection: ";
	std::cin >> choice;

	while (cin.fail() || choice < 1 || choice > 2) {
		if (cin.fail())
			clearCin();

		std::cout << "Error -- Invalid value\n";
		std::cout << "Please make a selection (1 - 2): ";
		std::cin >> choice;
	}

	return choice;
}																				//end showPassListMenu

//This function saves current data to file before closing.
void saveData(std::map<Day, std::shared_ptr<vector<std::shared_ptr<Airplane>>>> schedule) {
	std::ofstream dataFile ("scheduleData.dat");
	std::cout << "Saving reservations ...\n";

	for (int i = SUNDAY; i <= SATURDAY; i++) {
		dataFile << i << std::endl;

		for (int j = 0; j < schedule.at(Day(i)).get()->size(); j++) {
			dataFile << j << std::endl;
			schedule.at(Day(i)).get()->at(j)->writePassengerList(dataFile);
		}
	}
}																				//end saveData

//This function displays the final message before closing.
void showEndMessage() {
	std::cout << "Thank you for using this program\n";
}																				//end showEndMessage