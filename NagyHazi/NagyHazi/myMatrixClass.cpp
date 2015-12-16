#include "myMatrixClass.h"

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
	if(idx > q) throw (myException(myException::index_c));

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
	} catch(exception &e)
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
ostream & operator<<(ostream &, const myMatrixClass<T> &)
{
	// TODO: insert return statement here
}

template<class T>
ofstream & operator<<(ofstream &, const myMatrixClass<T>&)
{
	// TODO: insert return statement here
}

template<class T>
istream& operator>>(istream& in, myMatrixClass<T>& myMatrix) {
	istream retVal;
	string line;
	unsigned int q = 0;

	while (!getline(in, temp, ';').eof) {
		istringstream reader(line);
		vector<T> lineData;

		string::const_iterator i = line.begin();
		while (!reader.eof())
		{
			T value;
			value << reader;

			lineData.push_back(val);
		}
		if (myMatrix.p == 0) myMatrix.p = lineData.size();
		q++;
		for (auto dat : lineData) {
			myMatrix.pData.push_back(dat);
		}
	}
	myMatrix.q = q;

	return in;
}
