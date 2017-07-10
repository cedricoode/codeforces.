#include <iostream>
#include <limits>

using namespace std;

class TriNode {
	public:

	int count;
	TriNode *nodes[26];
	bool isleaf;

	TriNode() {
		isleaf = false;
		for (int i = 0; i < 26; i++) {
			nodes[i] = NULL;
		}
		count = 0;
	}

	int upsert(char *str) {
		int i = 0;
		TriNode * p1 = this;
		while (str[i]) {
			TriNode* &next = p1->nodes[str[i] - 'a'];
			if (!next) {
				next = new TriNode;				
			}
			p1 = next;
			i++;
		}
		p1 -> isleaf = true;
		p1 -> count++;
		return p1->count;
	}
};

int main(void) {
	int requests = 0;
	cin >> requests;

	TriNode root;
	char temp[32];
	for (int i = 0; i < requests;i++) {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.getline(temp, 32);
		int count = root.upsert(temp);
		if (count == 1) {
			cout << "OK" << endl;
		} else {
			cout << temp << count-1 << endl;
		}
	}
}