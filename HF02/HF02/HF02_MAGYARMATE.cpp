//Magyar Máté - Q8C1NV

#include <iostream>
#include <typeinfo>
#include <string>
#include "myAnimals.h"
#include "myHerbs.h"


int main(int args, char* argv) {

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
		if (!string(typeid(*myArray[i]).name()).compare("class myHerb")) {
			if((dynamic_cast<myHerb*>(myArray[i]))->isFlower()) flowers++; //Lehetne egyszerubben, de logikailag az, hogy van-e virag, nem tartozik az ososztalyba
		}
		avgAge += myArray[i]->getAge();
	}
	avgAge /= (float)i;

	cout << "Az atlagos eletkor: " << avgAge << endl << "A viragok szama:" << flowers << endl;


	return 0;
}
