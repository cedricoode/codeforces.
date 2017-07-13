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

long long find_limits(int* circle, map<pair<int, int>, pair<int, int>, mycompare> &numbers, map<pair<int, int>, pair<int, int>, mycompare>::iterator &itr, set<int> &dups);

inline int next_index(int c, int total, int inc);

inline map<pair<int, int>, pair<int, int>, mycompare>::iterator find(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int value, int index);

int search_side(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int* circle, set<int> &same_i, int direction, int curr_i);

void pair_same_value(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int* circle, set<int> &same_i, int previous_i, int next_i, bool found_max);

int search_dup(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int *circle, int direction, int index);



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
	set<int> duplicate_values;

	long long count = 0;

	int max_value = numbers.rbegin()->first.first;
	long long max_value_count = 0;

	for(map<pair<int, int>, pair<int, int>, mycompare>::reverse_iterator i = numbers.rbegin(); i != numbers.rend(); i++) {
		if (i->first.first != max_value) {
			break;
		}
		i->second.first = i->first.second;
		i->second.second = i->first.second;
		max_value_count++;
	}

	count = (max_value_count-1) * max_value_count /2;
	
	for (map<pair<int, int>, pair<int, int>, mycompare>::iterator i = numbers.begin(); i != numbers.end(); i++) {
		if (i->second.first == -1) {
			// i is not configured
			count += find_limits(circle, numbers, i, duplicate_values);
		}
	}

	// for (set<int>::iterator i = duplicate_values.begin(); i != duplicate_values.end(); i++) {
	// 	int previous_i = numbers[pair<int, int>(circle[*i], *i)].second;
	// 	int next_i = numbers[pair<int, int>(circle[*i], *i)].first;
	// 	int n_dup1 = 0, n_dup2 = 0;
	// 	if (duplicate_values.count(previous_i) > 0 || (max_value_count>1 && circle[previous_i] == max_value)) {
	// 		// find number of duplications.
	// 		if (circle[previous_i] == max_value) {
	// 			n_dup1 = max_value_count;
	// 		} else {
	// 			n_dup1 = search_dup(numbers, circle, 1, previous_i);
	// 		}
	// 	}

	// 	if (duplicate_values.count(next_i) > 0 || (max_value_count>1 && circle[next_i] == max_value)) {
	// 		int n_dup = 0;
	// 		if (circle[next_i] == max_value) {
	// 			n_dup2 = max_value_count;
	// 		} else {
	// 			n_dup2 = search_dup(numbers, circle, -1, next_i);
	// 		}
	// 	}

	// 	int dup = n_dup1 + n_dup2;
	// 	if (circle[previous_i] == max_value && circle[next_i] == max_value) {
	// 		dup -= n_dup1;
	// 	}

	// 	count = count + (dup-2) * search_dup(numbers, circle, 1, *i);

	// }
	
	cout << count << endl;

	// for (map<pair<int, int>, pair<int, int> >::iterator i = numbers.begin(); i != numbers.end(); i++) {
	// 	cout << i->second.first << endl;
	// }
}

long long find_limits(int* circle, map<pair<int, int>, pair<int, int>, mycompare> &numbers, map<pair<int, int>, pair<int, int>, mycompare>::iterator &itr, set<int> &dups) {
	int total = numbers.size();
	long long count = 0;
	int curr_i = itr->first.second;
	int curr_v = itr->first.first;
	set<int> same_i;

	int next_i = search_side(numbers ,circle, same_i, 1, curr_i);
	int next_v = circle[next_i];

	itr->second.second = next_i;
	
	// find left biggest
	int previous_i = next_i;
	next_i = search_side(numbers, circle, same_i, -1, curr_i);	
	next_v = circle[next_i];
	itr->second.first = next_i;
	pair_same_value(numbers, circle, same_i, previous_i, next_i, true);
	if (previous_i == next_i && next_i != curr_i) {
		count--;
	}
	count += same_i.size() * (same_i.size() + 1) / 2;
	count += (same_i.size() + 1)*2;
	if (same_i.size() > 0) {
		dups.insert(curr_i);
	}
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
	int curr_v = circle[curr_i];
	int next_i = next_index(curr_i, total, direction);
	int next_v = circle[next_i];
	while (next_i != curr_i && next_v <= curr_v) {
		if (next_v == curr_v ) {
			if (!same_i.insert(next_i).second) {
				return next_i;
			}
			next_i = next_index(next_i, total, direction);
			next_v = circle[next_i];
		} else {
			if (direction == -1) {
				next_i = find(numbers, next_v, next_i)->second.first;
			} else{
				next_i = find(numbers, next_v, next_i)->second.second;
			}
			next_v = circle[next_i];
		}
	}
	return next_i;
}

void pair_same_value(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int* circle, set<int> &same_i, int previous_i, int next_i, bool found_max) {
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
}

// void extend_range(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int* circle, int &i , int&j) {
// 	map<pair<int, int>, pair<int, int> >::iterator i = find(numbers, circle[i], i);
// 	int offset_i = 0, offset_j = 0;
// 	while ((i-offset_i) >= numbers.begin() && (i-offset_i++)->first.first == circle[i]);
// 	while ((i+offset_j) < numbers.end() && (i+offset_j++)->first.first == circle[i]);
// 	i = offset_i;
// 	j = offset_j;
// }

int search_dup(map<pair<int, int>, pair<int, int>, mycompare> &numbers, int *circle, int direction, int index) {
	int value = circle[index];
	int next_i = -1;
	map<pair<int, int>, pair<int, int>, mycompare>::iterator i = find(numbers, value, index), j;	
	int count = 0;
	
	if (direction == 1) {
		next_i = numbers[pair<int, int>(value, index)].second;
		j = i;
		while (j->first.first == value && j->second.second == next_i) {
			count++;
			j++;
		}
		int not_count = 0;
		j = i;
		if (next_i < index) {
			j--;
			while(j->first.first == value) {
				count++;
				j--;
				if (j->second.second != next_i) {
					not_count++;
				}
				j--;
			}
		}

		count -= not_count;
	} else {
		next_i = numbers[pair<int, int>(value, index)].first;
		j = i;
		while(j->first.first == value && i->second.first == next_i) {
			count++;
			j--;
		}

		int not_count = 0;
		j = i;
		if (next_i > index) {
			j++;
			while(j->first.first == value) {
				count++;
				j++;
				if (j->second.first != next_i) {
					not_count++;
				}
				j++;
			}
		}
		count -= not_count;
	}
	return count;
}

