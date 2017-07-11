#include <iostream>
#include <utility>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef pair<int, int> Node;

struct mycompare {
	bool operator()(const pair<Node, int> &p1,const pair<Node, int> &p2) {
		if (p1.first.first < p2.first.first) { 
			return true;
		} else if (p1.first.first == p2.first.first) {
			return p1.first.second < p2.first.second;
		} else {
			return false;
		}
	}
};

// struct dpcompare {
// 	bool operator()(const Node &n1, const Node &n2) {
// 		if (n1.first < n2.first) {
// 			return true;
// 		} else if (n1.first == n2.first) {
// 			return n1.second < n2.second;
// 		} else {
// 			return false;
// 		}
// 	}
// }
void print_chain(vector<Node> &dp, set<pair<Node, int>, mycompare > &envelopes, int i);

void compute_l_chain(vector<Node> &dp, pair<Node, int> const&n, set<pair<Node, int>, mycompare> &envelopes);

int find_max(vector<Node> &dp, Node const&n, set<pair<Node, int>, mycompare> &envelopes);

set<pair<Node, int>, mycompare>::iterator moveto (set<pair<Node, int>, mycompare>::iterator i, int k);

bool operator<(Node &n1, Node &n2){
	return n1.first < n2.first && n1.second < n2.second;
}

int main(void) {
	int n;
	cin >> n;
	Node node;
	cin >> node.first >> node.second;

	int tw, th;
	vector<Node> dp; // <count, previous_order);
	// dp.push_back(pair<int, int>(0, -1));
	set<pair<Node, int>, mycompare> envelopes; // <<width, height>, order>

	envelopes.insert(pair<Node, int>(node, 0));
	for (int i = 0; i < n; i++) {
		cin >> tw >> th;
		if (tw > node.first && th > node.second) {
			Node p(tw, th);
			pair<Node, int> envelope(p, i+1);
			envelopes.insert(envelope);
		}
	}

	for (set<pair<Node, int>, mycompare>::iterator i = envelopes.begin(); i != envelopes.end(); i++) {
		compute_l_chain(dp, *i, envelopes);
	}

	int max_i = find_max(dp, Node(1e7, 1e7), envelopes);

	print_chain(dp, envelopes, max_i);	


	// for (set<pair<Node, int>, mycompare>::iterator i = envelopes.begin(); i != envelopes.end(); i++) {
	// 	cout << (*i).first.first << " " << (*i).first.second << endl;
	// }
}

int find_max(vector<Node> &dp, Node const&n, set<pair<Node, int>, mycompare> &envelopes) {
	vector<Node>::reverse_iterator max_i = dp.rbegin();
	int max_count = -1;
	set<pair<Node, int>, mycompare>::iterator itr_begin = envelopes.begin();

	for (vector<Node>::reverse_iterator i = dp.rbegin(); i != dp.rend(); i++) {
		set<pair<Node, int>, mycompare>::iterator itr = moveto(itr_begin, dp.rend() - i - 1);
		if (itr->first < n && i->first > max_count) {
			max_i = i;
			max_count = i->first;
		}
	}
	if (max_i == dp.rend()) {
		return -1;
	} else {
		return dp.rend() - max_i - 1;
	}
}

void compute_l_chain(vector<Node> &dp, pair<Node, int> const&n, set<pair<Node, int>, mycompare> &envelopes) {
	Node node(-1, -1);
	
	int max_i = find_max(dp, n.first, envelopes);

	if (max_i == -1) {
		node.first = 0;
		node.second = -1;
		dp.push_back(node);
	} else {
		node.first = dp[max_i].first + 1;
		node.second = max_i;
		dp.push_back(node);
	}
}


set<pair<Node, int>, mycompare>::iterator moveto (set<pair<Node, int>, mycompare>::iterator i, int k) {
	while (k-- > 0) {
		i++;
	}
	return i;
}
void print_chain(vector<Node> &dp, set<pair<Node, int>, mycompare> &envelopes, int i) {
	if (i == -1) {
		cout << 0 << endl;
	} else {
		cout << dp[i].first << endl;
		set<pair<Node, int>, mycompare>::iterator itr_begin = envelopes.begin();
		stringstream convert;
		while (i != 0 ) {
			set<pair<Node, int>, mycompare>::iterator itr = moveto(itr_begin, i);
			// cout << itr->second << endl;
			convert << itr->second;
			i = dp[i].second;
		}
		string a = convert.str();
		for (string::reverse_iterator i = a.rbegin(); i != a.rend(); i++){
			cout << *i << " ";
		}
		cout << endl;
	}
}