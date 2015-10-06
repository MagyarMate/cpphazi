#define BUF_MAX 1000
#define BUF_MIN 1
#define BUD_DEFAULT 10

#include <iostream>
#include <exception>

using namespace std;



class myException : public exception {
public:
	enum defEx { remFromEmpty, insToFull };

	myException(defEx state) {
		this->state = state;
	}
	~myException() {};

	virtual const char* what() const throw()
	{
		if (state == remFromEmpty) {
			return "Exception: The buffer is empty";
		}
		else if (state == insToFull) {
			return "Exception: The buffer is full";
		}
	}
private:
	defEx state;
};


template<class T>
class CircularBuffer
{
public:
	CircularBuffer(int size = 10);
	CircularBuffer(const CircularBuffer<T> &other); //Copy constructor
	~CircularBuffer();

	void insert(T newElement) throw (myException);
	T remove() throw (myException);


	bool operator>(CircularBuffer& rValue);

	bool isEmpty();
	bool isFull();

	template<class F>
	friend ostream& operator<<(ostream& os, const CircularBuffer<F> &myBuffer);

private:
	int size;
	int load;
	bool full, empty;
	int firstIndex;
	int lastIndex;
	T*  pData;
};

template<class T>
CircularBuffer<T>::CircularBuffer(int size)
{
	if (BUF_MIN > size || BUF_MAX < size) this->size = BUD_DEFAULT;
	else this->size = size;
	pData = new T[size];
	firstIndex = 0;
	lastIndex = size - 1;
	load = 0;
	full = false;
	empty = true;
}

template<class T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer<T> &other) : CircularBuffer(other.size)
{
	load = other.load;
	firstIndex = other.firstIndex;
	lastIndex = other.lastIndex;
	full = other.full;
	empty = other.empty;

	for (int i = firstIndex; firstIndex + load > i; i++) {
		this->pData[i] = other.pData[i % size];
	}
}

template<class T>
CircularBuffer<T>::~CircularBuffer()
{
	delete[] pData;
}

template<class T>
void CircularBuffer<T>::insert(T newElement) throw (myException)
{
	if (full) throw myException(myException::defEx::insToFull);
	else {
		if (empty) empty = false;
		if ((load += 1) == size) full = true;
		pData[lastIndex = (lastIndex + 1) % size] = newElement;
	}
}

template<class T>
T CircularBuffer<T>::remove() throw (myException)
{
	T retVal;
	if (empty) throw myException(myException::defEx::remFromEmpty);
	else {
		if (full) full = false;
		if ((load -= 1) == 0) empty = true;
		retVal = pData[firstIndex];
		firstIndex = (firstIndex + 1) % size;
	}
	return retVal;
}

template<class T>
bool CircularBuffer<T>::operator>(CircularBuffer & rValue)
{
	return this->load > rValue.load ? true : false;
}

template<class T>
bool CircularBuffer<T>::isEmpty()
{
	return load == 0 ? true : false;
}

template<class T>
bool CircularBuffer<T>::isFull()
{
	return load == size ? true : false;
}

template<class T>
ostream& operator<<(ostream& os, const CircularBuffer<T> &myBuffer) {
	for (int i = myBuffer.firstIndex; myBuffer.firstIndex + myBuffer.load > i; i++) {
		os << myBuffer.pData[i % myBuffer.size] << " ";
	}
	return os;
}


template<class T>
T getMax(T& a, T& b) {
	return a > b ? a : b;
}


/*************************************************************************************/
//MAIN: TEST
int main(int argn, char** argv) {

	CircularBuffer<double> dcb(2);
	try {
		dcb.insert(3.3);
		dcb.insert(4.4);
		cout << "cb= " << dcb << endl;
		double r = dcb.remove();
		cout << "r= " << r << endl;
		cout << "cb= " << dcb << endl;
		dcb.insert(5.5);
		cout << "cb= " << dcb << endl;
		dcb.insert(6.6);
	}
	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}

	float f1 = 1.23, f2 = 3.21;
	cout << getMax(f1, f2) << endl;

	CircularBuffer<int> icb1(1200);
	CircularBuffer<int> icb2 = icb1;
	try {
		icb1.insert(5);
		cout << getMax(icb2, icb1) << endl;
		icb1.remove();
		icb1.remove();
	}
	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}


	return 0;
}