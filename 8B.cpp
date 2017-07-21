#include <iostream>

using namespace std;

char map[202][202];
char path[101];
int len, i, x = 101, y = 101, px = x, py = y;

int main(void) {

	cin >> path;

	while (path[i]) {
		if (map[x][y]) {
			cout << "BUG" << endl;
			return 0;
		}
		map[x][y] = 1;
		bool bug = false;				
		switch(path[i]) {
		case 'L':
			y--;
			if (map[x][y-1] || map[x+1][y] || map[x-1][y]) {
				bug = true;
			}
			break;
		case 'R':
			y++;
			if (map[x][y+1] || map[x+1][y] || map[x-1][y]) {
				bug = true;
			}
			break;
		case 'D':
			x++;
			if (map[x+1][y] || map[x][y-1] || map[x][y+1]) {
				bug = true;
			}
			break;
		case 'U':
			x--;
			if (map[x-1][y] || map[x][y-1] || map[x][y+1]) {
				bug = true;
			}
			break;
		}

		if (bug) {
			cout << "BUG" << endl;
			return 0;
		}
		i++;
	}

	cout << "OK" << endl;

}