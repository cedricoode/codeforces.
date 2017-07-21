#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string stations, mem1, mem2;

// char stations[100005];
// char mem1[102], mem2[102];

int len1, len2, len;

int main(void) {
	cin >> stations >> mem1 >> mem2;

	len1 = mem1.length();
	len2 = mem2.length();
	len = stations.length();

	if (len1+len2 > len) cout << "fantasy" << endl;
	else {
		bool ff = false;
		int pos = stations.find(mem1);
		if (pos != -1) {
			pos = stations.find(mem2, pos+len1);
			if (pos != -1) {
				ff = true;
			}
		}

		reverse(stations.begin(), stations.end());

		pos = stations.find(mem1);
		if (pos != -1) {
			pos = stations.find(mem2, pos+len1);
			if (pos != -1) {
				if (ff) cout << "both" << endl;
				else  cout << "backward" << endl;
			} else {
				if (ff) cout << "forward" << endl;
				else cout << "fantasy" << endl;
			}
		} else {
			if (ff) {
				cout << "forward" << endl;
			} else cout << "fantasy" << endl;
		}

	}
}
