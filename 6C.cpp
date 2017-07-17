#include <iostream>

using namespace std;


int main(void) {
	int n;
	cin >> n;
	int consum = 0;
	int candies[100000];
	int alice = 0, bob = 0;
	int i_alice = 0, i_bob= n-1;

	for (int i = 0; i < n; i++) {
		cin >> candies[i];
	}

	for (int i = 0; i < n; i++) {
		if (consum <= 0) {
			alice++;
			consum += candies[i_alice];
			i_alice++;
		} else {
			bob++;
			consum -= candies[i_bob];
			i_bob--;
		}
	}

	cout << alice << " " << bob << endl;
}