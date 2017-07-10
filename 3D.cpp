#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct QuestionMark {
    int idx;
    int o_cost;
    int c_cost;
};

bool pair_quotes(char* seq, int start, int end, int &stack_seq);

bool compute_cost(char *seq, vector<QuestionMark> &q_seq, int &stack_seq, int idx, int &cost);

int remains(int idx, int length);

int main(void) {
    char sequence[50000];
    cin.getline(sequence, 50000);
    int length = strlen(sequence);
    int qlength = 0;

    for (int i = 0; i < length; i++) {
        if (sequence[i] == '?') {
            qlength++;
        }
    }

    vector<QuestionMark> q;
    int previous_start = 0;
    for (int i = 0; i < qlength; i++) {
        QuestionMark qmark;
        cin >> qmark.o_cost >> qmark.c_cost;
        qmark.idx = find(sequence+previous_start, sequence+length, '?') - sequence;
        previous_start = qmark.idx + 1;
        q.push_back(qmark);
    }

    int stack_seq = 0;
    int index = 0;

    
    if (q.size() > 0) {
        int cost = 0;
        compute_cost(sequence, q, stack_seq, 0, cost);
        cout << cost << endl;
        cout << sequence << endl;
    } else {
        pair_quotes(sequence, 0, length, stack_seq);
        cout << 0 << endl;
        cout << sequence << endl;        
    }
    
}

bool pair_quotes(char* seq, int start, int end, int &stack_seq) {
    // from start to len try to pair the sequence, based on previous stack_seq
    if (stack_seq < 0) {
        return false;
    }
    for (int i = start; i < end; i++) {
        if (seq[i] == '(') {
            stack_seq++;
        } else if (seq[i] == ')') {
            stack_seq--;
        } else {
            return false;
        }

        if (stack_seq < 0) {
            return false;
        } 
    }
    return true;
}


bool compute_cost(char *seq, vector<QuestionMark> &q_seq, int &stack_seq, int idx, int &cost) {
    int length = strlen(seq);
    if (stack_seq-2 >= remains(q_seq[idx].idx, length)) {
        return false;
    }
    
    int start = 0;
    if (idx != 0) {
        start = q_seq[idx-1].idx + 1;
    }
    if (!pair_quotes(seq, start, q_seq[idx].idx, stack_seq)) {
        return false;
    }

    if (stack_seq == 0) {
        cost += q_seq[idx].o_cost;
        seq[q_seq[idx].idx] = '(';
        stack_seq++;
        if (idx + 1 == q_seq.size()) {
            int temp_idx = q_seq[idx].idx + 1;
            return pair_quotes(seq, temp_idx, length, stack_seq);
        } else {
            return compute_cost(seq, q_seq, stack_seq, idx+1, cost);
        }
    }
    // else if (stack_seq  == remains(q_seq[idx].idx, length) + 1) {
    //     seq[q_seq[idx].idx] = ')';
    //     return (pair_quotes(seq, q_seq[idx].idx, strlen(seq), stack_seq));
    // } else if (stack_seq == remains(q_seq[idx].idx, length) - 1) {
    //     seq[q_seq[idx].idx] = '(';
    //     return (pair_quotes(seq, q_seq[idx].idx, strlen(seq), stack_seq));
    else {        
        if (idx + 1 == q_seq.size()) {
            int s1 = stack_seq + 1;
            int s2 = stack_seq - 1;
            bool isowork = pair_quotes(seq, q_seq[idx].idx + 1, length, s1);
            isowork = isowork && s1 == 0;
            bool iscwork = pair_quotes(seq, q_seq[idx].idx + 1, length, s2);
            iscwork = iscwork && s2 == 0;

            if ((isowork && iscwork && s1 <= s2) || (isowork && !iscwork)) {
                stack_seq = s1;
                seq[q_seq[idx].idx] = '(';
                cost += q_seq[idx].o_cost;
                return true;
            } else if ((isowork && iscwork && s2 > s1) || (iscwork && !isowork)) {
                stack_seq = s2;
                seq[q_seq[idx].idx] = ')';
                cost += q_seq[idx].c_cost;
                return true;
            } else {
                return false;
            }
        } else {
            int s1 = stack_seq + 1;
            int s2 = stack_seq - 1;
            int temp_idx = idx + 1;
            int temp_cost1 = cost+q_seq[idx].o_cost;
            int temp_cost2 = cost+q_seq[idx].c_cost;

            bool isowork = compute_cost(seq, q_seq, s1, temp_idx, temp_cost1);
            bool iscwork = compute_cost(seq, q_seq, s2, temp_idx, temp_cost2);
            if ((isowork && iscwork && temp_cost1 <= temp_cost2) || 
                (isowork && !iscwork)) {
                
                cost = temp_cost1;
                seq[q_seq[idx].idx] = '(';
                stack_seq = s1;
                return true;
            } else if ((isowork && iscwork && temp_cost1 > temp_cost2) || 
                (!isowork && iscwork)) {
                
                cost = temp_cost2;
                seq[q_seq[idx].idx] = ')';
                stack_seq = s2;
                return true;
            } else {
                return false;
            }
        }
    }
}

int remains(int idx, int length) {
    return length - idx - 1;
}