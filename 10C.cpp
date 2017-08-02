#include <iostream>

using namespace std;

int n;

int main(void) {
	cin >> n;
	double count = 0;
	for (double i = 1; i < n+1; i++) {
		for (double j = i; j < n+1; j++) {
			double mul = i * j;
			int ri = i % 9;
			int rj = i % 9;
			int rc = (ri * rj) % 9;
			int rm = mul % 9;
			
		}
	}
}