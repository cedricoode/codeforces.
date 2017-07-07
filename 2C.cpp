#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;


float pow(float x) {
	return x*x;
}

enum DrawingType {Circle, Point, Line};

int compare_float(float);

float distance(float x1, float y1, float x2, float y2);

class Drawing {
public:
	float x;
	float y;
	float r;
	DrawingType type;
	Drawing() {
		this->x = 0;
		this->y = 0;
		this->r = 0;
		
		this->type = Circle;
	}

	Drawing(float a, float b, float c=0, DrawingType type=Circle) {
		this->x = a;
		this->y = b;
		this->r = c;
		this->type = type;
	}

	Drawing observeDrawing(Drawing const& c2) {
		if (compare_float(c2.r - this->r) == 0) {
			float a = 2 * (this->x - c2.x);
			float b = 2 * (this->y - c2.y);
			float r = -(pow(this->x) - pow(c2.x) + pow(this->y) - pow(c2.y));
			return Drawing(a, b, r, Line);
		} else {
			float x = ((pow(this->r)*c2.x - pow(c2.r)*this->x) / (pow(this->r) - pow(c2.r)));
			float y = ((pow(this->r)*c2.y - pow(c2.r)*this->y) / (pow(this->r) - pow(c2.r)));
			float r = sqrt((pow(this->x - c2.x) + pow(this->y - c2.y))) * this->r * c2.r / abs((pow(this->r) - pow(c2.r)));
			return Drawing(x, y, r, Circle);
		}
	}

	vector<Drawing> computeintersection(Drawing const&drawing) const{
		if (this->type != Circle && drawing.type != Circle) {
			return this->line_intersection(drawing);
		} else if (this->type == Line) {
			return this->line_circle_intersection(drawing);
		} else if (drawing.type == Line) {
			return drawing.line_circle_intersection(*this);
		} else {
			return this->circle_circle_intersection(drawing);
		}
	}

	vector<Drawing> line_intersection(Drawing const&dr) const{
		vector<Drawing> drs;
		float prl = (this->y*dr.x - this->x*dr.y);
		if (compare_float(prl) == 0) {
			return drs;
		}
		
		float x=0, y=0;
		if (compare_float(this->x) == 0) {
			y = -this->r / this->y;
			x = -(dr.r + dr.y * y) / dr.x;
		} else {
			float coeff = dr.y - this->y * dr.x / this->x;
			y = (dr.x * this->r / this->x - dr.r) / coeff;
			x = -(this->r + this->y * y) / this->x;
		}
		drs.push_back(Drawing(x, y, 0, Point));
		return drs;
	}

	vector<Drawing> line_circle_intersection(Drawing const& dr) const{
		// this is a line
		vector<Drawing> drs;		
		// translation and rotation 
		float h = this->line_compute_distance(dr.x, dr.y);
		if (compare_float(h - dr.r) == 1) {
			return drs;
		}

		float trl_x = dr.x;
		float trl_y = dr.y;
		float sin_theta = 0, cos_theta = 0;
		if (compare_float(this->y) == 0) {
			sin_theta = 1;
			cos_theta = 0;
		} else {
			float p1x =1, p2x = 2, p1y = this->line_compute_y(p1x), p2y = this->line_compute_y(p2x);
			float d = distance(p1x, p1y, p2x, p2y);
			sin_theta = (p2y - p1y) / d;
			cos_theta = (p2x - p1x) / d;
		}

		Drawing line = line_translation_rotaion(sin_theta, cos_theta, trl_x, trl_y);

		float ty = -line.y * line.r / (pow(line.x) + pow(line.y));
		float tx1 = sqrt(pow(dr.r) - pow(ty));
		
		Drawing dr1(tx1, ty, 0, Point);
		Drawing p1 = dr1.point_translation_rotation(sin_theta, cos_theta, trl_x, trl_y);

		drs.push_back(p1);
		
		if (compare_float(h - dr.r) == -1) {
			Drawing dr2(-tx1, ty, 0, Point);
			Drawing p2 = dr2.point_translation_rotation(sin_theta, cos_theta, trl_x, trl_y);
			drs.push_back(p2);
		}

		return drs;
	}

	vector<Drawing> circle_circle_intersection(Drawing const& dr) const{
		vector<Drawing> drs;
		float d = distance(this->x, this->y, dr.x, dr.y);
		if (compare_float(d - this->r - dr.r) == 1 || compare_float(dr.r - d - this->r) == 1 || compare_float(this->r - d - dr.r) == 1) {
			return drs;
		}
	
		float sin_theta = (dr.y - this->y) / d;
		float cos_theta = (dr.x - this->x) / d;
		float trl_x = this->x, trl_y = this->y;
		float tx = (pow(d) + pow(this->r) - pow(dr.r)) / 2.0 / d;
		float ty1 = sqrt(pow(this->r) - pow(tx));
		
		Drawing tp(tx, ty1, 0, Point);
		Drawing p1 = tp.point_translation_rotation(sin_theta, cos_theta, trl_x, trl_y);
		drs.push_back(p1);
		
		if (compare_float(d - this->r - dr.r) == -1) {
			Drawing tp(tx, -ty1, 0 , Point);
			Drawing p2 = tp.point_translation_rotation(sin_theta, cos_theta, trl_x, trl_y);
			drs.push_back(p2);
		}
		
		return drs;
	}
	
	float line_compute_distance(float x, float y) const{
		return abs(this->x * x + this->y * y + this->r) / sqrt(pow(this->x) + pow(this->y));
	}

	float line_compute_y(float x) const{
		// only when this->y != 0
		return (-this->r - this->x * x) / this->y;
	}

	Drawing line_translation_rotaion(float sin_theta, float cos_theta, float trl_x, float trl_y) const{
		float x = this->x * cos_theta +  this->y * sin_theta;
		float y = -this->x * sin_theta + this->y * cos_theta;
		float c = this->r + this->x * trl_x + this->y* trl_y;
		return Drawing(x, y, c, Line);
	}

	Drawing point_translation_rotation(float sin_theta, float cos_theta, float trl_x, float trl_y) {
		float x1 = cos_theta * this->x - sin_theta * this->y;
		float y1 = sin_theta * this->x + cos_theta * this->y;
		x1 += trl_x;
		y1 += trl_y;
		Drawing dr(x1, y1, 0, Point);
		return dr;
	}

	void print_answer() {
		cout << fixed << setprecision(5) << this->x << " " << this->y << endl;
	}

	void print_drawing() {
		switch(this->type) {
		case Circle:
			cout << "This is a circle, center is: (" << this->x << ", " << this->y << "), radius is: " << this->r << endl;
			break;
		case Line:
			cout << "This is a line, (a, b) is: (" << this->x << ", " << this->y << "), c is: " << this->r << endl;			
			break;
		default:
			cout << "This is a point, it is: (" << this->x << ", " << this->y << ")" << endl;			
		}
	}
};


int compare_float(float diff) {
	if (abs(diff) < 1e-6) {
		return 0;
	} else if (diff > 0){
		return 1;
	} else {
		return -1;
	}
}

float distance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x1-x2)+ pow(y1-y2));
}

int choose_drawing(vector<Drawing> &drs, Drawing &circle) {
	Drawing &dr1 = drs[0];
	Drawing &dr2 = drs[1];
	float t1 = circle.r / distance(dr1.x, dr1.y, circle.x, circle.y);
	float t2 = circle.r / distance(dr2.x, dr2.y, circle.x, circle.y);
	if (t1 > t2) {
		return 0;
	} else return 1;
}


int main(void) {
	float x, y, r;
	vector<Drawing> circles;
	for (int i = 0; i < 3; i++) {
		cin >> x >> y >> r;
		circles.push_back(Drawing(x, y, r, Circle));
	}

	Drawing c4 = circles[0].observeDrawing(circles[1]);
	Drawing c5 = circles[0].observeDrawing(circles[2]);
	
	// c4.print_drawing();
	// c5.print_drawing();
	
	vector<Drawing> drs = c4.computeintersection(c5);
	int idx = 0;
	// for (vector<Drawing>::iterator i = drs.begin(); i != drs.end(); i++) {
	// 	(*i).print_drawing();
	// }
	if (drs.size() == 2) {
		idx = choose_drawing(drs, circles[0]);
		drs[idx].print_answer();
	} else if (drs.size() == 1) {
		drs[idx].print_answer();
	}
}