#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

typedef pair<int, int> Node;

struct mycompare {
	bool operator()(const vector<int> &v1, const vector<int> &v2) const {
		for (int i = 0; i < v1.size(); i++) {
			if (v1[i] < v2[i]) {
				return true;
			}
		}
		return false;
	}
};

void attack(map<vector<int>, vector<int>, mycompare> &memory, vector<int> &archers, set<int> &attack_points, vector<int> &attack_order, int a, int b, int n);

int main(void) {
	int n, a, b;

	cin >> n >> a >> b;

	// vector<Node> archers(n, -1);
	vector<int> archers; //value, main cost, collateral cost
	set<int> attack_points;

	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		archers.push_back(temp);
	}

	for (int i = 1; i < n -1; ++i) {
		attack_points.insert(i);
	}

	// extreme archers have no main cost

	vector<int> attack_order;

	map<vector<int>, vector<int>, mycompare> memory;

	

	attack(memory, archers, attack_points, attack_order, a, b, n);

	cout << attack_order.size() << endl;
	for (int i = 0; i < attack_order.size(); i++) {
		cout << attack_order[i] + 1 << " ";
	}
	cout << endl;
}

void attack(map<vector<int>, vector<int>, mycompare> &memory, vector<int> &archers, set<int> &attack_points, vector<int> &attack_order, int a, int b, int n) {
	map<vector<int>, vector<int>, mycompare>::iterator itr = memory.find(archers);
	if (itr != memory.end()) {
		attack_order = itr->second;
		// cout << "found" << endl;
		return;
	}
	if (attack_points.size() == 0) {
		while (archers[0] > -1) {
			archers[1] = archers[1] < a ? -1 : archers[1] - a;
			archers[2] = archers[2] < b ? -1 : archers[2] - b;
			archers[0] = archers[0] < b ? -1 : archers[0] - b;
			attack_order.push_back(0);
		}
		while (archers[n-1] > -1) {
			archers[n-2] = archers[n-2] < a ? -1 : archers[n-2] - a;
			archers[n-1] = archers[n-1] < b ? -1 : archers[n-1] - b;
			archers[n-3] = archers[n-3] < b ? -1 : archers[n-3] - b;
			attack_order.push_back(n-2);
		}
		// for (int i = 0; i < attack_order.size(); i++) {
		// 	cout << attack_order[i] << " ";
		// }
		// cout << endl;
		return;
	}

	vector<vector<int> > new_attack_orders(attack_points.size());

	int min_length = 1000;
	int min_index = -1;
	int i = 0;
	for (set<int>::iterator itr = attack_points.begin(); itr != attack_points.end(); itr++, i++) {
		// attack each point;
		int index = *itr;
		vector<int> remain_archers(archers);
		remain_archers[index] = archers[index] < a ? -1 : archers[index] - a;
		remain_archers[index+1] = archers[index+1] < b ? -1 : archers[index+1] - b;
		remain_archers[index-1] = archers[index-1] < b ? -1 : archers[index-1] - b;

		set<int> remain_attack_points(attack_points);
		new_attack_orders[i] = vector<int>(attack_order);

		int cost = 0;

		cost += remain_archers[index] == -1 ? 0 : 1 + remain_archers[index];
		cost += remain_archers[index+1] == -1 ? 0 : 1 + remain_archers[index+1];
		cost += remain_archers[index-1] == -1 ? 0 : 1 + remain_archers[index-1];

		if (cost == 0 || (remain_archers[index] == -1 && (remain_archers[index-1] == -1 || remain_archers[index+1] == -1))) {
			remain_attack_points.erase(index);
		}
		

		if (index > 1) {
			cost = 0;
			cost += remain_archers[index-2] == -1 ? 0 : 1 + remain_archers[index-2];
			cost += remain_archers[index-1] == -1 ? 0 : 1 + remain_archers[index-1];
			cost += remain_archers[index] == -1 ? 0 : 1 + remain_archers[index];
			if (cost == 0 || (remain_archers[index-1] == -1 && (remain_archers[index-2] == -1 || remain_archers[index] == -1))) {
				remain_attack_points.erase(index-1);
			}

			if (index > 2) {
				cost = 0;
				cost += remain_archers[index-3] == -1 ? 0 : 1 + remain_archers[index-3];
				cost += remain_archers[index-2] == -1 ? 0 : 1 + remain_archers[index-2];
				cost += remain_archers[index-1] == -1 ? 0 : 1 + remain_archers[index-1];
				if (cost == 0 || (remain_archers[index-2] == -1 && (remain_archers[index-3] == -1 || remain_archers[index-1] == -1))) {
					remain_attack_points.erase(index-2);
				}
			}
		}

		if (index < n-2) {
			cost = 0;
			cost += remain_archers[index+2] == -1 ? 0 : 1 + remain_archers[index+2];
			cost += remain_archers[index+1] == -1 ? 0 : 1 + remain_archers[index+1];
			cost += remain_archers[index] == -1 ? 0 : 1 + remain_archers[index];
			if (cost == 0 || (remain_archers[index+1] == -1 && (remain_archers[index+2] == -1 || remain_archers[index] == -1))) {
				remain_attack_points.erase(index+1);
			}

			if (index < n-3) {
				cost = 0;
				cost += remain_archers[index+3] == -1 ? 0 : 1 + remain_archers[index+3];
				cost += remain_archers[index+2] == -1 ? 0 : 1 + remain_archers[index+2];
				cost += remain_archers[index+1] == -1 ? 0 : 1 + remain_archers[index+1];
				if (cost == 0 || (remain_archers[index+2] == -1 && (remain_archers[index+3] == -1 || remain_archers[index+1] == -1))) {
					remain_attack_points.erase(index+2);
				}
			}
		}

		attack(memory, remain_archers, remain_attack_points, new_attack_orders[i], a, b, n);
		memory.insert(pair<vector<int>, int>(remain_archers, new_attack_orders[i].size()));
		new_attack_orders[i].insert(new_attack_orders[i].begin(), index);		
		if (min_length > new_attack_orders[i].size()) {
			min_index = i;
			min_length = new_attack_orders[i].size();
		}
	}

	attack_order = new_attack_orders[min_index];
}
