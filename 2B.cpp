#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

struct Cell {
    int n2;
    int n5;
    char from;
    Cell(): n2(0), n5(0){}
};

struct Body {
    Cell cell2;
    Cell cell5;
};

inline void extract_factor2_5_0(int, int&, int&);

inline void merge_body(Body const &body, Body &target);

inline void compare_merge(Body const &bodyu, Body const &bodyl, Body &target);

void print_most_rounded(vector<vector<Body> > &game, int size);

int main(void) {
    int dim;
    cin >> dim;
    vector<vector<Body> > most_rounded;
    most_rounded.resize(dim);

    for (int i = 0; i < dim; i++) {
        most_rounded[i].resize(dim);
        for (int j = 0; j < dim; j++) {
            int value;
            cin >> value;

            Body &body = most_rounded[i][j];

            int n2=0, n5=0;

            extract_factor2_5_0(value, n2, n5);

            body.cell2.n2 = n2;
            body.cell2.n5 = n5;
            body.cell5.n2 = n2;
            body.cell5.n5 = n5;

            if (i == 0) {
                if (j - 1 >= 0) {
                    Body &body_before = most_rounded[i][j-1];
                    merge_body(body_before, most_rounded[i][j]);
                    body.cell2.from = 'R';
                    body.cell5.from = 'R';
                }
            } else if (j == 0){
                Body &body_before = most_rounded[i-1][j];
                merge_body(body_before, most_rounded[i][j]);
                body.cell2.from ='D';
                body.cell5.from ='D';
            } else {
                Body &body_u = most_rounded[i-1][j];
                Body &body_l = most_rounded[i][j-1];
                compare_merge(body_u, body_l, most_rounded[i][j]);
            }
        }
    }

    print_most_rounded(most_rounded, dim);
}

void extract_factor2_5_0(int value, int& n2, int& n5) {
    while (value % 2 == 0) {
        n2++;
        value /= 2;
    }
    while (value % 5 == 0) {
        n5++;
        value /= 5;
    }
}

void merge_body(Body const &body, Body &target) {
    target.cell2.n2 += body.cell2.n2;
    target.cell2.n5 += body.cell2.n5;

    target.cell5.n5 += body.cell5.n5;
    target.cell5.n2 += body.cell5.n2;
}


void compare_merge(Body const &bodyu, Body const &bodyl, Body &target) {
    if (bodyu.cell2.n2 < bodyl.cell2.n2) {
        target.cell2.n2 += bodyu.cell2.n2;
        target.cell2.n5 += bodyu.cell2.n5;
        target.cell2.from = 'D';
    } else {
        target.cell2.n2 += bodyl.cell2.n2;
        target.cell2.n5 += bodyl.cell2.n5;
        target.cell2.from = 'R';
    }

    if (bodyu.cell5.n5 < bodyl.cell5.n5) {
        target.cell5.n2 += bodyu.cell5.n2;
        target.cell5.n5 += bodyu.cell5.n5;
        target.cell5.from = 'D';
    } else {
        target.cell5.n2 += bodyl.cell5.n2;
        target.cell5.n5 += bodyl.cell5.n5;
        target.cell5.from = 'R';
    }

}

void print_path(vector<vector<Body> > &game, int size, int which) {
    string path = "";
    Body &body = game[size-1][size-1];
    int offsetx = 1, offsety = 1;
    if (which == 2) {
        for (int i = 0; i < 2 * size - 2; i++) {
            body = game[size-offsetx][size-offsety];
            path = body.cell2.from + path;
            if (body.cell2.from == 'R') {
                offsety++;
            } else {
                offsetx++;
            }
        }
    } else if (which == 5) {
        for (int i = 0; i < 2 * size - 2; i++) {
            body = game[size-offsetx][size-offsety];
            path = body.cell5.from + path;
            if (body.cell5.from == 'R') {
                offsety++;
            } else {
                offsetx++;
            }
        }
    }
    cout << path << endl;
}

void print_most_rounded(vector<vector<Body> > &game, int size) {
    Body &body = game[size-1][size-1];
    int zero2, zero5 = 0;
    if (body.cell2.n2 <= body.cell2.n5) {
        zero2 = body.cell2.n2;
    } else {
        zero2 = body.cell2.n5;
    }

    if (body.cell5.n2 <= body.cell5.n5) {
        zero5 = body.cell5.n2;
    } else {
        zero5 = body.cell5.n5;
    }

    if (zero2 < zero5) {
        cout << zero2 << endl;
        print_path(game, size, 2);
    } else {
        cout << zero5 << endl;
        print_path(game, size, 5);        
    }
}

