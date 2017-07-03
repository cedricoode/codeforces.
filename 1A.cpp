#include <iostream>

using namespace std;

int main(void) {
	int n, m, a;
	cin >> n >> m >> a; 
	int sizem = m / a;
	int sizen = n / a;
	if (m % a != 0) {
		sizem = sizem + 1;
	}
	if (n % a != 0) {
		sizen = sizen + 1;
	}
	long long re = (long long)1 * sizem * sizen;
	cout << re << endl;
}