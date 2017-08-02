// key the number of BST trees of n nodes t(n) = sum(t(i-1) * t(n-i)) i = 1 .. n
#include <iostream>
#include <set>
#include <utility>
#include <iterator>

using namespace std;

typedef long long LL;
typedef set<int> Nums;

LL dp[36][36];
LL total[36];
int n, h;

LL factorial(LL dep) {
	if (dep == 0 || dep == 1) return 1;
	return dep * factorial(dep-1);
}

LL compute_dp(int len, int dep, Nums &nums) {
	if (len == 0 ) return 0;
	else if (dep == 0 || dep == 1) {
		dp[len][dep] = total[len];
		return total[len];
	}

	LL sum = 0;
	LL previous = 0;
	for (Nums::iterator itr = nums.begin(); itr != nums.end(); itr++) {
		int k1 = distance(nums.begin(), itr);
		int k2 = distance(itr, nums.end()) - 1;
		previous = sum;
		if (dep-1 <= k1) {
			if (dp[k1][dep-1]) {
				sum += dp[k1][dep-1] * total[k2];
			}else {
				Nums n1(nums.begin(), itr);
				sum += compute_dp(k1, dep-1, n1) * total[k2];
			}
		} 
		
		if (dp[k2][dep-1] || k2 < dep-1) {
			sum += (total[k1] - dp[k1][dep-1]) * dp[k2][dep-1];
		} else {
			itr++;
			Nums n2(itr, nums.end());
			itr--;
			sum += (total[k1] - dp[k1][dep-1]) * compute_dp(k2, dep-1, n2);
		}
	}
	return dp[len][dep] = sum;
}


int main(void) {
	cin >> n >> h;
	Nums nums;
	total[0] = total[1] = 1;
	for (int i = 2; i <= n; i++) {
		LL sum = 0;
		for (int j = 1; j <= i; j++) {
			sum += total[j-1] * total[i-j];
		}
		total[i] = sum;
	}
	for (int i = 1; i <= n; i++) nums.insert(i);
	cout << compute_dp(n, h, nums) << endl;
}