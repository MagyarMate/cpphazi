#pragma warning(disable:4996)
#define SCL_SECURE_NO_WARNINGS

//Magyar Máté Q8C1NV
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

int A[] = { 0,6,1,4,63,21,87 };
int AN = sizeof(A) / sizeof(int);

class myCounter
{
public:
	myCounter() : con(0), pp(0), ast(0), eq(0) {};
	~myCounter() {};
	int con, pp, ast, eq;

	friend ostream& operator<<(ostream& os, myCounter& counter) {
		os << endl;
		os << "Constructor: \t" << counter.con << endl;
		os << "operator++: \t" << counter.pp << endl;
		os << "operator*: \t" << counter.ast << endl;
		os << "operator=: \t" << counter.eq << endl;
		return os;
	}

private:

};

class OstreamIteratorCnt :public ostream_iterator<int> {
	// counter attributumok v. kulso counter obj.-ra ref

private:
	std::ostream &os;
	int size;
	int cnt;
	const char *sep;
	myCounter& counter;

public:
	// konstr.
	OstreamIteratorCnt(std::ostream &a, const char *b, int c, myCounter& counter)
		: ostream_iterator<int>(a), os(a), size(c), cnt(0), sep(b), counter(counter) { this->counter.con++; };

	// op++
	OstreamIteratorCnt& operator++() {
		counter.pp++;
		static_cast<std::ostream_iterator<int> >(*this).operator++();
		os << (++cnt < size ? sep : "}");
		return *this;
	}
	// op*
	OstreamIteratorCnt& operator*() {
		counter.ast++;
		if (cnt == 0) os << "{";
		static_cast<std::ostream_iterator<int> >(*this).operator*();
		return *this;
	}
	// op=
	OstreamIteratorCnt& operator=(const int x) {
		counter.eq++;
		std::ostream_iterator<int>::operator=(x);
		return *this;
	}
	// kiolv. fv.

	friend ostream& operator<<(ostream& os, OstreamIteratorCnt& myOS) {
		os << myOS.counter;
		return os;
	}

	~OstreamIteratorCnt() {};
};


int main() {

	// ostream_iterator => OstreamIteratorCnt
	ostream_iterator<int> oi(cout, "\t");
	myCounter cnt;
	OstreamIteratorCnt myOI(cout, "\t", AN,cnt);

	int con = 0, pp = 0, ast = 0, eq = 0;

	//copy(A, A + AN, oi);
	copy(A, A + AN, myOI);


	cout << endl << "Az egyes operatorok ennyiszer lettek meghivva az oi objektumban:" << myOI << endl;


	// oi szamlaloinak kiolvasasa, kiirasa

	return 0;
}