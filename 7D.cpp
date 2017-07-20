#include <cstdio>

using namespace std;

char palindrome[6000005];

int dp[6000005], acc = 1, p = 13, hr, hl, i, ans;

// This is not a absolutely right answer, actualy the formula is correct in the sense that it is only a necessary condition. not a sufficient condition.
int main(void) {
	gets(palindrome);
	for (;palindrome[i]; i++) {
		hr = hr * p + palindrome[i];
		hl += palindrome[i] * acc;
		acc *= p;		
		dp[i+1] = hr == hl ? dp[(i+1) / 2] + 1 : 0;
		ans += dp[i+1]; 
	}
	printf("%d\n", ans);
}
