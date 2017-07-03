#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    float x;
    float y;
    Point() {

    }
    Point(float x1, float x2){
        this->x = x1;
        this->y = x2;
    }
    float distance(Point* p1) {
        return math.sqrt(math.pow(this->x - p1->x, 2) + math.pow(this->y - p1->y, 2));
    }
};

class Triangle {
public:
    Point* p1, *p2, *p3, *center;
    Triangle(Point* p1, Point* p2, Point* p3) {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
    }
    Point* get_center() {
        Point* center = new Point();
        double d = 2 * (this->p1->x * (this->p2->y - this->p3 ->y) +
                       this->p2->x * (this->p3->y - this->p1->y) +
                       this->p3->x * (this->p1->y - this->p2->y));
        center->x = 1 / d * ((this->p1->x * this->p1->x+ this->p1->y * this->p1->y) * (this->p2->y - this->p3->y) +
                (this->p2->x * this->p2->x+ this->p2->y * this->p2->y) * (this->p3->y - this->p1->y) +
                (this->p3->x * this->p3->x+ this->p3->y * this->p3->y) * (this->p1->y - this->p2->y));
        center-> y = 1 / d * ((this->p1->x * this->p1->x+ this->p1->y * this->p1->y) * (this->p3->x - this->p2->x) +
                (this->p2->x * this->p2->x+ this->p2->y * this->p2->y) * (this->p1->x - this->p3->x) +
                (this->p3->x * this->p3->x+ this->p3->y * this->p3->y) * (this->p2->x - this->p1->x));
        this->center = center;
        return center;
    }

};

int main(void) {
    Point* p1 = new Point(0, 0);
    Point* p2 = new Point(1, 1);
    Point* p3 = new Point(0, 1);
    Triangle* tri = new Triangle(p1, p2, p3);
    cout << p1->distance(tri->center) << endl << p2->distance(tri->center) << endl << p3->distance(tri->center) << endl;
}