#include "myMatrix.h"


int main(int argn, char** argc) {

	unitTest myUnit;
	myUnit.runTests();

	myMatrixClass<float> testMatrix;
	cout << "---------------------------------------------------------------"<< endl  << "You can test here:" << endl;
	cin >> testMatrix;  //use \n+CTRL+Z to create EOF
	cout << "TestMatrix:" << endl << testMatrix << endl;
	cout << "TestMatrix - transposed:" << endl << transpose(testMatrix) << endl;



	return 0;
}