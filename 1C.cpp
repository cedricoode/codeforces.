#include <iostream>
#include <cmath>
#include <iomanip>

const double PI = 3.14159265;
using namespace std;

double sqr(double v) {
    return v*v;
}

struct Point {
    double x;
    double y;
    Point() {

    }
    Point(double x1, double x2){
        this->x = x1;
        this->y = x2;
    }
    double distance(Point* p1) {
        return sqrt(sqr(this->x - p1->x) + sqr(this->y - p1->y));
    }
};

class Triangle {
public:
    Point* p1, *p2, *p3, *center;
    double r, alpha1, alpha2, alpha3;
    Triangle(Point* p1, Point* p2, Point* p3) {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        this->get_center();
        this->r = this->center->distance(this->p1);
        this->compute_alpha();
    }
    Point* get_center() {
        Point* center = new Point();
        double d = 2 * (this->p1->x * (this->p2->y - this->p3 ->y) +
                       this->p2->x * (this->p3->y - this->p1->y) +
                       this->p3->x * (this->p1->y - this->p2->y));
        center->x = 1 / d * ((this->p1->x * this->p1->x+ this->p1->y * this->p1->y) * (this->p2->y - this->p3->y) +
                (this->p2->x * this->p2->x+ this->p2->y * this->p2->y) * (this->p3->y - this->p1->y) +
                (this->p3->x * this->p3->x+ this->p3->y * this->p3->y) * (this->p1->y - this->p2->y));
        center->y = 1 / d * ((this->p1->x * this->p1->x+ this->p1->y * this->p1->y) * (this->p3->x - this->p2->x) +
                (this->p2->x * this->p2->x+ this->p2->y * this->p2->y) * (this->p1->x - this->p3->x) +
                (this->p3->x * this->p3->x+ this->p3->y * this->p3->y) * (this->p2->x - this->p1->x));
        this->center = center;
        return center;
    }

    void compute_alpha() {
        double d = this->p1->distance(this->p2);
        this->alpha1 = 2 * asin(d / 2 / this->r);
        d = this->p2->distance(this->p3);
        this->alpha2 = 2 * asin(d / 2 / this->r);
        d = this->p3->distance(this->p1);
        this->alpha3 = 2 * asin(d / 2 / this->r);
    }

};

double round(double x) {
    return floor(x + 0.5);
}

int approximate(double a1, double a2, double a3) {
    int edges = 3;
    double error = 1;
    int smallest = 100;
    double min_error = 10;
    while (error > 1e-5 && edges <= 100) {
        double m1 = a1 * edges / 2 / PI;
        double m2 = a2 * edges / 2 / PI;
        error = abs(m1 - round(m1)) + abs(m2 - round(m2));
        // cout << fixed << setprecision(5) << m1 << " " << m2 << " " << floor(m1) << " " << floor(m2) << endl;
        if (error < min_error) {
            min_error = error;
            smallest = edges;
        }
        edges++;
    }

    if (edges >= 100 ) {
        return smallest;
    } else {
        return edges - 1;
    }
}

double compute_area(double r, int edges){
    double alpha = 2* PI / edges;
    return edges * (r) * (r) * cos(alpha/2) * sin(alpha / 2);

};

int main(void) {
    Point* p1 = new Point(0, 0);
    Point* p2 = new Point(0, 0);
    Point* p3 = new Point(0, 0);

    cin >> p1->x >> p1->y;
    cin >> p2->x >> p2->y;
    cin >> p3->x >> p3->y;

    Triangle* tri = new Triangle(p1, p2, p3);

    int edges = approximate(tri->alpha1, tri->alpha2, tri->alpha3);
    cout << fixed << setprecision(8) << compute_area(tri->r, edges) << endl;
}