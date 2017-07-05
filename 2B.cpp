#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

struct Cell {
    int n2;
    int n5;
    char from;
    char from5;
    int value;
    Cell(): n2(0), n5(0){}
};

struct Coord{
    int i;
    int j;

    Coord():i(-1), j(-1) {}

    Coord(int a, int b): i(a), j(b){}
};

inline void extract_factor2_5_0(int, int&, int&);

inline void merge_body(Cell const &, Cell &);

inline void compare_merge(Cell const &, Cell const &, Cell &);

void print_most_rounded(vector<vector<Cell> > &, vector<Coord> &, int );

int main(void) {
    int dim;
    cin >> dim;
    vector<vector<Cell> > most_rounded;
    most_rounded.resize(dim);
    vector<Coord> zeros;
    int zero[] = {-1, -1};

    for (int i = 0; i < dim; i++) {
        most_rounded[i].resize(dim);
        for (int j = 0; j < dim; j++) {
            Cell &cell = most_rounded[i][j];
            cin >> cell.value;

            int n2=0, n5=0;

            if (cell.value == 0) {
                Coord coord(i, j);
                zeros.push_back(coord);
                cell.value = 10;
            } 
            
            extract_factor2_5_0(cell.value, n2, n5);
            cell.n2 = n2;
            cell.n5 = n5;
            
            if (i == 0) {
                if (j - 1 >= 0) {
                    Cell &cell_before = most_rounded[i][j-1];
                    merge_body(cell_before, cell);
                    cell.from = 'R';
                    cell.from5 = 'R';
                }
            } else if (j == 0){
                Cell &cell_before = most_rounded[i-1][j];
                merge_body(cell_before, cell);
                cell.from ='D';
                cell.from5 ='D';
            } else {
                Cell &cell_u = most_rounded[i-1][j];
                Cell &cell_l = most_rounded[i][j-1];
                compare_merge(cell_u, cell_l, cell);
            }
        }
    }

    print_most_rounded(most_rounded, zeros, dim);
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

void merge_body(Cell const &cell, Cell &target) {
    target.n2 += cell.n2;
    target.n5 += cell.n5;
}

int min(int a, int b) {
    if (a < b) return a;
    else return b;
}

int max(int a, int b) {
    if (a < b) return b;
    else return a;
}


void compare_merge(Cell const &cellu, Cell const &celll, Cell &target) {
    if  (cellu.n2 > celll.n2) {
        target.n2 += celll.n2;
        target.from = 'R';
    } else {
        target.n2 += cellu.n2;
        target.from = 'D';
    }

    if (cellu.n5 > celll.n5) {
        target.n5 += celll.n5;
        target.from5 = 'R';
    } else {
        target.n5 += cellu.n5;
        target.from5 = 'D';
    }
}

void print_path(vector<vector<Cell> > &game, int size, int which) {
    string path = "";
    Cell &cell = game[size-1][size-1];
    int offsetx = 1, offsety = 1;
    if (which == 2) {
        for (int i = 0; i < 2 * size - 2; i++) {
            cell = game[size-offsetx][size-offsety];
            path = cell.from + path;
            if (cell.from == 'R') {
                offsety++;
            } else {
                offsetx++;
            }
        }
    } else {
        for (int i = 0; i < 2 * size - 2; i++) {
            cell = game[size-offsetx][size-offsety];
            path = cell.from5 + path;
            if (cell.from5 == 'R') {
                offsety++;
            } else {
                offsetx++;
            }
        }
    }
    cout << path << endl;
}

void print_random(Coord &coord, int size) {
    string path = "";
    for (int i = 0; i < coord.i; i++) {
        path += 'D'; 
    }
    for (int j = 0; j < coord.j; j++) {
        path += 'R';
    }
    for (int i = coord.i; i < size; i++) {
        path += 'D';
    }
    for (int j = coord.j; j < size; j++) {
        path += 'R';
    }

    cout << path << endl;
}

void print_most_rounded(vector<vector<Cell> > &game, vector<Coord> &zeros, int size) {
    Cell &cell = game[size-1][size-1];
    int which, count;
    if (cell.n2 < cell.n5) {
        count = cell.n2;
        which = 2;
    } else {
        count = cell.n5;
        which = 5;
    }

    if (zeros.size() != 0 && count != 0) {
        cout << 1 << endl;
        print_random(*zeros.begin(), size);
    } else {
        cout << count << endl;
        print_path(game, size, which);
    }
}

