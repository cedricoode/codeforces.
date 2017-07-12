#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


double pow(double t);

double compute_time(double a, double v, double w, double s);



int main(void) {
	double a, v, l , d, w;
	cin >> a >> v >> l >> d >> w;
	double tsum = 0;

	double d1 = 0.5 * pow(w) / a;
	double slowdown = 0.5 * (pow(v) - pow(w)) / a;
	double d2 = 0.5 * pow(v) / a;
	if (v < w || d1 >= d) {
		tsum = compute_time(a, v, 0, l);
	} else if (slowdown + d2 <= d) {
		double t1 = v /a ;
		double t2 = 1.0 * (v-w) /a;
		double t3 = (d - slowdown - d2) / v;
		tsum = t1 + t2 + t3 + compute_time(a, v, w, l-d);
	} else {
		double t1 = sqrt((d+pow(w)/2/a) / a);
		double t2 = (a*t1 - w) /a;
		tsum = t1 + t2 + compute_time(a,v, w, l-d); 
	}

	cout << fixed << setprecision(6) << tsum << endl;
}

double pow(double t) {
	return t*t;
}

double compute_time(double a, double v, double w, double s) {
	double t1 = (v-w) /a;
	double d = 0.5 * a * pow(t1) + w * t1;
	if ( d>= s) {
		return (-w + sqrt(pow(w) + 2* a*s)) / a;
	} else {
		return t1 + (s - d) / v;
	}
}