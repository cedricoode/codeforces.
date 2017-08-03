#include <iostream>
#include <cmath>

using namespace std;

int n;

int count(int t) {
	return n >= t ? (n - t) / 9 + 1 : 0;
}

typedef long long LL;

int main(void) {
	cin >> n;
	LL sum = 0;
	LL bound = sqrt(double(n));
	for (int i = 1; i <= bound; ++i) {
		int ri = (i % 9);
		int rc = (ri * ri) % 9;
		rc = rc ? rc : 9;
		sum += count(rc) - 1;
		for (int j = i+1; j <= bound; ++j) {
			int ri = i % 9, rj = j % 9;
			int rc = (ri * rj) % 9;
			rc = rc ? rc : 9;
			int c = count(rc);
			sum += 2 * count(rc) - 2;
		}
	}


	for (int i = bound; i <= n; ++i) {
		int ri = (i % 9);
		int rc = (ri * ri) % 9;
		rc = rc ? rc : 9;
		if (i != bound)
			sum += count(rc);
		for (int j = i + 1; j <= n; ++j) {
			int ri = i % 9, rj = j % 9;
			int rc = (ri * rj) % 9;
			rc = rc ? rc : 9;
			int c = count(rc);
			if (c) cout << i << " " << j << ": " << c << endl;
			sum += 2 * count(rc);
		}
	}
	cout << sum << endl;
}