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

void add_holes(set<int> &holes, unsigned num) {
	int reverse_num = 0, i, temp;
	int num_of_bits = n / 2;
	for (i = 0; i < num_of_bits; i++) {
		temp = (num& (1<<i));
		if (temp) reverse_num |= (1 << ((num_of_bits - 1) - i));
	}
	holes.insert(reverse_num);
	holes.insert(base - 1 - reverse_num);
}

void add_holes_odd(set<int> &holes, unsigned num) {
	int reverse_num = 0, i, temp;
	int num_of_bits = n / 2;
	unsigned num2 = num;
	num >>= 1;
	for (i = 0; i < num_of_bits; i++) {
		temp = (num& (1<<i));
		if (temp) reverse_num |= (1 << ((num_of_bits - 1) - i));
	}
	if (num2 & 1) {
		holes.insert(reverse_num);	
	} else {
		holes.insert(base - 1 - reverse_num);
	}
}


int main(void) {
	// cin >> n >> k;
	n = 49, k = 40394027154620;

	state = vector<int>(n, 0);
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

	long long start = base - 1;
	int i = 0;
	for (; i < base / factor; i++) {
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
		start -= (base - factor*i);
		count = start;
		int j = (n-1) / 2;
		int num_i = i;
		while (i != 0) {
			state[j--] = i % 2;
			i /= 2;
		}

		set<int> holes;
		map<int, int> holes_w_i;

		if (n&1) {
			count = k - count - 1;
			for (unsigned int j = 0; j < num_i; j++) {
				add_holes_odd(holes, j);
			}
		} else {
			count = k - count;	
			for (unsigned int j = 1; j < num_i; j++) {
				add_holes(holes, j);
			}
		}

		j = 1;
		holes_w_i.insert(make_pair(-1, 0));
		set<int>::iterator itr = holes.begin();
		while(itr != holes.end()) {
			holes_w_i.insert(make_pair(*itr, j++));
			holes.erase(itr++);
		}

		int previous = -1;
		map<int, int>::iterator itrl = --holes_w_i.upper_bound(count);
		while (itrl != holes_w_i.end() && itrl->first != previous) {
			count += itrl->second - holes_w_i[previous];
			previous = itrl->first;
			itrl = --holes_w_i.upper_bound(count);
		}

		j = n - 1;
		while (count != 0) {
			if (count&1) state[j] = 1;
			j--;
			count >>= 1;
		}
	}

	for (int i = 0; i < n; i++) cout << state[i];
	cout << endl;
	

	// dfs(0);
	// cout << count << endl;
}