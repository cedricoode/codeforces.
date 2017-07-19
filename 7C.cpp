#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int r[50];
int m[50];

long long a, b, c;

double find_int(double t1, double t2, double t3, double t4);

int main(void) {
	cin >> a >> b >> c;

	int cnt = 0;

	if (a == 0) {
		if (c % b != 0) cout << -1 << endl;
		else cout << 0 << " " << -c / b << endl;
		return 0;
	}

	if (b == 0) {
		if (c % a != 0) cout << -1 << endl;
		else cout << -c / a << " " << 0 << endl;
		return 0;
	}

	bool flipped = false;
	if (abs(b) <= abs(a)) {
		if (b < 0) {
			a = -a;
			b = -b;
			c = -c;
		}
		r[0] = a;
		r[1] = b;
	} else {
		flipped = true;
		if (a < 0) {
			a = -a;
			b = -b;
			c = -c;
		}
		r[0] = b;
		r[1] = a;
	}

	while (r[cnt + 1] != 0) {
		cnt++;
		m[cnt-1] = r[cnt-1] / r[cnt];
		if (r[cnt-1] < 0) m[cnt-1]--;
		r[cnt+1] = r[cnt-1] - m[cnt-1] * r[cnt];
	}

	int d = r[cnt];

	if (c % d != 0) {
		cout << -1 << endl;
	} else {
		long long c0 = 1, c1 = -m[cnt-2];
		if (cnt == 1) {
			c0 = 0;
			c1 = 1;			
		} else {
			for (int i = cnt-2; i > 0; i--) {
				long long temp = c0;
				c0 = c1;
				c1 = (temp - c1 * m[i-1]);
			}
		}
		int mult = -c / d;
		c0 *= mult;
		c1 *= mult;

		if (abs(c0) <= 5e18 && abs(c1) <= 5e18) {
			if (flipped) swap(c0, c1);
			cout << c0 << " " << c1 << endl;
			return 0;
		}

		double t01 = (-5e18 - c0) * d / r[1];
		double t02 = (5e18 - c0) * d / r[1];
		double t11 = (-5e18 - c1) * d / r[0];
		double t12 = (5e18 - c1) * d / r[0];
		if (t11 > t12) {
			swap(t11, t12);
		}
		
		if (t01 > t12 || t02 < t11) {
			cout << -1 << endl;
		} else {
			double t = find_int(t01, t02, t11, t12);
			if (t == -1) {
				cout << -1 << endl;
			} else {
				cout << fixed << setprecision(0) ;
				if (!flipped) swap(c0, c1);
				cout << (c0 + (long long) (r[1] / d * t)) << " " << (c1 - (long long) (r[0] / d * t)) << endl;
			}
		}
	}
	
}

double find_int(double t1, double t2, double t3, double t4) {
	double start = max(t1, t3), end = min(t2, t4);
	t1 = ceil(start);
	if (t1 >= start && t1 <= end) {
		return t1;
	} else return -1;
}