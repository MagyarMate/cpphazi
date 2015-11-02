//Magyar Máté Q8C1NV
#include <iostream>
#include <iterator>
#include <vector>
#include <map>

using namespace std;

class TimeStamp
{
public:
	TimeStamp() : hour(0), min(0) {};
	TimeStamp(int hour, int min) : hour(hour), min(min) {};
	~TimeStamp() {};

	friend const bool operator<(const TimeStamp& lVal, const TimeStamp& rVal) {
		return lVal.hour < rVal.hour || ( lVal.hour == rVal.hour && lVal.min < rVal.min );
	}

	friend ostream& operator<<(ostream& os, const TimeStamp& myTimeStamp) {
		os << myTimeStamp.hour << ":" << myTimeStamp.min;
		return os;
	}

private:
	int hour;
	int min;
};


int main(int argc, char** argv) {

	int							hour[]		= { 6,8,14,8,18,8,21 };
	int							min[]		= { 11,22,33,44,55,31,41 };
	double						dat[]		= { 36.5,37.3,38.5,37.1,37.1,37.5,37.4 };
				
	vector<int>					vHours;
	vector<int>					vMins;
	vector<double>				vData;
	map<TimeStamp, double>		mData;

	copy(hour, hour + sizeof(hour) / sizeof(int), inserter(vHours, vHours.end()));
	copy(min, min + sizeof(min) / sizeof(int), inserter(vMins, vMins.end()));
	copy(dat, dat + sizeof(dat) / sizeof(double), inserter(vData, vData.end()));

	for (int i = 0; i < vData.size(); i++) {
		TimeStamp temp(vHours[i], vMins[i]);
		mData.insert(std::pair<TimeStamp, double>(temp, vData[i]));
	}

	for (auto data : mData) {
		cout << data.first << " " << data.second << endl;
	}

	return 0;
}
