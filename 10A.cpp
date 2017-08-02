#include <iostream>

using namespace std;

int n, P1, P2, P3, T1, T2;
int main(void) {
	cin >> n >> P1 >> P2 >> P3 >> T1 >> T2;
	int sum = 0;
	int previous = 0;
	for (int i = 0; i < n; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		if (i != 0) {
			if (t1 - previous >= T1) {
				sum += T1 * P1;
				if (t1 - previous - T1 >= T2) {
					sum += (t1 - previous - T1 - T2) * P3 + T2 * P2;
				} else {
					sum += (t1 - previous - T1) * P2;
				}
			}
			else sum +=  (t1 - previous) * P1;
		}
		sum += (t2 - t1) * P1;
		previous = t2;
	}
	cout << sum << endl;
}