#pragma warning(disable:4996)
#define SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <iterator>

using namespace std;

int A[] = { 0,6,1,4,63,21,87 };
int AN = sizeof(A) / sizeof(int);

class OstreamIteratorCnt :public ostream_iterator<int> {
	// counter attributumok v. kulso counter obj.-ra ref
public:
	// konstr.
	OstreamIteratorCnt(ostream &a, const char* b, int c) :
		ostream_iterator<int>(a), Os(a), Size(c), Ctr(0), Sep(b)
	{
	}
	// op++
	OstreamIteratorCnt& operator++()
	{
		static_cast<ostream_iterator<int> >(*this).operator++();
		//Os << (++Ctr != Size ? Sep : "}");
		return *this;
	}
	// op*
	OstreamIteratorCnt& operator*(const OstreamIteratorCnt&)
	{ // figyeld a csalást: op* vté.-e maga az objektum output_it.-nál
	  //if (Ctr == 0)
	  //  Os << "{";	// értékadásnál ez az elsõ fv., ami meghívódik
	  //// output_it.-nál ez a mûvelet ki is hagyható..
		static_cast<std::ostream_iterator<int> >(*this).operator*();
		return *this;
	}
	// op=
	OstreamIteratorCnt& operator=(const int x)
	{
		//if (Ctr == 0)
		//  Os << "";	// értékadásnál ez hívódik meg másodszor
		std::ostream_iterator<int>::operator=(x);
		return *this;
	}
	// kiolv. fv.
	friend ostream& operator<<(ostream& os, const OstreamIteratorCnt& oi)
	{
		//os << "cica" << endl;
		//return os;
	}

private:
	ostream& Os;
	int Size;
	int Ctr;
	const char* Sep;
};

int main() {

	// ostream_iterator => OstreamIteratorCnt
	//ostream_iterator<int> oi(cout, "\t");
	OstreamIteratorCnt oi(cout, "\t", AN);

	//copy(A, A + AN, oi);
	copy(A, A + AN, oi);
	cout << endl << "Az egyes operatorok ennyiszer lettek meghivva az oi objektumban:" << oi << endl;

	// oi szamlaloinak kiolvasasa, kiirasa

	return 0;
}