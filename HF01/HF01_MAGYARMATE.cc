//Magyar Máté Q8C1NV
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;


struct mytime_t {
	int hours;
	int minutes;

	string timestring;

	bool addMinutes(int plusMinutes, int multiplier) {
		if (300 < plusMinutes && 0 > plusMinutes) return false;
		else {
			hours = (hours + (minutes + (multiplier * plusMinutes)) / 60) % 24;
			minutes = (minutes + (multiplier * plusMinutes)) % 60;
			timestring.clear();
			timestring.append(getTextValue(hours));
			timestring.append(" ora ");
			timestring.append(getTextValue(minutes));
			timestring.append(" perc");
			return true;
		}
	}

	bool getValues() {  // Bekeri az ertekeket a kert modon
		int tempHours;
		int tempMinutes;
		char colon;

		
		cin >> tempHours >> colon >> tempMinutes;


		if (0 > tempHours || 23 < tempHours || 0 > tempMinutes || 59 < tempMinutes || ':' != colon || cin.fail()) {
			cout << endl << "Hibas formatum vagy adat, add meg ujra" << endl;

			cin.clear();  // Ha valami nagyon rossz jonne
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return false;
		}
		else {
			hours = tempHours;
			minutes = tempMinutes;
			timestring.clear();
			timestring.append(getTextValue(hours));
			timestring.append(" ora ");
			timestring.append(getTextValue(minutes));
			timestring.append(" perc");
		}
		return true;
	}

	void display(int max) {
		cout << "| ";
		cout.fill('0');
		cout.width(2);
		cout << hours << ':';
		cout.fill('0');
		cout.width(2);
		cout << minutes;

		cout << " |";
		//int spacenum = ((max - timestring.size()) / 2);
		string temp = timestring;
		int spacenum = ((max % 2 ? max: (max + 1)) - (timestring.size() % 2 ? timestring.size() : (timestring.size() +1))) / 2 +1;
		temp.insert(temp.begin(), spacenum, ' ');
		cout << setw(max+2) << setfill(' ') <<left <<  temp << '|' << endl;
		
	}

	

	string getTextValue(int num) { //Itt mar biztosan ketjegyu
		int units, tens;
		tens = num / 10;
		units = num % 10;
		string retVal;

		switch (tens)
		{
		case 0:
			if (0 == units) retVal.append("nulla");
			break;
		case 1:
			if (0 == units) retVal.append("tiz");
			else retVal.append("tizen");
			break;
		case 2:
			if (0 == units) retVal.append("husz");
			else retVal.append("huszon");
			break;
		case 3:
			retVal.append("harminc");
			break;
		case 4:
			retVal.append("negyven");
			break;
		case 5:
			retVal.append("otven");
			break;
		case 6:
			retVal.append("hatvan");
			break;
		default:
			break;
		}

		switch (units) {
		case 1:
			retVal.append("egy");
			break;
		case 2:
			retVal.append("ketto");
			break;
		case 3:
			retVal.append("harom");
			break;
		case 4:
			retVal.append("negy");
			break;
		case 5:
			retVal.append("ot");
			break;
		case 6:
			retVal.append("hat");
			break;
		case 7:
			retVal.append("het");
			break;
		case 8:
			retVal.append("nyolc");
			break;
		case 9:
			retVal.append("kilenc");
			break;
		default:
			break;
		}
		return retVal;
	}
};

struct timeList {
	mytime_t myTime;
	timeList* next=NULL;
};

void display(timeList* head, int max) {
	timeList* current;
	for (current = head; current != NULL; current = current->next) {
		current->myTime.display(max);
	}
}

void garbageCollector(timeList* head) {
	timeList* current;
	for (current = head; current != NULL; ) {
		timeList* garbage = current;
		current = current->next;
		delete garbage;
	}
}

int fillList(timeList* head, int plusMinutes) {
	timeList* current = head;
	int max = head->myTime.timestring.size();
	for (int i = 1; i < 4;i++) {
		current->next = new timeList;
		current->next->myTime = current->myTime;
		current = current->next;
		current->myTime.addMinutes(plusMinutes, i);
		max = current->myTime.timestring.size()>max ? current->myTime.timestring.size() : max;
	}
	return max;
}

bool getMinutes(int& plusMinutes) {
	cin >> plusMinutes;

	if (0 > plusMinutes || 300 < plusMinutes || cin.fail()) {
		cout << endl << "Hibas szamadat, add meg ujra" << endl;

		cin.clear();  // Ha valami nagyon rossz jonne
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return false;
	}
	else {
		return true;
	}
}

int main(int argc, char* argv) {


//	time myTime;
	timeList* head = new timeList;
	int max;
	bool res = false;
	int plusMinutes=20;
	cout << "Hello, kerlek adj meg egy idopontot ilyen formaban: HH:MM!" << endl;
	while (!head->myTime.getValues());
	cout << "Kerlek add meg a hozzaadando percek erteket, legfeljebb 300min" << endl;
	while (!getMinutes(plusMinutes));

	max = fillList(head, plusMinutes);
	display(head, max);
	garbageCollector(head);

	return 0;
}
