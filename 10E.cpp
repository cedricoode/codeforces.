#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef long long LL;

int n;
int coin[400];

void greedy(int sum, vector<int> &ans) {
	int c = 0;
	while (sum > 0 && c < n) {
		if (sum >= coin[c]) ans[c]++, sum -= coin[c];
		else c++;
	}
}

LL sum(vector<int> &s, int j) {
	LL ans = 0;
	for (int i = 0; i < j; ++i) ans += s[i] * coin[i];
	ans += coin[j] * (s[j] + 1);
	return ans;
}

bool check(vector<int> &ans, vector<int> &grdy, int j) {
	bool valid = true;
	// check coins sum
	int sumg = 0, suma = 1;
	for (int i = 0; i < n; ++i) sumg += grdy[i];
	for (int i = 0; i <= j; ++i) suma += ans[i];
	return suma < sumg;
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> coin[i];
	}

	for (int i = n-1; i > 0; --i) {
		LL smallest = LLONG_MAX;
		for (int j = n-1; j >= i; --j) {
			vector<int> ans(n, 0);
			greedy(coin[i-1]-1, ans);
			int w = sum(ans, j);
			vector<int> grdy(n, 0);
			greedy(w, grdy);
			if (check(ans, grdy, j) && smallest >= w) {
				smallest = w;
			}
		}
		if (smallest != LLONG_MAX) {
			cout << smallest << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}