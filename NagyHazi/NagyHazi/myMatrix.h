#pragma once
#define UNIT_TEST_FILES 1
#define OK "OK"
#define NOK "NOK"

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <iterator>
#include <string>
#include <sstream>


/*! \mainpage Haladó C++ programozás nagy házi feladat
*
* \section name Magyar Máté
*
* Q8C1NV
*
* \section problem Feladatleírás
* \subsection explain Mátrix tároló
* A mûveletek fõleg a mátrix végét érintik. Alapvetõen több oszlop, mint sor. Lehet transzponálni.
*/



using namespace std;


namespace arbitraryFunctions {
	/**
	* Swaps the two given number
	*/
	void swap(unsigned int& a, unsigned int& b) {
		unsigned int c;
		c = a;
		a = b;
		b = c;
	}
}



/** Custom exception class derived from std::exception*/
class myException : public exception {
public:
	/** Definition of the exception*/
	enum reason_t {
		general_c,		///< General exception
		index_c,		///< Indexing error
		oversize_c,     ///< Exceeding matrix size
		memory_c,       ///< Memory allocation error
		bad_data_c,     ///< Bad data given
	} reason;
	/**
	*  Describes the type of exeption
	*  \return the string format of the error
	*/
	myException(reason_t reason) {
		this->reason = reason;
	}
	virtual const char* what() const throw()
	{
		switch (reason)
		{
		case myException::general_c:
			return "General error happened\n";
			break;
		case myException::index_c:
			return "Given index does not exists\n";
			break;
		case myException::oversize_c:
			return "Size error\n";
			break;
		case myException::memory_c:
			return "Memory allocation error\n";
		case myException::bad_data_c:
			return "Bad data\n";
		default:
			return "Default error\n";
			break;
		}
	}
};
/** Matrix class.
* This class is a generic matrix class, storing values, and can be transposed.
*/
template<class T>
class myMatrixClass {
private:
	bool transposed;

	size_t p;
	size_t q;
	vector<T> pData;

	void fill(T data);

public:
	myMatrixClass() {
		p = 0;
		q = 0;
		transposed = 0;
	};
	/** Copy constructor
	* \param other The matrix to be copied
	*/
	myMatrixClass(const myMatrixClass<T>& other);
	/** Constructor allocates the given size for matrix
	* \param p dimension of columns
	* \param q dimension of rows
	*/
	myMatrixClass(unsigned int p, unsigned int q);
	/** Constructor allocates the given size for matrix and filles
	* \param p dimension of columns
	* \param q dimension of rows
	* \param inlist you can give the parameters by an init list
	*/
	myMatrixClass(unsigned int p, unsigned int q, initializer_list<T> inlist) throw();

	/**
	* \param idx index of the desired column
	* \return the column in vector
	*/
	vector<T> getCol(unsigned int idx);
	/**
	* \param idx index of the desired row
	* \return the row in vector
	*/
	vector<T> getRow(unsigned int idx);
	/**
	* Returns the desired element
	* \param n column id
	* \param m row id
	* \return matrix element
	*/
	T&  getElement(unsigned int n, unsigned int m) throw();

	/**
	* Resizes the matrix
	* \param p column dimension
	* \param q row dimension
	*/
	void resize(unsigned int p, unsigned int q);

	/**
	* \return the size of the container
	*/
	unsigned int size();



	/**
	* Reads matrix from file
	* \return myMatrixClass
	*/
	myMatrixClass<T> readMatrix(ifstream&);

	/**
	* Copy constructor
	* \return myMatrixClass
	*/
	myMatrixClass<T>& operator=(const myMatrixClass& rval);


	/**
	* Stream input operator
	*/
	template<class J>
	friend ostream& operator<<(ostream&, const myMatrixClass<J>&) throw();
	/**
	* Stream output operator
	*/
	template<class J>
	friend istream& operator>>(istream&, myMatrixClass<J>&);
	/**
	* Transpose
	* Working explanation: the container remains in its original state.
	* Matrix vector subscripts swapped when accessing elements, this causes transpose.
	*/
	template<class J>
	friend myMatrixClass<J>& transpose(myMatrixClass<J>& other);
};

template<class T>
void myMatrixClass<T>::fill(T data)
{
	pData.push_back(data);
}

template<class T>
myMatrixClass<T>::myMatrixClass(const myMatrixClass<T>& other)
{
	this = other;
}

template<class T>
myMatrixClass<T>::myMatrixClass(unsigned int p, unsigned int q)
{
	this->pData.reserve(p*q);
}

template<class T>
myMatrixClass<T>::myMatrixClass(unsigned int p, unsigned int q, initializer_list<T> inlist) throw()
{
	if (inlist.size() == p*q) {
		this->p = p;
		this->q = q;
		copy(inlist.begin(), inlist.end(), inserter(this->pData, pData.begin()));
	}
	else {
		throw myException(myException::oversize_c);
	}
}

//template<class T>
//myMatrixClass<T>::~myMatrixClass()
//{
//	delete[] pData;
//}

template<class T>
vector<T> myMatrixClass<T>::getCol(unsigned int idx)
{
	vector<T> retVal;
	if (idx * p > p*q) throw (myException(myException::index_c));
	for (int i = 0; i < p; i++) {
		retVal.push_back(this->getElement(idx, i));
	}
	return retVal;
}

template<class T>
vector<T> myMatrixClass<T>::getRow(unsigned int idx)
{
	vector<T> retVal;
	if (idx > q) throw (myException(myException::index_c));

	for (int i = 0;i < q;i++) {
		retVal.push_back(this->getElement(i, idx));
	}

	return retVal;
}

template<class T>
T & myMatrixClass<T>::getElement(unsigned int n, unsigned int m) throw()
{
	if (this->transposed) arbitraryFunctions::swap(n, m);
	if (m > this->p || n > this->q || m*n > this->p*q) throw myException(myException::index_c);
	return this->pData[(n)*this->p + (m)];  //Formula: (a)*p+(b)
}

template<class T>
void myMatrixClass<T>::resize(unsigned int p, unsigned int q) throw()
{
	try {
		this->pData.resize(p*q);
	}
	catch (exception &e)
	{
		throw myException(myException::memory_c);
	}
}

template<class T>
unsigned int myMatrixClass<T>::size()
{
	return p*q;
}

template<class T>
myMatrixClass<T> &transpose(myMatrixClass<T> & other)
{
	arbitraryFunctions::swap(other.p, other.q);
	other.transposed = true;
	return other;
}

template<class T>
myMatrixClass<T>& myMatrixClass<T>::operator=(const myMatrixClass & rval)
{
	this->p = rval.p;
	this->q = rval.q;
	this->transposed = rval.transposed;
	this->pData = rval.pData;
	return *this;
}

template<class T>
ostream & operator<<(ostream & out, const myMatrixClass<T> & myMatrix)
{
	if (!myMatrix.transposed) {
		for (unsigned int i = 0; i < myMatrix.q;i++) {
			for (unsigned int j = 0; j < myMatrix.p;j++) {
				out << " " << myMatrix.pData[i*myMatrix.p + j];
			}
			out << ";\n";
		}
	}
	else {
		for (unsigned int i = 0; i < myMatrix.q;i++) {
			for (unsigned int j = 0; j < myMatrix.p;j++) {
				out << " " << myMatrix.pData[j*myMatrix.q + i];
			}
			out << ";\n";
		}
	}
	return out;
}

template<class T>
istream& operator>>(istream& input, myMatrixClass<T>& myMatrix) throw() {
	string line;
	char last;
	unsigned int q = 0;

	input.ignore('\0');
	while (!input.eof() && getline(input, line, ';')) {
		q++;
		istringstream reader(line);
		vector<T> lineData;
		while (!reader.eof())
		{
			T value;
			reader >> value;
			lineData.push_back(value);
		}

		if (myMatrix.p == 0) myMatrix.p = lineData.size();
		if (lineData.size() != myMatrix.p) throw myException(myException::reason_t::bad_data_c);
		for (auto dat : lineData) {
			myMatrix.pData.push_back(dat);
		}
		input.get();
	}
	myMatrix.q = q;
	return input;
}



/**
* This class is used to collect and run the unit tests.
*/
class unitTest
{
public:
	unitTest() {};
	~unitTest() {};



	/**
	* Running unit tests. You can set UNIT_TEST_FILES when compiling if you want to check file handling.
	*/
	void runTests() {

		if (UNIT_TEST_FILES) {
			cout << "File read: " << (checkFileRead() ? OK : NOK) << endl;
			cout << "File write: " << (checkFileWrite() ? OK : NOK) << endl;
			cout << "File read transposed: " << (checkFileReadTransposed() ? OK : NOK) << endl;
		}
		cout << "Read from standard i/o:" << (checkStdIO() ? OK : NOK) << endl;
		cout << "Transpose: " << (checkTranspose() ? OK : NOK) << endl;
		cout << "Get elements, rows, columns: " << (checkGetElements() ? OK : NOK) << endl;
		cout << "Init list: " << (checkInitList() ? OK : NOK) << endl;

	}


private:

	bool checkFileRead() {
		stringstream expected(" 5 6;\n 7 8;\n 9 10;\n");
		stringstream actual;
		ifstream mat("matrix.txt");

		myMatrixClass<int> testMatrix;
		mat >> testMatrix;
		actual << testMatrix;
		return !actual.str().compare(expected.str());
	}

	bool checkFileWrite() {
		stringstream expected(" 5 6;\n 7 8;\n 9 10;\n");
		stringstream actual;
		ifstream mat("matrix.txt");
		ofstream out("matrix2.txt");

		myMatrixClass<int> testMatrix;
		mat >> testMatrix;
		out << testMatrix;

		out.close();

		ifstream mat2("matrix2.txt");
		actual << testMatrix;


		return !actual.str().compare(expected.str());
	}

	bool checkFileReadTransposed() {
		stringstream expected(" 5 7 9;\n 6 8 10;\n");
		stringstream actual;
		ifstream mat("matrix.txt");
		ofstream out("matrix2.txt");

		myMatrixClass<int> testMatrix;
		mat >> testMatrix;
		transpose(testMatrix);
		out << testMatrix;
		out.close();

		ifstream mat2("matrix2.txt");
		mat2 >> testMatrix;
		actual << testMatrix;
		mat2.clear();
		mat2.close();
		return !actual.str().compare(expected.str());
	}

	bool checkGetElements() {

		myMatrixClass<int> testMatrix(3, 3, { 1,2,3,4,5,6,7,8,9 });
		if (testMatrix.getElement(1, 0) != 4) return false;

		{
			vector<int> testcol = testMatrix.getCol(1);
			vector<int> expected = { 4, 5, 6 };
			if (!equal(testcol.begin(), testcol.end(), expected.begin())) return false;
		}

		{

			vector<int> testcol = testMatrix.getRow(1);
			vector<int> testcolT = transpose(testMatrix).getRow(1);
			vector<int> expected = { 2, 5, 8 };
			vector<int> expectedT = { 4, 5, 6 };
			if (!equal(testcol.begin(), testcol.end(), expected.begin())) return false;
			if (!equal(testcolT.begin(), testcolT.end(), expectedT.begin())) return false;

			try {
				int testcol = testMatrix.getElement(23, 45);
			}
			catch (myException e) {
				string expected("Given index does not exists\n");
				if (expected.compare(e.what())) return false;
			}


			return true;
		}


	}

	bool checkInitList() {
		stringstream expected(" 10 20 34;\n 23 44 55;\n 99 88 44;\n");
		stringstream actual;
		myMatrixClass<int> testMatrix(3, 3, { 10, 20, 34, 23, 44, 55, 99, 88, 44 });
		actual << testMatrix;

		if (actual.str().compare(expected.str())) return false;

		try {
			myMatrixClass<int> testMatrix2(3, 3, { 10, 20, 34, 23, 44, 55, 99, 88, 44, 45 });
		}
		catch (myException e) {
			string expected("Size error\n");
			if (expected.compare(e.what())) return false;
		}

		return true;
	}

	bool checkStdIO() {
		stringstream expected(" 5 6;\n 7 8;\n 9 10;\n");
		stringstream actual;

		myMatrixClass<int> testMatrix;
		expected >> testMatrix;
		actual << testMatrix;
		if (actual.str().compare(expected.str())) return false;

		stringstream input2(" 5 6;\n 7 8;\n 9;\n");
		string expected2("Bad data\n");
		myMatrixClass<int> testMatrix2;

		try {
			input2 >> testMatrix2;
		}
		catch (myException e) {
			if (expected2.compare(e.what())) return false;
		}

		return true;
	}

	bool checkTranspose() {
		stringstream expected(" 5 7 9;\n 6 8 10;\n");
		stringstream input(" 5 6;\n 7 8;\n 9 10;\n");
		stringstream actual;


		myMatrixClass<int> testMatrix;
		input >> testMatrix;
		transpose(testMatrix);
		actual << testMatrix;

		return !actual.str().compare(expected.str());
	}

};
