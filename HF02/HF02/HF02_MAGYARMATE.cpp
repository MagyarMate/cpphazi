//Magyar Máté - Q8C1NV


//myCreature.h
#ifndef __MY_CREATURE_H__
#define __MY_CREATURE_H__


//Absztrakt õs élõlény osztály
class myCreature
{
public:
	myCreature();
	myCreature(int);
	~myCreature();

	void setAge(int age = 0) {
		this->age = age;
	}

	int getAge() {
		return age;
	}

	virtual void printOut() = 0; // Ettõl lesz "absztrakt" -> nem példányosítható

private:
	int age;
};

myCreature::myCreature()
{
}

myCreature::myCreature(int age)
{
	this->age = age;
}

myCreature::~myCreature()
{
}

#endif


//myAnimals.h
#ifndef __MY_ANIMALS__
#define __MY_ANIMALS__

//Includes iostream for cout, string for string, myCreature for polymorphism
#include <iostream>
#include <string>
//#include "myCreature.h"

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


//myHerbs.h
#ifndef __MY_HERBS__
#define __MY_HERBS__

#include <iostream>
//#include "myCreature.h"

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
	cout << "Tipus: Noveny" << endl << "Eletkorom: " << this->getAge() << endl << "Van-e viragom: " << (this->Flower ? "van" : "nincs") << endl << "Hanyszor kell megontozni egy heten: " << water << endl << endl;
}

#endif



#include <iostream>
#include <typeinfo>
#include <string>
//#include "myAnimals.h"
//#include "myHerbs.h"


int main(int args, char* argv) {

	//Teszt
	myCreature* myArray[4];

	myArray[0] = new myHerb(5, true, 4);
	myArray[1] = new myAnimal(4, "oroszlan", 14);
	myArray[2] = new myHerb(2, true, 9);
	myArray[3] = new myHerb(8, false);

	int i;
	int flowers = 0;
	float avgAge = 0;
	for (i = 0;i < 4;i++) {
		myArray[i]->printOut();
		if (!string(typeid(*myArray[i]).name()).compare("class myHerb")) { //Kb. ugyanaz, mintha irtam volna egy gettype metodust
			if((dynamic_cast<myHerb*>(myArray[i]))->isFlower()) flowers++; //Lehetne egyszerubben, de logikailag az, hogy van-e virag, nem tartozik az ososztalyba
		}
		avgAge += myArray[i]->getAge();
	}
	avgAge /= (float)i;

	cout << "Az atlagos eletkor: " << avgAge << endl << "A viragok szama:" << flowers << endl;


	return 0;
}
