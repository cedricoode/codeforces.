#include <iostream>

using namespace std;

void next_index(int &, int &, int &);

int main(void) {
	int edges[4];
	cin >> edges[0] >> edges[1] >> edges[2] >> edges[3];

	for (int i = 0; i < 3; i++) {
		int ind = 0;
		for (int j = 1; j < 4 - i; j++) {
			if (edges[ind] > edges[j]) {
				int temp = edges[j];
				edges[j] = edges[ind];
				edges[ind] = temp; 
			}
			ind = j;
		}
	}

	// 4 cases
	int a = 0, b = 1, c = 2;
	int cases = 0;
	int find = false;
	int degenerate = false;
	while (cases < 4) {
		if (edges[a] +edges[b] > edges[c]) {
			if (edges[b] - edges[a] < edges[c]) {
				find = true;
				break;
			}
		} else if (edges[a] + edges[b] == edges[c]) {
			degenerate = true;
		}
		next_index(a, b, c);
		cases++;
	}

	if (find) {
		cout << "TRIANGLE" << endl;
	} else if (degenerate) {
		cout << "SEGMENT" << endl;
	} else 
		cout << "IMPOSSIBLE" << endl;
}

void next_index(int &a, int&b, int &c) {
	if (c == 4 - 1) {
		if (b == 4 - 2) {
			++a;
		} else {
			++b;
		}
	} else {
		++c;
	}
}