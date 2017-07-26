#include <iostream>
#include <cmath>
#include <iomanip>
#include <complex>
#include <vector>

using namespace std;

typedef complex<double> Point;

int compare_float(double d1, double d2) {
	double diff = d1 - d2;
	if (abs(diff) < 1e-6) {
		return 0;
	} else if (diff > 0){
		return 1;
	} else {
		return -1;
	}
}

Point c, h, s;
int t1, t2;
double ch, cs, sh;

vector<Point> intersection(Point &p1, double r1, Point &p2, double r2) {
	Point p1t = p1 - p1, p2t = p2 - p1;
	double stheta = -p2.imag() / abs(p2);
	double ctheta = p2.real() / abs(p2);
	Point rotation(ctheta, stheta), rrotation(ctheta, -stheta);
	p1t *= rotation;
	p2t *= rotation;
	double x = (p2t.real() * p2t.real() + r1*r1 - r2*r2) / 2.0 / p2t.real();
	if (abs(x) > r1) return vector<Point>(0);
	double y = sqrt(r1*r1 - x*x);
	vector<Point> intcs(1);
	Point intc(x, y);
	intc = intc * rrotation + p1;
	intcs[0] = intc;

	if (compare_float(y, 0) != 0) {
		intc = Point(x, -y);
		intc = intc * rrotation + p1;
		intcs.push_back(intc);
	}
	return intcs;
}

bool check(double r1, double r2, double r3) {
	r1 = max(r1, 0.);
	r2 = max(r2, 0.);
	r3 = max(r3, 0.);
	vector<Point> ints12 = intersection(c, r1, h, r2);
	vector<Point> ints13 = intersection(c, r1, s, r3);
	
	if (ints12.size() == 0) {
		return abs(h-s) <= (r2 + r3);
	}

	bool found = false; 
	for (int i = 0; i < ints12.size(); i++) {
		if (compare_float(abs(ints12[i]-s), r3) <= 0) {
			found = true;
			break;
		}
	}
	if (!found) {
		for (int i = 0; i < ints13.size(); i++) {
			if (compare_float(abs(ints13[i]-h), r2) <= 0) {
				found = true;
				break;
			}
		}
		return found;
	} else return true;
}

int main(void) { 
	cin >> t1 >> t2;
	double temp1, temp2;
	cin >> temp1 >> temp2;
	c = Point(temp1, temp2);
	cin >> temp1 >> temp2;
	h = Point(temp1, temp2);
	cin >> temp1 >> temp2;
	s = Point(temp1, temp2);

	ch = abs(c-h), sh = abs(s-h), cs = abs(c-s);

	double D1 = ch + t2;
	double D2 = cs + t1;
	double diff = 1, r1 = 0, r2 = min(ch+t2, cs + sh + t1), rc;

	if (cs + sh <= ch + t2) {
		cout << fixed << setprecision(5) << min(cs+sh+t1, ch+t2) << endl;
		return 0;
	}

	while (diff > 1e-8) {
		rc = (r1+r2) / 2;
		if (check(rc, D1- rc, D2-rc)) {
			diff = abs(r2 - r1);
			r1 = rc;
		} else {
			diff = abs(r2 - r1);
			r2 = rc;
		}
	}

	cout << fixed << setprecision(5) << r1 << endl;

}