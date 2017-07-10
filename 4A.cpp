#include <iostream>

using namespace std;

int main(void) {
	int m;
	cin >> m;
	if (m % 2 == 1 || m == 2) {
		cout << "NO" << endl;
		return 0;
	} else {
		cout << "YES" << endl;
		return 0;
	}
}