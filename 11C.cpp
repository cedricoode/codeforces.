#include <iostream>

using namespace std;

int t, n, m;
char matrix[250][250];
bool visited[250][250];

bool findhs(int i, int j) {
	int count = 1;

	bool valid = true;
	while (i + count < n && !visited[i+count][j] && matrix[i+count][j]) {
		if (j > 0 && !matrix[i+count][j-1]) {
			valid = false;
			break;
		}

		if (count > 1 && j < m-1 && !matrix[i+count][j+1]) {
			valid = false;
			break;
		}
		++count;
	}

	if (valid) {

	}

	while (i+count < n && j+count < m && !visited[i+count][j] && !visited[i][j+count] && matrix[i+count][j] && matrix[i][j+count]) {
		visited[i+count][j] = true;
		visited[i][j+count] = true;
		count++;
	}
}

int main(void) {
	int k;
	cin >> k;
	int count = 0;
	for (int i = 0; i < k; ++i) {
		cin >> n >> m;
		for (int i = 0; i < n+2; ++i)
			for (int j = 0; j < m; ++j) visited[i][j] = false;

		for (int i = 1; i <= n; ++i) 
			for (int j = 1; j <= m; ++j)
				cin >> matrix[i][j];
		
		for (int i = 1; i < n-1; ++i) {
			for (int j = 1; j < m-1; ++j) {
				if (!visited[i][j] && matrix[i][j]) {
					bool valid = true;
					if (i > 0 && matrix[i-1][j]) valid = false;
					if (i > 0 && j > 0 && matrix[i-1][j-1]) valid = false;
					if (j > 0 && matrix[i][j-1]) valid = false;
					
					count += findhs(i,j);
					count += findds(i, j); 
				}
			}
		}
	}
}