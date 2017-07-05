#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

struct Cell {
    int n2;
    int n5;
    char *path;
    Cell(): n2(0), n5(0){}
};

struct Body {
    Cell cell2;
    Cell cell5;
};

void extract_factor2_5_0(Cell &cell, int);

void merge_body(Body const &body, Body &target);

void compare_merge(Body const &bodyu, Body const &bodyl, Body &target);

void print_most_rounded(vector<vector<Body> > &game, int size);

int main(void) {
    int dim;
    cin >> dim;
    vector<vector<Body> > most_rounded;
    most_rounded.resize(dim);
    for (int i = 0; i < dim; i++) {
        most_rounded[i].resize(dim);
        for (int j = 0; j < dim; j++) {
            Cell cell;
            Body body;
            int value;
            cin >> value;

            extract_factor2_5_0(cell, value);

            body.cell2 = cell;
            body.cell5 = cell;
            body.cell2.path = new char[i+j+1];
            body.cell5.path = new char[i+j+1];
            body.cell2.path[0] = '\0';
            body.cell5.path[0] = '\0';

            most_rounded[i][j] = body;
            if (i == 0) {
                if (j - 1 >= 0) {
                    Body &body_before = most_rounded[i][j-1];
                    merge_body(body_before, most_rounded[i][j]);
                    strcpy(most_rounded[i][j].cell2.path, body_before.cell2.path);
                    strcat(most_rounded[i][j].cell2.path, "R");
                    strcpy(most_rounded[i][j].cell5.path, body_before.cell5.path);
                    strcat(most_rounded[i][j].cell5.path, "R");
                }
            } else if (j == 0){
                Body &body_before = most_rounded[i-1][j];
                merge_body(body_before, most_rounded[i][j]);
                strcpy(most_rounded[i][j].cell2.path, body_before.cell2.path);
                strcat(most_rounded[i][j].cell2.path, "D");
                strcpy(most_rounded[i][j].cell5.path, body_before.cell5.path);
                strcat(most_rounded[i][j].cell5.path, "D");
            } else {
                Body &body_u = most_rounded[i-1][j];
                Body &body_l = most_rounded[i][j-1];
                compare_merge(body_u, body_l, most_rounded[i][j]);
            }
        }
    }

    print_most_rounded(most_rounded, dim);
}

void extract_factor2_5_0(Cell &cell, int value) {
    while (value % 10 == 0) {
        cell.n2++;
        cell.n5++;
        value /= 10;
    }
    while (value % 2 == 0) {
        cell.n2++;
        value /= 2;
    }
    while (value % 5 == 0) {
        cell.n5++;
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
        strcpy(target.cell2.path, bodyu.cell2.path);
        strcat(target.cell2.path, "D");
    } else {
        target.cell2.n2 += bodyl.cell2.n2;
        target.cell2.n5 += bodyl.cell2.n5;
        strcpy(target.cell2.path, bodyl.cell2.path);
        strcat(target.cell2.path, "R");
    }

    if (bodyu.cell5.n5 < bodyl.cell5.n5) {
        target.cell5.n2 += bodyu.cell5.n2;
        target.cell5.n5 += bodyu.cell5.n5;
        strcpy(target.cell5.path, bodyu.cell5.path);
        strcat(target.cell5.path, "D");
    } else {
        target.cell5.n2 += bodyl.cell5.n2;
        target.cell5.n5 += bodyl.cell5.n5;
        strcpy(target.cell5.path, bodyl.cell5.path);
        strcat(target.cell5.path, "R");
//        target.cell5.from = 'R';
    }

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
        cout << zero2 << endl << game[size-1][size-1].cell2.path << endl;
    } else {
        cout << zero5 << endl << game[size-1][size-1].cell5.path << endl;
    }
}