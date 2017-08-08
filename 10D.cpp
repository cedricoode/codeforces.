#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int n1, n2;
int seq1[501], seq2[501];
int dp[501][501][3]; // first, second, len
typedef long long LL;

int find(char c, int pos, int n, int seq[])
{
	for (int i = 0; i < n; ++i)
	{
		if (c == seq[pos + i])
			return i + pos;
	}
	return -1;
}

vector<int> LCS(int n, int m)
{
	if (dp[n][m][0] || dp[n][m][1] || !(dp[n][m][0] || dp[n][m][1] || dp[n][m][2] == 0)) {
		vector<int> r(3, 0);
		r[0] = dp[n][m][0];
		r[1] = dp[n][m][1];
		r[2] = dp[n][m][2];
		return r;
	}
	// cout << n << " " << m << endl;
	if (n == 0)
	{
		int pos = find(seq1[0], 0, m + 1, seq2);
		vector<int> r(3, 0);
		if (pos != -1) {
			dp[n][m][0] = 0;
			dp[n][m][1] = pos;
			dp[n][m][2] = 1;
			dp[0][pos][0] = 0;
			dp[0][pos][1] = pos;
			dp[0][pos][2] = 1;
			r[0] = 0;
			r[1] = pos;
			r[2] = 1;
		} else {
			dp[n][m][0] = -1;
			dp[n][m][1] = -1;
			dp[n][m][2] = 0;
			dp[pos][0][0] = pos;
			dp[pos][0][1] = 0;
			dp[pos][0][2] = 1;
			r[0] = -1;
			r[1] = -1;
			r[2] = 0;
		}
		return r;
	}
	else if (m == 0)
	{
		int pos = find(seq2[0], 0, n + 1, seq1);
		vector<int> r(3, 0);
		if (pos != -1) {
			dp[n][m][0] = pos;
			dp[n][m][1] = 0;
			dp[n][m][2] = 1;
			r[0] = pos;
			r[1] = 0;
			r[2] = 1;
		} else {
			dp[n][m][0] = -1;
			dp[n][m][1] = -1;
			dp[n][m][2] = 0;			
			r[0] = -1;
			r[1] = -1;
			r[2] = -1;
		}
		return r;
	}

	if (seq1[n] == seq2[m])
	{
		dp[n][m][0] = n;
		dp[n][m][1] = m;
		vector<int> t =  LCS(n - 1, m - 1);
		dp[n][m][2] = 1 + t[2];
		vector<int> r(3, 0);
		r[0] = n, r[1] = m, r[2] = 1 + t[2];
		return r;		
	}
	else
	{
		vector<int> r1 = LCS(n-1, m);
		vector<int> r2 = LCS(n, m-1);
		if (r1[2] >= r2[2]) {
			dp[n][m][0] = r1[0];
			dp[n][m][1] = r1[1];
			dp[n][m][2] = r1[2];
			return r1;
		} else {
			dp[n][m][0] = r2[0];
			dp[n][m][1] = r2[1];
			dp[n][m][2] = r2[2];
			return r2;
		}
	}
}

int main(void)
{
	cin >> n1;
	for (int i = 0; i < n1; ++i)
		cin >> seq1[i];

	cin >> n2;
	for (int i = 0; i < n2; ++i)
		cin >> seq2[i];

	
	vector<int> r = LCS(n1 - 1, n2 - 1);

	int len = r[2];
	int x = r[0], y = r[1];
	vector<int> str;
	while (len) {
		if (dp[x][y][0] == x && dp[x][y][1] == y) {
			str.push_back(seq1[x]);
			x = x - 1;
			y = y - 1;
			len = dp[x][y][2];
		} else {
			x = dp[x][y][0];
			y = dp[x][y][1];
		}
	}


	int end = 0;
	if (str.size() == n1 || str.size() == n2) {
		end = 1;
		cout << (str.size() - 1) << endl;
	} else 
		cout << str.size() << endl;
	for (int i = str.size() - 1; i >= end; --i)
		cout << str[i] << " ";
	cout << endl;
}