#include <string>
#include <vector>
#include <iostream>

using namespace std;


void find_max_interval(vector<pair<int, int> > intervals);


int main(void) {
	string brackets;
	vector<pair<int, int> > intervals;// <start with 0 end with zero>
	getline(cin, brackets);

	int i = 0;
	int len = brackets.length();
	while (i < len) {
		pair<int, int> node;
		int idx = i;
		
		while (brackets[idx] != '(' && idx++ < len);
		if (idx >= len) break; 
		
		node.first = idx;
		int accu = 0;

		int zero_idx = -1;
		while (accu >= 0 && idx < len) {
			if (brackets[idx] == '(') {
				accu++;
			} else {
				accu--;
			}

			if (accu == 0) {
				zero_idx = idx;
			}

			if (accu < 0) {
				break;
			}
			idx++;
		}
		if (accu > 0 && zero_idx == -1) {
			i++;
			continue;
		};
		if (zero_idx != -1) {
			node.second = zero_idx;
			i = zero_idx + 1;
		} else {
			node.second = idx - 1;
			i = idx;
		}
		intervals.push_back(node);
	}

	find_max_interval(intervals);
}

void find_max_interval(vector<pair<int, int> > intervals) {
	int max = 0;
	int accu = 1;
	for (int i = 0; i < intervals.size(); i++) {
		int length = intervals[i].second - intervals[i].first + 1;
		if (max < length) {
			accu = 1;
			max = length;
		} else if (max == length) {
			accu++;
		}
	}
	cout << max << " " << accu << endl;
}