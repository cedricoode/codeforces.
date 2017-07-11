#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;


typedef vector<int> Node;

bool operator<(Node const&n1, Node const&n2) {
	return n1[0] < n2[0] && n1[1] < n2[1];
}

struct mycompare{
	bool operator()(Node const& n1, Node const& n2) {
		if (n1[0] < n2[0]) {
			return true;
		} else if (n1[0] == n2[0]) {
			return n1[1] < n2[1];
		} else {
			return false;
		}
	}
} comp;

int find_max(vector<Node> &envelopes, Node &node, int end);

void print_max(vector<Node> &envelopes, int k);



int main(void) {
	Node MAX_NODE(5, -1);	
	MAX_NODE[0] = 1e7;
	MAX_NODE[1] = 1e7;
	vector<Node> envelopes;
	
	Node card(5, 0);
	int n;

	cin >> n;
	cin >> card[0] >> card[1];
	card[4] = -1;

	envelopes.push_back(card);

	for (int i = 0; i < n; i++) {
		Node node(5, -1);
		cin >> node[0] >> node[1];
		if (card < node) {
			node[2] = i + 1;
			envelopes.push_back(node);
		}
	}

	sort(envelopes.begin(), envelopes.end(), comp);

	for (int i = 1; i < envelopes.size(); i++) {
		Node &node = envelopes[i];

		int max_i = find_max(envelopes, node, i);
		
		if (max_i != i) {
			node[3] = envelopes[max_i][3] + 1;
			node[4] = max_i;
		}
	}


	int max_i = find_max(envelopes, MAX_NODE, envelopes.size() -1);

	cout << envelopes[max_i][3] << endl;
	if (max_i != 0)
		print_max(envelopes, max_i);

	

	// for (set<Node, mycompare>::iterator i = envelopes.begin(); i != envelopes.end(); i++) {
	// 	Node &node = *i;
	// 	// Find the max to contain
	// 	set<Node, mycompare>::reverse_iterator j(i);
	// 	int max_count = -1;
	// 	set<Node, mycompare>::reverse_iterator max_i(i);
	// 	for (; j != envelopes.rend(); j++) {
	// 		if (*max_i < *j && j[3] > max_count) {
	// 			max_count = j[3];
	// 			max_i = j;
	// 			i[3] = max_i + 1;
	// 			i[4] = envelopes.rend() - max_i - 1;
	// 		}
	// 	}
	// }
}

int find_max(vector<Node> &envelopes, Node &node, int end) {
	int max_count = -1;
	int max_i = end;
	for (int i = end; i > -1; i--) {
		if (envelopes[i] < node && envelopes[i][3] > max_count) {
			max_count = envelopes[i][3];
			max_i = i;
		}
	}
	return max_i;
}

void print_max(vector<Node> &envelopes, int k) {
	if (k <= 0) {
		return;
	}

	int previous = envelopes[k][4];
	print_max(envelopes, previous);
	cout << envelopes[k][2] << " ";
}