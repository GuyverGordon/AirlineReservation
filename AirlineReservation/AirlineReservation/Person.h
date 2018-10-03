#pragma once
#include <string>

using namespace std;

class Person
{
private:
	string firstName;
	string lastName;

public:
	//Constructors
	Person();

	Person(string, string);

	//Deconstructor
	~Person();

	//Accessor Functions
	string getFirstName();
	string getLastName();

	//Mutator Functions
	void setName(string, string);

	//Other Functions
	string getName();

	//Overloaded operator
	const Person operator = (const Person &);
	bool operator < (const Person &);
	bool operator > (const Person &);
	bool operator == (const Person &);
};
