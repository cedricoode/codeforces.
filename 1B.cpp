#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

using namespace std;

bool isclassicformat(string ca) {
    int r_i = ca.find('R');
    int c_i = ca.find('C');
    int d = 0;
    for (int i = r_i + 1; i < c_i; i++) {
        if (isdigit(ca[i])) d++;
    }
    return d==0;
}

struct row_col {
	int row;
	int col;
};

int pow(int base, int expo) {
    if (expo == 0) {
        return 1;
    }

    int mult = 1;
    for (int i = 0; i < expo; i++) {
        mult *= base;
    }
    return mult;
}

row_col convert2modern(string classic) {
	int i = 0;
	string c = "";
	while (!isdigit(classic[i])) {
		c += classic[i++];
	}
	string r = classic.substr(i);
	int col = 0;
	for (int j = 0; j < i; j++) {
		col += (classic[j] - 'A' + 1) * pow(26, i - j - 1);
	}
	row_col rc;
	rc.col = col;
	stringstream(r) >> rc.row;
	return rc;
}

string convert2classic(string modern) {
	string::size_type loc = modern.find('C');
	int row, col;
	stringstream(modern.substr(1, loc - 1)) >> row;
	stringstream(modern.substr(loc + 1)) >> col;
    string cols = "";
    while (col != 0) {
        cols = char((col % 26 + 25) % 26 + 'A') + cols;
        if (col % 26 == 0) {
            col = col / 26 - 1;
        } else {
            col /= 26;
        }
    }
    ostringstream os;
    os << cols << row;
    return os.str();
	cout << row << col << endl;
}

int main(void) {
	int casen;
	cin >> casen;
	string ca;
	for (int i = 0; i < casen; i++) {
		cin >> ca;
		if (isclassicformat(ca)) {
			row_col rc = convert2modern(ca);
			cout << 'R' << rc.row << 'C' << rc.col << endl; 
		} else {
			cout << convert2classic(ca) << endl;
		}
	}
}