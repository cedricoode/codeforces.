#include <iostream>
#include <map>
#include <utility>
#include <set>

using namespace std;

int next_index(int, int index, int dir);

typedef pair<int, int> Node;

struct mycompare {
	bool operator()(const Node &p1, const Node &p2){
		if (p1.first < p2.first || (p1.first == p2.first && p1.second < p2.second)) {
			return true;
		} else {
			return false;
		}
	}
};



int main(void) {
	int total;
	cin >> total;
	int max_v = -1;
	int max_i = -1;
	long long max_count = 0;
	int *a = new int[1000000];	
	int **lr = new int*[2];
	map<Node, Node, mycompare> numbers;

	lr[0] = new int[1000000];
	lr[1] = new int[1000000];
	for (int i = 0; i < total; i++) {
		cin >> a[i];
		if (a[i] > max_v) {
			max_v = a[i];
			max_i = i;
			max_count = 1;
		} else if (a[i] == max_v) {
			max_count++;
		}
		lr[0][i] = -1;
		lr[1][i] = -1;

		Node node(-1, -1), key(a[i], i);
		numbers.insert(pair<Node, Node>(key, node));
	}


	set<int> same_i;

	long long total_count = 0;
	map<Node, Node, mycompare>::iterator i = numbers.begin();
	for (; i != numbers.end(); i++) {
		if (i->first.first == max_v || i->second.first != -1) {
			continue;
		}

		int index = i->first.second;
		same_i.clear();
		same_i.insert(index);
		int same_count = 1;
		int right = next_index(total, index, 1);
		int left = next_index(total, index, -1);

		while(a[right] <= a[index]) {
			if (a[right] == a[index]) {
				same_i.insert(right);
				right = next_index(total, right, 1);
				same_count++;
			} else {
				right = numbers[Node(a[right], right)].second;
			}
		}

		while(a[left] <= a[index]) {
			if (a[left] == a[index]) {
				same_i.insert(left);
				left = next_index(total, left, -1);
				same_count++;
			} else {
				left = numbers[Node(a[left], left)].first;
			}
		}

		if (same_count >= 1) {
			for (set<int>::iterator j = same_i.begin(); j != same_i.end(); j++) {
				numbers[Node(a[*j], *j)].first = left;
				numbers[Node(a[*j], *j)].second = right;
			}
		}

		total_count += (same_count * 2 + (same_count-1) * same_count / 2);
		if (left == right) {
			total_count -= same_count;	
		}
		
	}

	total_count += (max_count * (max_count - 1) / 2);
	cout << total_count << endl;
}

int next_index(int total, int index, int dir) {
	return (index+dir+total) % total;
}