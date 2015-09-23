#ifndef __MY_HERBS__
#define __MY_HERBS__

#include <iostream>
#include "myCreature.h"

using namespace std;

class myHerb : public myCreature
{
public:
	myHerb(int, bool, int);
	~myHerb();

	void printOut();

	void setFlower(bool Flower) { this->Flower = Flower; }
	bool isFlower() { return Flower; }

	void setWater(int water) { this->water = water; };
	int getWater() { return this->water; }

private:
	bool Flower;
	int water;
};

myHerb::myHerb(int age = 0, bool Flower = false, int water = 0) : myCreature(age)
{
	this->Flower = Flower;
	this->water = water;
}

myHerb::~myHerb()
{
}

void myHerb::printOut() {
	cout << "Tipus: Noveny" << endl << "Eletkorom: " << this->getAge() << endl << "Van-e viragom: " << (this->Flower?"van":"nincs") << endl << "Hanyszor kell megontozni egy heten: " << water << endl << endl;
}

#endif
