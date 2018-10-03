#include "Person.h"


//Constructors
Person::Person()
{
	firstName = "FirstName";
	lastName = "LastName";
}

Person::Person(string first, string last)
{
	setName(first, last);
}

//Deconstructor
Person::~Person()
{
}

//Accessor Functions
string Person::getFirstName()
{
	return firstName;
}

string Person::getLastName()
{
	return lastName;
}

//Mutator Functions
void Person::setName(string first, string last)
{
	firstName = first;
	lastName = last;
}

//Other Functions
string Person::getName()
{
	return firstName + " " + lastName;
}

//Overloaded operator
const Person Person::operator=(const Person &person)
{
	firstName = person.firstName;
	lastName = person.lastName;
	return *this;
}

bool Person::operator<(const Person &other)
{
	bool status;

	if (lastName < other.lastName)
		status = true;
	else if (lastName == other.lastName && firstName < other.firstName)
		status = true;
	else
		status = false;

	return status;
}

bool Person::operator>(const Person &other)
{
	bool status;

	if (lastName > other.lastName)
		status = true;
	else if (lastName == other.lastName && firstName > other.firstName)
		status = true;
	else
		status = false;

	return status;
}

bool Person::operator==(const Person &other)
{
	bool status;

	if (lastName == other.lastName && firstName == other.firstName)
		status = true;
	else
		status = false;

	return status;
}

