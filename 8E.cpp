#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int n, k;
vector<int> state(0);
vector<int> memory(0);
int count = 0, target = 0;


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
		} else {
			count++;
			
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

	// int factor = 1;
	// if (n & 1) { // odd
	// 	factor = 1;
	// } else {
	// 	factor = 2;
	// }

	// long long base = pow(2, n/2);

	// if (k > (base + base * (base / factor -1) / 2 - 1)) {
	// 	cout << -1 << endl;
	// 	return 0;
	// }

	// long long start = base - 1;
	// int i = 0;
	// for (; i < base / factor; i++) {
	// 	if (k <= start) break;
	// 	else start += (base - factor*(1+i));
	// }

	// if (k <= base - 1) {
	// 	int i = n - 1;
	// 	while (k != 0) {
	// 		state[i--] = k % 2;
	// 		k /= 2;
	// 	}
	// } else {
	// 	start -= (base - factor*i);
	// 	count = start;
	// 	int j = (n-1) / 2;
	// 	while (i != 0) {
	// 		state[j--] = i % 2;
	// 		i /= 2;
	// 	}

	// 	int numi = 0;
	// 	while (count != k) {
	// 		i = numi++;
	// 		int j;
	// 		for (j = (n-1) / 2 + 1; j < n; j++) state[j] = 0;
	// 		j = n - 1;
	// 		while (i != 0) {
	// 			state[j--] = i % 2;
	// 			i /= 2;
	// 		}
	// 		if (!c_b_smaller()) count++;
	// 	}

	// 	// dfs(n/2);
		
	// }

	// for (int i = 0; i < n; i++) cout << state[i];
	// cout << endl;
	
	// cout << (base + base* (base / factor - 1) / 2 - 1) << endl;

	dfs(0);
	cout << count << endl;
}