#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstring>

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

inline bool operator==(const QuestionMark &q1, const QuestionMark &q2) {
	return q1.idx == q2.idx;
}

void toggle_quotes(QuestionMark &q, int end, vector<QuestionMark> &qs);

class PriorityQueue {
	public:
	list<QuestionMark> elems;
	void insert(QuestionMark const &m) {
		list<QuestionMark>::iterator i = elems.begin();
		for (; i != elems.end(); i++) {
			if ((*i).cost() < m.cost()) {
				break;
			}
		}
		elems.insert(i, QuestionMark(m));
	}
	QuestionMark pop_front() {
		if (elems.size() > 0) {
			QuestionMark a (*elems.begin());
			elems.pop_front();
			return a;
		} else {
			QuestionMark m;
			m.idx = -1;
			return m;
		}
	}
	int size() {
		return elems.size();
	}
};

bool match_sequence(char seq[], vector<QuestionMark> & q_seq, long long&cost);

void print_sequence(char seq[], vector<QuestionMark> &q_seq);

int main(void) {
	char sequence[50000];
    cin.getline(sequence, 50000);
    int length = strlen(sequence);
    int qlength = 0;
    vector<QuestionMark> q;

    for (int i = 0; i < length; i++) {
        if (sequence[i] == '?') {
            qlength++;
        }
    }

    int previous_start = 0;
    for (int i = 0; i < qlength; i++) {
        QuestionMark qmark;
        cin >> qmark.o_cost >> qmark.c_cost;
        qmark.idx = find(sequence+previous_start, sequence+length, '?') - sequence;
        previous_start = qmark.idx + 1;
		qmark.isopening = false;
        q.push_back(qmark);
    }

	long long cost = 0;
	if (match_sequence(sequence, q, cost)) {
		cout << cost << endl;		
		print_sequence(sequence, q);
	} else {
		cout << -1 << endl;
	}
}

void print_sequence(char seq[], vector<QuestionMark> &q_seq){
	int idx = 0;
	for (int i = 0; i < strlen(seq); i++) {
		if (seq[i] == '?') {
			if (q_seq[idx].isopening) {
				cout << '(';
			} else {
				cout << ')';
			}
			idx++;
		} else {
			cout << seq[i];
		}
	}
}


bool match_sequence(char seq[], vector<QuestionMark> &q_seq, long long&cost) {
	int length = strlen(seq);
	int stack = 0;
	PriorityQueue que;
	int idx = 0;
	for (int i = 0; i < length; i++) {
		if (seq[i] == '(') {
			stack++;
		} else if (seq[i] == ')') {
			stack--;
		} else {
			q_seq[idx].isopening = false;
			que.insert(q_seq[idx]);
			cost += q_seq[idx].c_cost;
			stack--;
		}

		if (stack < 0) {
			if (que.size() == -1) {
				return false;
			} else {
				QuestionMark m = que.pop_front();
				toggle_quotes(m, idx+1, q_seq);
				cost -= m.cost();
				stack += 2;
			}
		}

		if (seq[i] == '?') {
			idx++;
		}
	}
	return stack == 0;
}

void toggle_quotes(QuestionMark &q, int end, vector<QuestionMark> &qs) {
	// vector<QuestionMark>::iterator i = find(qs.begin(), qs.begin()+end, q);
	for (int i = 0; i < end; i ++) {
		if (qs[i].idx == q.idx) {
			qs[i].isopening = !q.isopening;
			return;
		}
	}
}