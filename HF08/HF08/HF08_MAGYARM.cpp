//Magyar Máté Q8C1NV

#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>


using namespace std;

class SineGen : public unary_function<void, double> {
private:
	double amplitude;
	int	period;
	int phase;
	int x;
public:
	SineGen(double amplitude, int period, int phase) : amplitude(amplitude), period(period), phase(phase), x(0) {};
	double operator()(){
		double retVal = amplitude*sin((double)2 * M_PI * x++ / period + phase * M_PI / 2);
		return round(retVal * 10000 ) / 10000;
	}
};




int main(int argc, char** argv) {

	vector<double> a(20);
	vector<double> b(0);
	vector<double> c(0);

	ostream_iterator<double> oia(cout, " ");
	ostream_iterator<double> oib(cout, " ");
	ostream_iterator<double> oic(cout, " ");

	generate(a.begin(), a.end(), SineGen(1, 4, 0));
	generate_n(inserter(b,b.begin()), 20, SineGen(1, 4, 1));
	generate_n(inserter(c, c.begin()), 20, SineGen(2, 12, 0));

	cout << "1, 4, 0:" << endl;
	copy(a.begin(), a.end(), oia);
	cout << endl << "1, 4, 1:" << endl;
	copy(b.begin(), b.end(), oib);
	cout << endl << "2, 12, 0:" << endl;
	copy(c.begin(), c.end(), oic);
	cout << endl;
	return 0;
}
