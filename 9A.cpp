#include <iostream>

using namespace std;

int main(void) {
	int n, m;
	cin >> m >> n;
	int k = n > m ? n : m;
	int t = 6;
	k = (6 - k) + 1;
	if (k % 2 == 0) k /= 2, t /= 2;
	if (k % 3 == 0) k /= 3, t /= 3;
	cout << k << '/' << t << endl;
}