// This is a very simple question as long as one realise how to solve it......
#include <iostream>

using namespace std;

int mem[10];
int n;
long long ans;

int main(void) {
	cin >> n;
	for (int i = 1; i <= n; ++i) mem[i%9]++, ans -= n / i;
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) {
		  ans += 1ll * mem[i] * mem[j] * mem[i*j % 9];
		}
	cout << ans << endl;
}