#include <iostream>
#include <utility>
#include <set>

using namespace std;

typedef pair<int, int> node;

int main(void) {
	int m, n;
	char c;
	cin >> m >> n >> c;

	char plan[100][100];
	set<char> desks;

	node start(-1, -1), tail(-1, -1);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> plan[i][j];
			if (plan[i][j] == c) {
				if (start.first == -1) {
					start.first = i;
					start.second = j;
				}
				tail.first = i;
				tail.second = j;
			}
		}
	}

	int deputies = 0;
	// upper
	if (start.first > 0) {
		int ind = start.first - 1;
		for (int j = start.second; j <= tail.second; j++) {
			if (plan[ind][j] != '.')
				desks.insert(plan[ind][j]);
		}
	}

	deputies += desks.size();

	// left
	desks.clear();
	if (start.second > 0) {
		int ind = start.second - 1;
		for (int i = start.first; i <= tail.first; i++) {
			if (plan[i][ind] != '.')
				desks.insert(plan[i][ind]);
		}
	}
	deputies += desks.size();

	// right
	desks.clear();
	if (tail.second < n - 1) {
		int ind = tail.second + 1;
		for (int i = start.first; i <= tail.first; i++) {
			if (plan[i][ind] != '.')
				desks.insert(plan[i][ind]);
		}
	}
	deputies += desks.size();

	// down
	desks.clear();
	if (tail.first < m - 1) {
		int ind = tail.first + 1;
		for (int i = start.second; i <= tail.second; i++) {
			if (plan[ind][i] != '.')
				desks.insert(plan[ind][i]);
		}
	}
	deputies += desks.size();

	cout << deputies << endl;

}