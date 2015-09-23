#ifndef __MY_CREATURE_H__
#define __MY_CREATURE_H__


//Absztrakt �s �l�l�ny oszt�ly
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

	virtual void printOut() = 0; // Ett�l lesz "absztrakt" -> nem p�ld�nyos�that�

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
