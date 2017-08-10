#include <iostream>
#include <cmath>

using namespace std;

typedef long long LL;

int main(void) {
	int n;
	cin >> n;
	LL max = 0;
	LL count = 0;
	n = abs(n);
	while (n > max || (n + max) & 1) {
		count++;		
		max += count;
	}
	cout  << count <<  endl;
}