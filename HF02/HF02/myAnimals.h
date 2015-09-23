#ifndef __MY_ANIMALS__
#define __MY_ANIMALS__

//Includes iostream for cout, string for string, myCreature for polymorphism
#include <iostream>
#include <string>
#include "myCreature.h"

using namespace std;

class myAnimal : public myCreature
{
public:
	myAnimal(int, string, int);
	~myAnimal();

	void printOut();

	void setName(string name) { this->name = name; }
	string getName() { return this->name; }

	void setFeed(int feed) { this->feed = feed; }
	int getFeed() { return feed; }

private:

	string name;
	int feed;

};

myAnimal::myAnimal(int age = 0, string name = "", int feed = 0) : myCreature(age)
{
	this->name = name;
	this->feed = feed;
}

myAnimal::~myAnimal()
{
}

void myAnimal::printOut() {
	cout << "Tipus: Allat" << endl << "Eletkorom: " << this->getAge() << endl << "Nev: " << this->name << endl << "Hanyszor kerek enni egy heten: " << this->feed << endl << endl;
}


#endif