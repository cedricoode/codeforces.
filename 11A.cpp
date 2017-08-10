#include <iostream>

using namespace std;

typedef long long LL;

int n, d;
LL seq[2000];

int main(void) {
	cin >> n >> d;
	for (int i = 0; i < n; ++i) cin >> seq[i];

	int count = 0;
	for (int i = 1; i < n; ++i) {
		if (seq[i] <= seq[i-1]) {
			int temp = (seq[i-1] - seq[i]) / d + 1;
			seq[i] += temp * d;
			count += temp; 
		}
	}

	cout << count << endl;
}