#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

typedef pair<int, int> Node;

class mycompare {
	public:
	bool operator()(const Node &n1, const Node& n2) const{
		return (n1.first < n2.first || (n1.first == n2.first && n1.second < n2.second));
	}
};

int update(map<Node, int, mycompare> &nums, int archers[][3], int a, int b, int index, bool ismain, int n);


int main(void) {
	int n, a, b;
	map<Node, int, mycompare> nums;

	cin >> n >> a >> b;

	// vector<Node> archers(n, -1);
	int archers[10][4]; //value, main cost, collateral cost

	for (int i = 0; i < n; i++) {
		cin >> archers[i][0];
		archers[i][1] = archers[i][0] < a ? archers[i][0] + 1: a;
		archers[i][2] = archers[i][0] < b ? archers[i][0] + 1: b;
	}

	// extreme archers have no main cost
	archers[0][1] = -1;
	archers[n-1][1] = -1;

	for (int i = 1; i < n-1; i++) {
		int cost = archers[i][1] + archers[i-1][2] + archers[i+1][2];
		archers[i][3] = cost;
		Node node(-1, -1);
		node.first = cost;
		node.second = i;
		nums.insert(pair<Node, int>(node, archers[i][0]));
	}

	vector<int> attack;
	while (nums.size() > 0) {
		map<Node, int, mycompare>::reverse_iterator last = nums.rbegin();
		int index = last->first.second;
		attack.push_back(index + 1);
		if (archers[index][0] > -1) {
			archers[index][0] -= archers[index][1];
			if (archers[index][0] < 0) {
				archers[index][0] = -1;
			}
			archers[index][1] = archers[index][0] < a ? archers[index][0] + 1: a;
			archers[index][2] = archers[index][0] < b ? archers[index][0] + 1: b;
		}

		if (archers[index+1][0] > -1) {
			archers[index+1][0] -= archers[index+1][2];
			if (archers[index+1][0] < 0) {
				archers[index+1][0] = -1;
			}		
			archers[index+1][1] = archers[index+1][0] < a ? archers[index+1][0] + 1: a;
			archers[index+1][2] = archers[index+1][0] < b ? archers[index+1][0] + 1: b;
		}
		if (archers[index-1][0] > -1) {
			archers[index-1][0] -= archers[index-1][2];
			if (archers[index-1][0] < 0) {
				archers[index-1][0] = -1;
			}
			archers[index-1][1] = archers[index-1][0] < a ? archers[index-1][0] + 1: a;
			archers[index-1][2] = archers[index-1][0] < b ? archers[index-1][0] + 1: b;
		}

		nums.erase(Node(archers[index][3], index));
		archers[index][3] = archers[index][1] + archers[index+1][2] + archers[index-1][2];
		if (archers[index][3] > 0)
			nums.insert(pair<Node, int>(Node(archers[index][3], index), archers[index][0]));

		// update
		if (index + 2 < n - 1) {
			nums.erase(Node(archers[index+2][3], index+2));
			archers[index+2][3] = archers[index+2][1] + archers[index+3][2] + archers[index+1][2];
			if (archers[index+2][3] > 0)
				nums.insert(pair<Node, int>(Node(archers[index+2][3], index+2), archers[index+2][0]));
		}

		if (index-2 > 0) {
			nums.erase(Node(archers[index-2][3], index-2));
			archers[index-2][3] = archers[index-2][1] + archers[index-3][2] + archers[index-1][2];
			if (archers[index-2][3] > 0)
				nums.insert(pair<Node, int>(Node(archers[index-2][3], index-2), archers[index-2][0]));
		}

		if (index + 1 < n - 1) {
			nums.erase(Node(archers[index+1][3], index+1));
			archers[index+1][3] = archers[index+1][1] + archers[index+2][2] + archers[index][2];
			if (archers[index+1][3] > 0)
				nums.insert(pair<Node, int>(Node(archers[index+1][3], index+1), archers[index+1][0]));
		}


		if (index - 1 > 0) {
			nums.erase(Node(archers[index-1][3], index-1));
			archers[index-1][3] = archers[index-1][1] + archers[index-2][2] + archers[index][2];
			if (archers[index-1][3] > 0)
				nums.insert(pair<Node, int>(Node(archers[index-1][3], index-1), archers[index-1][0]));
		}

	}



	cout << attack.size() << endl;
	for (int i = 0; i < attack.size(); i++) {
		cout << attack[i] << " ";
	}

	cout << endl;
}
