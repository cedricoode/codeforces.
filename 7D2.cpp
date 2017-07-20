#include <cstdio>
#include <cstring>

using namespace std;
const int size = 5e6;

char str[size * 2+7];
int p[(size * 2) +7];

int len, ans;

void add_boundaries() {
	for (int i=len-1; i>=0; i--) str[i] = (i&1) ? str[i/2] : '|';
	str[len] = '\0';
}

int manacher() {
	int c = 0, r = 0, m = 0, n = 0;
	 for (int i=1; i<len; i++) {
		if (i>r) p[i] = 0, m = i - 1, n = i + 1;
		else {
			 int i2 = 2 * c - i;
			 if (p[i2]<r-i) m = -1;
			 else n = r+1, m = 2 * i - n, p[i] = r-i;
		}

		while (m>-1 && n < len && str[m] == str[n]) p[i]++, m--, n++;
		
		if ((i+p[i])>r) {
			c = i, r = i + p[i];
			if (i == p[i]) ans += p[i/2] + 1;
		}

	 }
	 return ans;
}

int main(void) {
	scanf("%s", str);
	len = strlen(str) * 2 + 1;
	add_boundaries();
	printf("%d\n", manacher());
}