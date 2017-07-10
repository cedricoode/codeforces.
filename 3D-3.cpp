#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <functional>

using namespace std;

struct QuestionMark {
    int idx;
    int o_cost;
    int c_cost;
	bool isopening;
	int cost() const{
		return c_cost - o_cost;
	}
};

class my_compare {
	public:
	bool operator()(const QuestionMark& q1, const QuestionMark& q2) {
		return q1.cost() <= q2.cost();
	}
};

int main(void) {
	char sequence[60000];
    cin.getline(sequence, 60000);
	int length = strlen(sequence);
    int qlength = 0;

	priority_queue<QuestionMark, vector<QuestionMark>, my_compare> que;
	long long cost;
	int stack = 0;
	if (length % 2 == 1) {
		cout << -1 << endl;
		return 0;
	}
    for (int i = 0; i < length ; i++) {
        if (sequence[i] == '(') {
			stack++;
		} else if (sequence[i] == ')') {
			stack--;
		} else {
			QuestionMark q;
			cin>> q.o_cost >> q.c_cost;
			q.isopening = false;
			q.idx = i;
			stack--;
			cost += q.c_cost;
			que.push(q);
			sequence[i] = ')';
		}
		if (stack < 0) {
			if (que.size() == 0) {
				cout << -1 << endl;
				return 0;
			} else {
				QuestionMark m = que.top(); que.pop();
				stack += 2;
				cost -= m.cost();
				sequence[m.idx] = '(';
			}
		}
    }
	if (stack != 0) {
		cout << -1 << endl;
		return 0;
	} else {
		cout << cost << endl;
		cout << sequence << endl;
	}

}
