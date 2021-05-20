#include <iostream>
#include "PoleChudes.h"
using namespace std;

int main() {
	cout << "Hello World!" << endl;
	PoleChudes object;
	object.enterWordAndGreeting();
	object.letsPlay();
	return 0;
}

char enteringSimbol(int k = 0) {
	//no k: a-z or 0;
	//k=1: 0 or 1;
	//k=2: letters a-z;
	char c, a;
	bool ind;
	int i;
	do {
		do {
			i = 0;
			while ((c = getchar()) != '\n') {
				i++;
				a = c;
			}
			ind = false;
			if (i > 1) {
				ind = true;
				cout << "Error. Wrong entering.\nTry again: ";
			}
		} while (ind);
		ind = false;
		if (k == 1) {
			if (!(a >= '0' && a <= '1')) {
				ind = true;
				cout << "Error. Wrong entering.\nTry again: ";
			}
		}
		else if (k == 2) {
			if (!(a >= 'a' && a <= 'z')) {
				ind = true;
				cout << "Error. Wrong entering.\nTry again: ";
			}
		}
		else {
			if (a != '0' && !(a >= 'a' && a <= 'z')) {
				ind = true;
				cout << "Error. Wrong entering.\nTry again: ";
			}
		}

	} while (ind);
	return a;
}
