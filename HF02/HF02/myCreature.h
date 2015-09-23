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

	int getAge(){ 
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
