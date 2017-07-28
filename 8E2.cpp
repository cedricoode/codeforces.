// "This answer exceeds memory limit... should be prevented earlier"
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <utility>

typedef long long LL;
using namespace std;


LL n, k;
vector<int> state(0);
vector<int> memory(0);
LL count = 0, target = 0;
LL base;

bool c_b_smaller() {
	LL k = 0, k1 = 0, k2 = 0, k3 = 0;
	for (int i = 0; i < n; i++) {
		if (state[i]) k = k | 1<<(n-i);
		// reverse
		if (state[i]) k1 = k1 | 1 << (i+1);

		// mutual reverse
		if (!state[i]) k2 = k2 | 1 << (n-i);

		// reverse + mutial reverse
		if (!state[i]) k3 = k3 | 1 << (i+1);
	}

	if (k==0) return true;

	return (k1 < k || k2 < k || k3 < k);
}

void dfs(int l) {
	if (l == n) {
		// output 
		if (c_b_smaller()) {
			
			return;
		} else {
			count++;
			for (int i = 0; i < n; i++) {
				cout << state[i];
			}
			int start = (n-1) / 2 + 1;
			int j = 0;
			for (int i = start; i < n; i++) {
				if (state[i]) j = j | 1 << (n - i -1);
			}
			cout << " " << j;
			cout << endl;
			return;
		}
	}

	dfs(l+1);
	state[l] = 1;
	dfs(l+1);
	state[l] = 0;
}


// in the second half, if i+1 - n-1 are the same as(when reverse or inverse and reverse)
//first half, how does it compare to the first half, whether it's bigger or not;
//rl_compare[i][0] reverse
//rl_compare[i][0] reverse+inverse
bool rl_compare[26][2];

void update_comparison(int start, int end) {
	for (int i = start; i <= end; i++) {
		if (state[i] == state[n-1-i]) {
			if (i == n/2) {
				rl_compare[i-n/2][0] = true;
				rl_compare[i-n/2][1] = state[i] == 0;
			} else {
				rl_compare[i-n/2][0] = rl_compare[i-n/2-1][0];
				rl_compare[i-n/2][1] = state[i] == 0;
			}
		} else if (state[i] > state[n-1-i]) {
			rl_compare[i-n/2][0] = true;
			if (i == n/2) {
				rl_compare[i-n/2][1] = true;
			} else rl_compare[i-n/2][1] = rl_compare[i-n/2-1][1];
		} else {
			rl_compare[i-n/2][0] = false;
			if (i == n/2) rl_compare[i-n/2][1] = true;
			else rl_compare[i-n/2][1] = rl_compare[i-n/2-1][1];
		}
	}
}

int compute_count(int start) {
	int count = 0;
	if (start > n-1) {
		return rl_compare[n-1-n/2][0] && rl_compare[n-1-n/2][1];
	}
	if (start == n-1) {
		if (rl_compare[n-1-n/2][0] && rl_compare[n-1-n/2][1]) count++;
		if (state[0] == 0 && rl_compare[n-1-n/2-1][1]) count++;
		return count;
	}
	count += compute_count(start+1);
	state[start] = 1;
	update_comparison(start, n-1);
	count += compute_count(start+1);
	state[start] = 0;
	update_comparison(start, n-1);
	return count;
}
int solve(int start, int end, LL &left) {
	if (left == 0 || start > end) return n;
	
	for (int i = end+1; i >= start; --i) {
		int count = 0;
		state[i] = 1;
		update_comparison(i, n-1);
		count += compute_count(i+1);
		if (count >= left) {
			return i;
		} else {
			left -= count;
			state[i] = 0;
			update_comparison(i, n-1);
		}
	}
}


int main(void) {
	cin >> n >> k;

	state = vector<int>(n+1, 0);
	base = pow(2, n/2);	

	int factor = 1;
	if (n & 1) { // odd
		factor = 1;
	} else {
		factor = 2;
	}


	if (k > (base + base * (base / factor -1) / 2 - 1)) {
		cout << -1 << endl;
		return 0;
	}

	LL start = base - 1;
	int num_i = 0;
	for (int i = 0; i < base/factor; num_i = ++i) {
		if (k <= start) break;
		else start += (base - factor*(1+i));
	}

	if (k <= base - 1) {
		int i = n - 1;
		while (k != 0) {
			state[i--] = k % 2;
			k /= 2;
		}
	} else {
		start -= (base - factor*num_i);
		int j = (n-1) / 2;
		while (num_i != 0) {
			state[j--] = num_i % 2;
			num_i /= 2;
		}
		for (int i = n/2; i < n; ++i) {
			if (state[n-1-i]) {
				rl_compare[i-n/2][0] = false;
				if (i != n/2) {
					rl_compare[i-n/2][1] = rl_compare[i-n/2-1][1];
				} else {
					if (n & 1) {
						rl_compare[i-n/2][0] = true;
						rl_compare[i-n/2][1] = false;
					} else 
						rl_compare[i-n/2][1] = true;
				}
			} else {
				rl_compare[i-n/2][1] = true;
				if (i != n/2)
					rl_compare[i-n/2][0] = rl_compare[i-n/2-1][0];
				else
					rl_compare[i-n/2][0] = true;
			}
		}

		count = k - start;
		start = n/2;
		while (start < n) {
			start = 1 + solve(start, n-1, count);
		}
	}

	for (int i = 0; i < n; i++) {
		cout << state[i];
	}
	cout << endl;


	// dfs(0);
	// cout << count << endl;
}