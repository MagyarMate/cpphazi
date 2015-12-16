#pragma once
#include <fstream>
#include <vector>
#include <exception>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;
/** Custom exception class derived from std::exception*/
class myException : public exception {
public:
	/** Definition of the exception*/
	enum reason_t{
		general_c,		///< General exception
		index_c,		///< Indexing error
		oversize_c,     ///< Exceeding matrix size
		memory_c        ///< Memory allocation error
	};
	/** 
	*  Describes the type of exeption
	*  \return the string format of the error
	*/
	virtual const char* what(reason_t reason=general_c) const throw()
	{
		switch (reason)
		{
		case myException::general_c:
			return "General error happened";
			break;
		case myException::index_c:
			return "Given index does not exists";
			break;
		case myException::oversize_c:
			return "Size error";
			break;
		case myException::memory_c:
			return "Memory allocation error";
		default:
			return "Default error";
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
	size_t p; 
	size_t q;
	vector<T> pData;

	void fill(T data);

public:
	myMatrixClass() {};
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
	/** Destructor*/
	//~myMatrixClass();

	vector<T> getCol(unsigned int idx);
	vector<T> getRow(unsigned int idx);
	void setCol(unsigned int idx, vector<T> value);
	void setRow(unsigned int idx, vector<T> value);
	T&  getElement(unsigned int n, unsigned int m) const throw();
	void setElement(unsigned int n, unsigned int m, T value) const throw();
	void resize(unsigned int p, unsigned int q);
	unsigned int size();

	myMatrixClass<T>& transpose(myMatrixClass& other);

	myMatrixClass<T> readMatrix(ifstream&);

	myMatrixClass<T>& operator=(const myMatrixClass& rval);

	template<class J>
	friend ostream& operator<<(ostream&, const myMatrixClass<J>&);
	template<class J>
	friend istream& operator>>(istream&, myMatrixClass<J>&);
//	friend ofstream& operator<<(ofstream&, const myMatrixClass<T>&);
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
	if (inlist.size <= p*q) {

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
	if (idx + p > p*q) throw (myException(myException::index_c));
	for (int i = idx; i < idx + p; i++) {
		retVal.insert(pData[i]);
	}
	return retVal;
}

template<class T>
vector<T> myMatrixClass<T>::getRow(unsigned int idx)
{
	vector<T> retVal;
	if (idx > q) throw (myException(myException::index_c));

	for (int i = idx;i < idx + (p - 1)*q;i += p) {
		retVal.insert(pData[i]);
	}

	return vector<T>();
}

template<class T>
void myMatrixClass<T>::setCol(unsigned int idx, vector<T> value) //TODO
{
}

template<class T>
void myMatrixClass<T>::setRow(unsigned int idx, vector<T> value) //TODO
{
}

template<class T>
T & myMatrixClass<T>::getElement(unsigned int n, unsigned int m) const throw()
{
	if (m > this->p || n > this->q || m*n > this->p*q) throw myException(myException::index_c);
	return this->pData[(n)*this->p + (m)];  //Formula: (a)*p+(b)
}

template<class T>
void myMatrixClass<T>::setElement(unsigned int n, unsigned int m, T value) const throw()
{
	if (m > this->p || n > this->q || m*n > this->p*q) throw myException(myException::index_c);
	this->pData[n*m] = value;
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
myMatrixClass<T> & myMatrixClass<T>::transpose(myMatrixClass & other)
{
	// TODO: insert return statement here
}

template<class T>
myMatrixClass<T> myMatrixClass<T>::readMatrix(ifstream & inputFile) //TODO
{
	while (inputFile.eof()) {
		//string 
	}
}

template<class T>
myMatrixClass<T>& myMatrixClass<T>::operator=(const myMatrixClass & rval)
{
	this->p = rval.p;
	this->q = rval.q;
	this->pData = rval.pData;
}

template<class T>
ostream & operator<<(ostream & out, const myMatrixClass<T> & myMatrix)
{
	for (int i = 0;i < myMatrix.q;i++) {
		for (int j = 0;j < myMatrix.p;j++) {
			out << " " << myMatrix.pData[i + j];
		}
		out << ";\n";
	}
	return out;
}

template<class T>
ofstream & operator<<(ofstream &, const myMatrixClass<T>&)
{
	// TODO: insert return statement here
}

template<class T>
istream& operator>>(istream& in, myMatrixClass<T>& myMatrix) {
	string line;
	char last;
	bool run = true;
	unsigned int q = 0;
	while (run && getline(in, line, ';')) {
		q++;
		istringstream reader(line);
		vector<T> lineData;
		string::const_iterator i = line.begin();
		while (!reader.eof())
		{
			T value;
			reader >> value;
			lineData.push_back(value);
		}

		if (myMatrix.p == 0) myMatrix.p = lineData.size();
		for (auto dat : lineData) {
			myMatrix.pData.push_back(dat);
		}
		in.get(last);
		cout << (last == '\n' ? in.get() != EOF : 1);
		run = !in.eof() && (last=='\n'?in.get() == EOF : 1);
	}
	myMatrix.q = q;
	cout << "P, Q : " << myMatrix.p << ", " << myMatrix.q << endl;
	return in;
}
