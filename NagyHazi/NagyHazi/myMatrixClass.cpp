#include "myMatrixClass.h"

template<class T>
myMatrixClass<T>::myMatrixClass()
{
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
		throw myException();
	}
}

template<class T>
myMatrixClass<T>::myMatrixClass(ifstream & file)
{
	//typeof?
}

template<class T>
myMatrixClass<T>::~myMatrixClass()
{
	delete[] pData;
}

template<class T>
vector<T> myMatrixClass<T>::getCol(unsigned int idx)
{
	return vector<T>();
}

template<class T>
vector<T> myMatrixClass<T>::getRow(unsigned int idx)
{
	return vector<T>();
}

template<class T>
void myMatrixClass<T>::setCol(unsigned int idx, vector<T> value)
{
}

template<class T>
void myMatrixClass<T>::setRow(unsigned int idx, vector<T> value)
{
}

template<class T>
T & myMatrixClass<T>::getElement(unsigned int n, unsigned int m)
{
	// TODO: insert return statement here
}

template<class T>
bool myMatrixClass<T>::insert(vector<T> col, unsigned int idx)
{
	return false;
}

template<class T>
bool myMatrixClass<T>::forceInsert(vector<T> col, unsigned int idx)
{
	return false;
}

template<class T>
bool myMatrixClass<T>::remove(unsigned int idx)
{
	return false;
}

template<class T>
bool myMatrixClass<T>::resize(unsigned int p, unsigned int q)
{
	return false;
}

template<class T>
unsigned int myMatrixClass<T>::size()
{
	return 0;
}

template<class T>
myMatrixClass<T> myMatrixClass<T>::readMatrix(ifstream &)
{
	return myMatrixClass<T>();
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
