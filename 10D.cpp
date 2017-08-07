#include <iostream>
#include <map>
#include <utility>

using namespace std;

typedef map<int, int> Mem;

int n, m;
Mem mem;
int state[501][501][2];
int seq1[501];
int seq2[501];


int main(void) {
	cin >> n;
	for (int i = 0; i < n; ++i)	cin >> seq1[i];
	cin >> m;
	for (int i = 0; i < m; ++i) cin >> seq2[i];

	state[0][0][0] = -1;
	state[0][0][1] = -1;
	state[1][0][0] = -1;
	state[1][0][1] = -1;
	state[0][1][0] = -1;
	state[0][1][1] = -1;
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < m; ++j) {
			if (i && j) {
				int start = 0;
				if (state[i-1][j][0]) start = state[i-1][]
			}
		}
	}
}