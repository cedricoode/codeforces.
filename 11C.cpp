#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int t, n, m;
char matrix[255][255];
bool visited[255][255];
vector<int> points;
void dfs(int x, int y) {
	visited[x][y] = true;
	points.push_back(x*m + y);
	for (int i = -1; i < 2; ++i) 
		for (int j = -1; j < 2; ++j) {
			if (i == 0 && j ==0) continue;
			if (!visited[x+i][y+j] && matrix[i+x][j+y] == '1') dfs(i+x, j+y);
		}
}

bool check() {
	if (points.size() % 4 != 0) return false;
	vector<int> temp(0);
	//check horizontal square
	if (points[1] - points[0] == 1) {
		int count = 0;
		vector<int>::iterator itr = points.begin();
		int prev = *itr - 1;
		int start = prev % m + 1;
		while (*itr - prev == 1 && start+count < m+1) {
			temp.push_back(*itr);
			prev = *itr;
			itr++;
			count++;
		}

		if (points.size() != (count-1) * 4) return false;
		start = points[0];
		for (int i = 1; i < count; ++i) {
			temp.push_back(start + i*m);
			temp.push_back(start+count+i*m-1);
		}
		for (int i = 1; i < count-1; ++i) {
			temp.push_back(start + m*(count-1)+i);
		}

		if (temp.size() != points.size()) return false;
		sort(temp.begin(), temp.end());
		return equal(temp.begin(), temp.end(), points.begin());

	} else { // diagonal square
		int count = 0;
		int start = points[0];
		int prev = start;
		vector<int> temp(0);
		int starti = start / m;
		int startj = start % m || m;
		while ((starti< n + 1 && startj< m + 1) && find(points.begin(), points.end(), prev) != points.end()) {
			temp.push_back(prev);
			if (count > 0) temp.push_back(prev - 2*count);
			count++;
			prev += (m + 1);
		}
		if (points.size() != 4 * (count - 1)) return false;
		int end = start + (count-1) * 2 * m;
		temp.push_back(end);

		for (int i = 1; i < count-1; ++i) {
			temp.push_back(end - i *m + i);
			temp.push_back(end - i *m - i);
		}
		sort(temp.begin(), temp.end());
		return equal(temp.begin(), temp.end(), points.begin());

	}
}

int main(void) {
	int k;
	cin >> k;
	for (int h = 0; h < k; ++h) {
		cin >> n >> m;
		int count = 0;
		for (int i = 0; i < n+2; ++i)
			for (int j = 0; j < m+2; ++j) {
				visited[i][j] = false;
				matrix[i][j] = 0;
			}

		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= m; ++j)
				cin >> matrix[i][j];
		
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < m; ++j) {
				if (!visited[i][j] && matrix[i][j] == '1') {
					points = vector<int>(0);
					dfs(i, j);
					sort(points.begin(), points.end());
					count += check();
				}
			}
		}
		cout << count << endl;
	}
}