#include <map>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct comp {
	bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
		if (p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second)) {
			return true;
		} else {
			return false;
		}
	}
};

int find_limits(int* circle, map<pair<int, int>, pair<int, int>, comp> &numbers, map<pair<int, int>, pair<int, int>, comp>::iterator const&i);

inline int next_index(int c, int total, int inc);



int main(void) {
	int n;
	cin >> n;
	int *circle = new int[n];
	map<pair<int, int>, pair<int, int>, comp> numbers; // number, <order, left, right>
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		circle[i] = t;
		pair<int, int> key(t, i);
		pair<int, int> look(-1, -1);
		numbers.insert(pair<pair<int, int>, pair<int, int> > (key, look));
	}

	for (map<pair<int, int>, pair<int, int>, comp>::iterator i = numbers.begin(); i != numbers.end(); i++) {
		find_limits(circle, numbers, i);
	}	

	for (map<pair<int, int>, pair<int, int> >::iterator i = numbers.begin(); i != numbers.end(); i++) {
		cout << i->second.first << endl;
	}
}

int find_limits(int* circle, map<pair<int, int>, pair<int, int>, comp> &numbers, map<pair<int, int>, pair<int, int>, comp>::iterator &itr) {
	int total = numbers.size();
	int count = 0;
	// find right biggest
	int curr_i = itr->first.second;
	int curr_v = itr->first.first;
	int next_i = next_index(curr_i, total, 1);
	int next_v = circle[next_i];
	vector<int> same_i;

	if (next_v > curr_v) {
		count++;
		itr->second.second = next_i;
	} else {
		while (next_i != curr_i && next_v <= curr_v) {
			if (next_v == curr_v) {
				same_i.push_back(next_i);
				next_i = next_index(next_i, total, 1);
				next_v = circle[next_i];
			} else { // could be probably merged together;
				next_i = find(numbers, next_v, next_i)->second.second;
				next_v = circle[next_i];
			}
		}

		if (next_i != curr_i) {
			count++;
			for (int i = 0; i < same_i.size(); i++) {
				find(numbers, curr_v, same_i[i])->second.second = next_i;
			}
			itr->second.second = next_i;
		} else {
			for (int i = 0; i <same_i.size(); i++) {
				find(numbers, curr_v, same_i[i])->second.second = same_i[i];
			}
			itr->seoncd.second = curr_i;
		}
		count += (same_i.size() + 1) * same_i.size() / 2;
	}
	// find left biggest
	next_i = next_index(curr_i, total, -1);
	next_v = circle[next_i];
	if (next_v > curr_v) {
		count++;
		itr->second.second = next_i;
	} else {
		while (next_i != curr_i && next_v <= curr_v) {
			if (next_v == curr_v ) {
				if (find(numbers, next_v, next_i)->second.first != -1) {
					same_i.push_back(next_i);
					next_i = next_index(next_i, total, -1);
					next_v = circle[next_i];
				} else {
					break;
				}
			} else {
				next_i = find(numbers, next_v, next_i)->second.first;
				next_v = circle[next_i];
			}
		}
	}
}

inline int next_index(int c, int total, int inc) {
	return (c+inc+total) % total;
}

inline map<pair<int, int>, pair<int, int>, comp>::iterator find(map<pair<int, int>, pair<int, int>, comp> numbers, int value, int index) {
	return numbers.find(pair<int, int>(value, next_i));
}