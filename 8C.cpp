#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int maxn = 24;

int pts[maxn+5][3];
vector<int> dp((1<<maxn)+10, INT_MAX);
int seq[((1<<maxn)+10)][3];
int n;

int dist(int x[], int y[]) {
	return (x[0] - y[0]) * (x[0] - y[0]) + (x[1] - y[1]) * (x[1] - y[1]);
}

int main(void) {
	cin >> pts[0][0] >> pts[0][1];
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> pts[i][0] >> pts[i][1];
		pts[i][2] = dist(pts[i], pts[0]);
	}

	dp[0] = 0;
	for (int i = 1; i < (1<<n); i++) {
		for (int j = 0; j < n; j++) {
			if (i&(1<<j)) {
				int temp = dp[i^(1<<j)] + 2 * pts[j+1][2];
				if (temp < dp[i]) {
					dp[i] = temp;
					seq[i][0] = 1;
					seq[i][1] = j;
				}

				for (int k = 0; k < n; k++) {
					if (k!=j && (i&(1<<k))) {
						int temp = dp[i^(1<<k)^(1<<j)] + dist(pts[j+1], pts[k+1]) + pts[j+1][2] + pts[k+1][2];
						if (temp < dp[i]) {
							dp[i] = temp;
							seq[i][0] = 0;
							seq[i][1] = j;
							seq[i][2] = k;
						}
					}
				}
				break;
			}
		} 	
	}

	int i = (1 << n) - 1;
	cout << dp[i] << endl;
	while (i != 0) {
		if (seq[i][0]) {
			cout << 0 << " " << seq[i][1]+1 << " ";
			i ^= (1<<seq[i][1]);
		} else {
			cout << 0 << " " << seq[i][1]+1 << " " << seq[i][2]+1 << " ";
			i ^= (1<<seq[i][1]|1<<seq[i][2]);
		}
	}
	cout << 0 << endl;
}