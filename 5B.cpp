#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;


int main(void) {
	string inputs[1001];
	int idx = 0;
	int max_len = 0;
	while (getline(cin, inputs[idx])) {
		if (inputs[idx].length() > max_len) {
			max_len = inputs[idx].length();
		}
		idx++;
	}

	cout << setfill('*') << setw(max_len + 2) << "" <<  endl;
	int inbalance = 0;
	for (int i = 0; i < idx; i++) {
		int length = inputs[i].length();
		int l1 = (max_len - length) / 2;
		int l2 = l1;
		if (l1 + l2 + length != max_len) {
			if (inbalance == 0) {
				l2++;			
			} else if (inbalance > 0) {
				l1++;
			} else {
				l2++;
			}
		}
		inbalance += (l2 - l1);
		cout << '*' << setfill(' ') << right << setw(l1+length) << inputs[i] << setw(l2) << "" << '*' << endl;
	}
	cout << setfill('*') << setw(max_len + 2) << "" <<  endl;	
}