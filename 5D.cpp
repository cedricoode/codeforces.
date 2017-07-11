#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


double pow(double t);

double compute_time(int a, int v, double w, double s);



int main(void) {
	int a, v, l , d, w;
	cin >> a >> v >> l >> d >> w;

	double t = 1.0 * w / a;
	double tsum = 0;
	double slowdown = 0.5 * (pow(v) - pow(w)) / a;
	if (slowdown <= 0) {
		tsum = compute_time(a, v, 0, l);
	} else if (0.5 * a * pow(t) >= d) {
		double t1 = sqrt(2.0 * d / a);
		tsum =  t1 + compute_time(a, v, a*t1, l - d);
	} else if (d >= 0.5 * a * pow(t) + slowdown) {
		tsum = t + (v - w) / a + (d - 0.5 * a * pow(t) - slowdown) / v + compute_time(a, v, w, l-d);
	} else {
		double t1 = sqrt((d + pow(w) / 2 / a) / a);
		double t2 = (a * t1 - w) / a;
		tsum = t1 + t2 + compute_time(a, v, w, l-d);
	}
	cout << fixed << setprecision(6) << tsum << endl;
}

double pow(double t) {
	return t*t;
}

double compute_time(int a, int v, double w, double s) {
	double t1 = (v - w) / a;
	double t2 = (s - 0.5 * a * pow(t1)) / v;
	if (t2 < 0) {
		return (sqrt(pow(w) + 2 * a * s) - w) / a;
	} else {
		return t1 + t2;
	}
}