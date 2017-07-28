#include <iostream>
#include <cmath>

using namespace std;
typedef long long LL;
LL n, vb, vs, xu, yu;
int x[102];

int main(void) {
	cin >> n >> vb >> vs;
	for (int i = 0; i < n; i++) cin >> x[i];
	cin >> xu >> yu;
	if (xu <= x[1]) cout << 2 << endl;
	else {
		bool startd = false;

		double prevd = x[1] * 1.0 / vb + sqrt((x[1] - xu)*(x[1] - xu) + yu*yu)/vs;
		double d = 0;
		int previ = 1;
		int num_i = 1;
		for (int i = 2; i < n && x[i] <= xu; num_i = ++i) {
			d = x[i] * 1.0 / vb + sqrt((x[i] - xu)*(x[i] - xu) + yu*yu)/vs;
			// cout << d << " ";
			if (!startd && d <= prevd) startd = true;
			if (startd && d > prevd) break;
			if (d <= prevd) previ = i, prevd = d;
		}
		
		// if (n == 85) cout << xu << 111 << yu << endl;
		cout << previ + 1 << endl;
	}
}
