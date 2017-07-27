// "This answer exceeds memory limit... should be prevented earlier"
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <utility>

using namespace std;


long long n, k;
vector<int> state(0);
vector<int> memory(0);
long long count = 0, target = 0;
long long base;

bool c_b_smaller() {
	long long k = 0, k1 = 0, k2 = 0, k3 = 0;
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



int main(void) {
	cin >> n >> k;

	state = vector<int>(n, 0);


	dfs(0);
	cout << count << endl;
}