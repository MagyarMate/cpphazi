#pragma once
#include <fstream>
#include <vector>
#include <exception>

using namespace std;

class myException : public exception {
	virtual const char* what() const throw()
	{
		return "Given index does not exists";
	}
};

template<class T>
class myMatrixClass {
private:
	size_t p;
	size_t q;
	vector<T> pData;

public:
	myMatrixClass();
	myMatrixClass(const myMatrixClass<T>& other);
	myMatrixClass(unsigned int p, unsigned int q);
	myMatrixClass(unsigned int p, unsigned int q, initializer_list<T> inlist) throw();
	myMatrixClass(ifstream& file);
	~myMatrixClass();

	vector<T> getCol(unsigned int idx);
	vector<T> getRow(unsigned int idx);
	void setCol(unsigned int idx, vector<T> value);
	void setRow(unsigned int idx, vector<T> value);
	T&  getElement(unsigned int n, unsigned int m);
	bool insert(vector<T> col, unsigned int idx = p);
	bool forceInsert(vector<T> col, unsigned int idx = p);
	bool remove(unsigned int idx);
	bool resize(unsigned int p, unsigned int q);
	unsigned int size();


	myMatrixClass<T> readMatrix(ifstream&);
	myMatrixClass<T>& operator=(const myMatrixClass& rval);

	friend ostream& operator<<(ostream&, const myMatrixClass&);
//	friend ofstream& operator<<(ofstream&, const myMatrixClass<T>&);
};

