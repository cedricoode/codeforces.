#include <iostream>

using namespace std;

void dfs(int pos, int current, int pre, int post, int count);



int h[15];
int n, a, b;
int ans = 1e9;
int path[160];
int tpath[160];

int main(void) {
	cin >> n >> a >> b;
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}
	int current = h[1];
	int pre = h[0];
	int post = h[2];
	dfs(1, current, pre, post, 0);

	cout << ans << endl;
	for (int i = 0; i < ans; i++) {
		cout << path[i] + 1 << " ";
	}
	cout << endl;
}

void dfs(int pos, int current, int pre, int post, int count) {
	if (pos == n-1) {
		while (current > -1) {
			tpath[count++] = n-2;
			current -= b;
		}

		if (count < ans) {
			for (int i = 0; i < count; i++) {
				path[i] = tpath[i];
			}
			ans = count;
		}
		return;
	}

	if (pre > -1) {
		int t = pre / b + 1;
		for (int i = 0; i < t; i++) {
			tpath[count++] = pos;
		}
		pre -= t*b;
		current -= t*a;
		post -= t*b;
	}

	int t = current > -1 ? current / a + 1 : 0;
	for (int i = 0; i <= t; i++) {
		for (int j = 0; j < i; j++) {
			tpath[count+j] = pos;
		}
		dfs(pos+1, post-b*i, current-a*i, h[pos+2], count+i);
	}

}