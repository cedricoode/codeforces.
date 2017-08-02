#include <iostream>
#include <cmath>

using namespace std;
char seats[101][101];
int n, k;
int rc, cc;
int total, remain;

int remoteness(int row, int cb, int ce) {
	int distance = 0;
	for (int i = cb; i <= ce; ++i) {
		distance += abs(i - cc);
	}
	distance += (ce - cb + 1) * abs(row - rc);
	return distance;
}

int row_seating(int m, int r, int &d) {
	int col = -1, row = rc;
	int mind = 1e7;
	if (seats[r][0] >= m) { 
		for (int i = 1; i <= k+1-m; ++i) {
			if (!seats[r][i]) {
				int j = 1;
				while (j < m && !seats[r][i+j]) j++;
				if (j >= m) {
					int dis = remoteness(r, i, i+m-1);
					if (dis < mind) {
						mind = dis;
						col = i;
					}
				}
			}
		}
	}
	d = mind;
	return col;
}

void seating(int m, int &r, int &c, int &dis) {
	if (remain < m) return;

	int offs = 1;
	int sum = 0;
	
	int col = -1, row = rc;
	int mind = 1e7;
	col = row_seating(m, rc, mind);
	for (int i = 1; i <= (k-1)/2; ++i) {
		// to screen
		int d;
		int newcol = row_seating(m, rc - i, d);
		if (d < mind || (d == mind && rc - i < row)) {
			mind = d;
			row = rc - i;
			col = newcol;
		} 

		// to back
		newcol = row_seating(m, rc + i, d);
		if (d < mind) {
			mind = d;
			row = rc + i;
			col = newcol;
		}
	}

	if (col != -1) {
		total -= m;
		seats[row][0] -= m;
		r = row;
		c = col;
		dis = mind;
		for (int i = col; i < col + m; i++) {
			seats[row][i] = true;
		}
	}
}


int main(void) {
	cin >> n >> k;
	for (int i = 0; i < k+1; i++) {
		seats[i][0] = k;
	}
	rc = cc = k / 2 + 1;
	total = k * k;
	remain = k * k;
	for (int i = 0; i < n; ++i) {
		int m;
		cin >> m;
		int col = -1, row = -1, dis = 1e7;
		seating(m, row, col, dis);
		if (col != -1) {
			cout << row << " " << col << " " << (col + m - 1) << endl;
		} else cout << -1 << endl;
	}
}