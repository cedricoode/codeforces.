#include <cmath>
#include <iostream>


using namespace std;


float pow(float x) {
	return x*x;
}

class Drawing {
public:
	float x;
	float y;
	float r;
	bool iscircle;
	Drawing() {
		this->x = 0;
		this->y = 0;
		this->r = 0;
		this->iscircle = false;
	}

	Drawing(float a, float b, float c, bool iscircle=true) {
		this->x = a;
		this->y = b;
		this->r = c;
		this->iscircle = iscircle;
	}

	Drawing observeDrawing(Drawing const& c2) {
		if (abs(c2.r - this->r) < 1e-6) {
			float a = 2 * (this->x - c2.x);
			float b = 2 * (this->y - c2.y);
			float r = -(pow(this->x) - pow(c2.x) + pow(this->y) - pow(c2.y));
			Drawing Drawing(a, b, r, false);
			return Drawing;
		} else {
			float x = sqrt((pow(this->r)*c2.x - pow(c2.r)*this->x) / (pow(this->r) - pow(c2.r)));
			float y = sqrt((pow(this->r)*c2.y - pow(c2.r)*this->y) / (pow(this->r) - pow(c2.r)));
			float r = sqrt((pow(this->x - c2.x) + pow(this->y - c2.y))) * this->r * c2.r / (pow(this->r) - pow(c2.r));
			Drawing Drawing(x, y, r, true);
			return Drawing;
		}
	}

	Drawing computeintersection(Drawing const&drawing) {
		if (!this->iscircle && !drawing.iscircle) {
			return this->line_intersection(drawing);
		} else if (!this->iscircle) {
			return this->line_circle_intersection(drawing);
		} else if (!drawing.iscircle) {
			return drawing.line_circle_intersection(*this);
		} else {
			return this->circle_circle_intersection(drawing);
		}
	}

	Drawing line_intersection(Drawing const&dr) {
		if (iszero(this->x)) {
			float y = -this->r / this->b;
			float x = dr
		}
	}

	Drawing line_circle_intersection(Drawing const& dr) {

	}

	Drawing circle_circle_intersection(Drawing const & dr) {

	}
};



float distance(float x1, float y1, float x2, float y2) {
	return sqrt(pow(x1-x2)+ pow(y1-y2));
}


int main(void) {
	Drawing Drawing1(0, 0, 10), Drawing2(60, 10, 10), Drawing3(30, 30, 10);
	Drawing c4 = Drawing1.observeDrawing(Drawing2);
	cout << c4.x << endl << c4.y << endl << c4.r << endl;
}