// Bits computation in digit form
#include <iostream>
#include <cmath>

using namespace std;

int main(void) {
	int n;
	cin >> n;
	int length = 0;
	int temp = 1;
	while (n >= temp) temp *=10, length++;
	int count = 0;
	count = lround(pow(2, length - 1)) - 1;

	temp = lround(pow(10, length-1));

	int j = 1;
	int t_length = 0;
	while (temp <= n && t_length < length) {
		// cout << temp << endl;
		count++;
		temp += 1;
		int i = temp;
		int r = i % 10;
		int k = 1;
		t_length = 0;
		while(r == 2) {
			t_length++;
			temp -= 2 * k;
			k *= 10;
			temp += k;
			i = temp / k;
			r = i % 10;
		}
	}

	cout << count << endl;
}

