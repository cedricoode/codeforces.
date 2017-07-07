#include <iostream>
#include <cmath>

using namespace std;

bool is_paralle(int start[], int end[]);

bool move_paralle(int start[], int end[]);

void move_vertex(int start[], int end[]);

int compute_distance(int start[], int end[]);

int main(void) {
	int start[2];
	int end[2];

	char a;
	int b;
	cin >> a >> b;
	start[0] = a - 'a';
	start[1] = b;
	cin >> a>> b;
	end[0] = a - 'a';
	end[1] = b;

	compute_distance(start, end);
	if (is_paralle(start, end)) {
		move_paralle(start, end);
	} else {
		move_vertex(start, end);
		move_paralle(start, end);
	}
}

int sign(int x) {
	return x / abs(x);
}

int compute_distance(int start[], int end[]) {
	int offx = end[0] - start[0];
	int offy = end[1] - start[1];
	int d1 = min(abs(offx), abs(offy));

	int newstart[2] = {start[0] + d1 * sign(offx) , start[1] + d1 * sign(offy)};
	offx = end[0] - newstart[0];
	offy = end[1] - newstart[1];
	int d2 = max(abs(offx), abs(offy));
	cout << d1 + d2 << endl;
}

bool is_paralle(int start[], int end[]) {
	return (start[0] == end[0] || start[1] == end[1]);
}

bool move_paralle(int start[], int end[]) {
	if (start[0] == end[0]) {
		if (start[1] < end[1]) {
			for (int i = 0; i < end[1] - start[1]; i++) {
				cout << 'U' << endl;
			}
		} else {
			for (int i = 0; i < start[1] - end[1]; i++) {
				cout << 'D' << endl;
			}
		}
	} else {
		if (start[0] < end[0]) {
			for (int i = 0; i < (end[0] - start[0]); i++) {
				cout << 'R' << endl;
			}
		} else {
			for (int i = 0; i < start[0] - end[0]; i++) {
				cout << 'L' << endl;
			}
		}
	}
}

void move_vertex(int start[], int end[]) {
	if (is_paralle(start, end)) {
		return;
	}

	if (start[0] > end[0]) {
		cout << 'L';
		start[0] = start[0] - 1;
	} else if (start[0] < end[0]) {
		cout << 'R';
		start[0] = start[0] + 1;
	}

	if (start[1] > end[1]) {
		cout << 'D';
		start[1] = start[1] - 1;		
	} else if (start[1] < end[1]) {
		cout << 'U';
		start[1] = start[1] + 1;		
	}

	cout << endl;
	move_vertex(start, end);
}