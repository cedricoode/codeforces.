#include <iostream>

using namespace std;

int main(void) {
	int d, sumTime;
	cin >> d >> sumTime;

	int **limitd = new int*[d];	
	
	for (int i = 0; i < d; i++) {
		limitd[i] = new int[3];
		cin >> limitd[i][0] >> limitd[i][1];
		sumTime -= limitd[i][0];
		limitd[i][2] = limitd[i][0];
		if (sumTime < 0) {
			cout << "NO" << endl;
			return 0;
		}
	}
	for (int i = 0; i < d; i++) {
		sumTime -= (limitd[i][1] - limitd[i][0]);
		limitd[i][2] = limitd[i][1];
		if (sumTime < 0) {
			limitd[i][2] += sumTime;
			break;
		}
	}
	if (sumTime > 0) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		for (int i = 0; i < d; i++) {
			cout << limitd[i][2] << ' ';
		}
	}
}