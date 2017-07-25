#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

typedef pair<float, float> Point;

Point operator-(const Point &p1, const Point &p2) {
	Point p;
	p.first = p1.first - p2.first;
	p.second = p1.second - p2.second;
	return p;
}

Point operator/(const Point &p1, float ceff) {
	Point p;
	p.first = p1.first / ceff;
	p.second = p1.second / ceff;
	return p;
}

Point middle(const Point &p1, const Point &p2) {
	Point p;
	p.first = (p1.first + p2.first) / 2.0;
	p.second = (p1.second + p2.second) / 2.0;
	return p;
}

int t1, t2;
Point c, h, s;
bool is_same_line, is_middle, is_same_dir;
float ch, cs, sh;

void same_path() {
	is_same_line = ((h.second-c.second)*(s.first-c.first) == (s.second-c.second)*(h.first-c.first));
}

void same_dir() {
	Point p1 = (h-c)/ch, p2 = (s-c)/cs;
	is_same_dir = ((abs(p1.first-p2.first) < 1e-8) && (abs(p1.second-p2.second) < 1e-8));
}

float dist(Point &p1, Point &p2) {
	return sqrt((p1.second-p2.second)*(p1.second-p2.second) + (p1.first-p2.first)*(p1.first-p2.first));
}

int main(void) {
	cin >> t1 >> t2;
	cin >> c.first >> c.second >> h.first >> h.second >> s.first >> s.second;
	same_path();
	ch = dist(c, h), cs = dist(c, s), sh = dist(s, h);
	same_dir();
	is_middle = is_same_line && is_same_dir && ch > cs;

	float d = 0;

	if (is_same_line) {
		if (is_same_dir) {
			if (is_middle) {
				d = min(t1, t2) + ch;
			} else {
				if (t1 > t2) d = t2 + ch;
				else {
					if (t2 - t1 < 2 * sh) d = ch + t1 + (t2 - t1) / 2.0;
					else d = t1 + 2*sh + ch;
				}
			}
		} else {
			if (t1 >= t2) {
				if (t1 - t2 >= 2*ch) d = t2 + ch;
				else d = t2 + (t1 - t2) / 2.0;
			} else {
				if (t2 - t1 < 2 * cs) d = (t2 - t1) / 2.0;
				else d = cs + sh + min(float(t1), t2+ch-cs-sh);
			}
		}
	} else {
		if (cs + sh <= t2 + ch) {
			if (t1 >= t2) d = cs + sh + t2 + ch - cs -sh;
			else d = cs + sh + min(t2+ch-cs-sh, float(t1));
		} else {
			Point pm = middle(c, s);
			Point p1 = c;
			Point p2 = s;
			float diff = dist(pm, c)+ dist(pm, h) - t2 - ch;
			while (abs(diff) > 1e-8 ) {
				if (diff > 0) p2 = pm;
				else p1 = pm;
				pm = middle(p1, p2);
				diff = dist(pm, c) + dist(pm, h) - t2 - ch;
			}
			if (t1 >= t2) d = t2 + ch - dist(pm, h);
			else d = dist(pm, c);
		}

		float candd = 0;
		if (ch+sh*2 <= t1 + cs + sh) {
			if (t1 >= t2) candd = ch + min(float(t2), t1+cs+sh-ch-2*sh);
			else candd = ch + t1 + cs + sh - ch - 2 * sh;
		} else {
			Point pm = middle(c, h);
			Point p1 = c, p2 = h;
			float diff = dist(pm, c) + dist(pm, s) + dist(s, h) - t1 - cs - sh;
			while (abs(diff) > 1e-8) {
				if (diff > 0) p2 = pm;
				else p1 = pm;
				pm = middle(p1, p2);
				diff = dist(pm, c) + dist(pm, s) + dist(s, h) - t1 - cs - sh;
			}
			candd = dist(pm, c);
		}
		if (candd > d) d = candd;
	}
	// if (t1 >= t2) {
	// 	if (is_same_line) {
	// 		if (is_same_dir) {
	// 			if (is_middle) {
	// 				d = t2 + ch;
	// 			} else d = t2 + ch;
	// 		} else {
	// 			if (t1 - t2 >= 2*ch) d = t2 + ch;
	// 			else d = t2 + (t1 - t2) / 2.0;
	// 		}
	// 	} else {
	// 		if (t1 - t2 >= 2*ch) d = t2 + ch;
	// 		else d = t2 + (t1 - t2) / 2.0;
	// 	}
	// } else {
	// 	if (is_same_line) {
	// 		if (is_same_dir) {
	// 			if (is_middle) d = t1 + ch;
	// 			else {
	// 				if (t2 - t1 < 2 * sh) d = ch + t1 + (t2 - t1) / 2.0;
	// 				else d = t1 + 2*sh + ch;
	// 			}
	// 		} else {
	// 			if (t2 - t1 < 2 * cs) d = t2 / 2.0;
	// 			else d = t1 + cs + sh;
	// 		}
	// 	} else {
	// 		if (t2 - t1 < 2 * (cs+sh)) d = t1 + (t2-t1) / 2.0;
	// 		else d = t1 + cs + sh;
	// 	}
	// }

	cout << setprecision(5) << fixed << d << endl;
}


