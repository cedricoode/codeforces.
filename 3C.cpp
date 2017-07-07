#include <iostream>
#include <cmath>

using namespace std;

bool haveiwon(int a[][3], int);

int main(void) {
	int a[3][3] = {{0}};
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			char ch;
			cin >> ch;
			if (ch == 'X') {
				a[i][j] = 1;
				count1++;
			} else if (ch == '.') {
				a[i][j] = 0;
			} else {
				a[i][j] = -1;
				count2++;
			}
		}
	}

	if (abs(count1 - count2) >= 2) {
		cout << "illegal" << endl;
		return 0;
	}

	bool w1 = haveiwon(a, 1);
	bool w2 = haveiwon(a, -1);

	if (count1 > count2) {
		if (w2) {
			cout << "illegal" << endl;
		} else if (w1) {
			cout << "the first player won" << endl;
		} else if (count1 + count2 == 9){
			cout << "draw" << endl;
		} else {
			cout << "second" <<endl;
		}
	} else if (count1 < count2) {
		cout << "illegal" << endl;
	} else {
		if (w1) {
			cout << "illegal" << endl;
		} else if (w2) {
			cout << "the second player won" << endl;
		} else {
			cout << "first" << endl;
		}
	}

	
}


bool haveiwon(int a[][3], int which) {
	for (int i = 0; i < 8; i++) {
		int count = 0;
		if (i < 3) {
			for (int j = 0; j < 3; j++) {
				count+= a[i][j];
			}
			
		} else if (i < 6) {
			for (int j = 0; j < 3; j++) {
				count += a[j][i-3];
			}
		} else if ( i == 6) {
			for (int j = 0; j < 3; j++) {
				count += a[j][j];
			}
		} else {
			for (int j = 0; j < 3; j++) {
				count += a[j][3-j-1];
			}
		}

		if (count == 3*which) {
			return true;
		}
	}
	return false;
}