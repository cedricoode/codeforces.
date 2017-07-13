#include <map>
#include <iostream>
#include <utility>
#include <set>

using namespace std;

struct mycompare {
	bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
		if (p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second)) {
			return true;
		} else {
			return false;
		}
	}
};

int find_limits(int* circle, map<pair<int, int>, pair<int, int>, mycompare> &numbers, map<pair<int, int>, pair<int, int>, mycompare>::iterator &itr);

inline int next_index(int c, int total, int inc);

inline map<pair<int, int>, pair<int, int>, mycompare>::iterator find(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int value, int index);

int search_side(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int* circle, set<int> &same_i, int direction, int curr_i);



int main(void) {
	int n;
	cin >> n;
	int *circle = new int[n];
	map<pair<int, int>, pair<int, int>, mycompare> numbers; // number, <order, left, right>
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		circle[i] = t;
		pair<int, int> key(t, i);
		pair<int, int> look(-1, -1);
		numbers.insert(pair<pair<int, int>, pair<int, int> > (key, look));
	}

	int count = 0;
	for (map<pair<int, int>, pair<int, int>, mycompare>::iterator i = numbers.begin(); i != numbers.end(); i++) {
		if (i->second.first == -1) {
			// i is not configured
			count += find_limits(circle, numbers, i);
		}
	}
	cout << count << endl;

	// for (map<pair<int, int>, pair<int, int> >::iterator i = numbers.begin(); i != numbers.end(); i++) {
	// 	cout << i->second.first << endl;
	// }
}

int find_limits(int* circle, map<pair<int, int>, pair<int, int>, mycompare> &numbers, map<pair<int, int>, pair<int, int>, mycompare>::iterator &itr) {
	int total = numbers.size();
	int count = 0;
	// find right biggest
	int curr_i = itr->first.second;
	int curr_v = itr->first.first;
	// int next_i = next_index(curr_i, total, 1);
	set<int> same_i;

	bool found_max = false;
	int next_i = search_side(numbers ,circle, same_i, 1, curr_i);
	int next_v = circle[next_i];
	// while (next_i != curr_i && next_v <= curr_v) {
	// 	if (next_v == curr_v) {
	// 		same_i.insert(next_i);
	// 		next_i = next_index(next_i, total, 1);
	// 		next_v = circle[next_i];
	// 	} else { // could be probably merged together;
	// 		next_i = find(numbers, next_v, next_i)->second.second;
	// 		next_v = circle[next_i];
	// 	}
	// }

	if (next_i != curr_i) {
		count++;
		found_max = true;
		itr->second.second = next_i;
	} else {
		itr->second.second = curr_i;
	}
	
	// find left biggest
	int previous_i = next_i;
	next_i = next_index(curr_i, total, -1);
	next_v = circle[next_i];
	next_i = search_side(numbers, circle, same_i, -1, curr_i);
	// while (next_i != curr_i && next_v <= curr_v) {
	// 	if (next_v == curr_v ) {
	// 		// start from the end
	// 		if (same_i.find(next_i) != same_i.end()) {
	// 			// form a circle
	// 			break;
	// 		} else {
	// 			same_i.insert(next_i);
	// 		}
	// 		next_i = next_index(next_i, total, -1);
	// 		next_v = circle[next_i];
	// 	} else {
	// 		next_i = find(numbers, next_v, next_i)->second.first;
	// 		next_v = circle[next_i];
	// 	}
	// }

	if (next_i != curr_i) {
		if (next_v == curr_v) {
			// form a circle
			itr->second.first = curr_i;
		} else {
			itr->second.first = next_i;
			count++;
		}
	} else {
		// form a circle
		itr->second.first = curr_i;
	}

	for (set<int>::iterator i = same_i.begin(); i != same_i.end(); i++) {
		int index = *i;
		map<pair<int, int>, pair<int, int>, mycompare>::iterator curr_itr = 
			find(numbers, circle[index], index);
		if (found_max) {
			curr_itr->second.second = previous_i;
			curr_itr->second.first = next_i;
		} else {
			curr_itr->second.second = curr_itr->first.second;
			curr_itr->second.first = curr_itr->first.second;
		}
	}
	if (previous_i == next_i && next_i != curr_i) {
		count--;
	}
	count += same_i.size() * (same_i.size() + 1) / 2;
	return count;
}

inline int next_index(int c, int total, int inc) {
	return (c+inc+total) % total;
}

inline map<pair<int, int>, pair<int, int>, mycompare>::iterator find(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int value, int index) {
	pair<int, int> key(value, index);
	return numbers.find(key);
}

int search_side(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int* circle, set<int> &same_i, int direction, int curr_i) {
	int total = numbers.size();
	next_i = next_index(curr_i, total, -1);
	next_v = circle[next_i];
	while (next_i != curr_i && next_v <= curr_v) {
		if (next_v == curr_v ) {
			if (!same_i.insert(next).second) {
				return next_i;
			}
			next_i = next_index(next_i, total, direction);
			next_v = circle[next_i];
		} else {
			next_i = find(numbers, next_v, next_i)->second.first;
			next_v = circle[next_i];
		}
	}
	return next_i;
}