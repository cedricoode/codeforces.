// Longest common increasing sequence
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int n1, n2;
int seq1[501], seq2[501];
int dp[501][2]; // first, second, len
typedef long long LL;

int LCIS() {
	for (int i = 0; i < n1; ++i) {
		int maxlen = 0; // maxlen of dj's prefix
		int maxj = -1;
		for (int j = 0; j < n2; ++j) {
			if (seq1[i] == seq2[j]) {
				dp[j][0] = maxlen + 1;
				dp[j][1] = maxj;
			} else if (seq1[i] > seq2[j]) {
				if (dp[j][0] > maxlen) {
					maxlen = dp[j][0];
					maxj = j;
				}
			}
		} 
	}

	int maxlen = 0, maxi = -1;
	for (int i = 0; i < n2; ++i) {
		if (dp[i][0] > maxlen) {
			maxlen = dp[i][0];
			maxi = i;
		}
	}
	return maxi;
}

int main(void) {
	cin >> n1;
	for (int i = 0; i < n1; ++i)
		cin >> seq1[i];

	cin >> n2;
	for (int i = 0; i < n2; ++i)
		cin >> seq2[i];

	int maxi = LCIS();
	int len = dp[maxi][0];
	cout << len << endl;
	vector<int> str;
	if (len) {
		while(dp[maxi][1] != -1) {
			str.push_back(seq2[maxi]);
			maxi = dp[maxi][1];
		}

		str.push_back(seq2[maxi]);

		for (int i = str.size() - 1; i >= 0; --i) {
			cout << str[i] << " ";
		}
	}
	cout << endl;
}