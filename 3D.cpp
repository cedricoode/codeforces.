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

bool compute_cost(char *seq, vector<QuestionMark> &q_seq, int &stack_seq, int idx, int &cost, vector<char> &selected_seq);

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
        vector<char> selected_seq;
        if (compute_cost(sequence, q, stack_seq, 0, cost, selected_seq)) {
            cout << cost << endl;

            int idx_mark = 0;
            for (int i = 0; i < length; i++) {
                if (sequence[i] != '?') {
                    cout << sequence[i];
                }else {
                    cout << selected_seq[idx_mark++];
                }
            }
            cout << endl;
        } else {
            cout << -1 << endl;
        }
    } else {
        if (pair_quotes(sequence, 0, length, stack_seq)) {
            cout << 0 << endl;
            cout << sequence << endl;
        } else {
            cout << -1 << endl;
        }
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


bool compute_cost(char *seq, vector<QuestionMark> &q_seq, int &stack_seq, int idx, int &cost, vector<char> &selected_seq) {
    int length = strlen(seq);
    
    int start = 0;
    if (idx != 0) {
        start = q_seq[idx-1].idx + 1;
    }

    if (stack_seq-2 >= remains(start, length)) {
        return false;
    }

    if (!pair_quotes(seq, start, q_seq[idx].idx, stack_seq)) {
        return false;
    }

    if (stack_seq == 0) {
        cost += q_seq[idx].o_cost;
        char previous = seq[q_seq[idx].idx];
        selected_seq.push_back('(');
        // seq[q_seq[idx].idx] = '(';
        stack_seq++;
        if (idx + 1 == q_seq.size()) {
            int temp_idx = q_seq[idx].idx + 1;
            if (pair_quotes(seq, temp_idx, length, stack_seq)) {
                return true;
            } else {
                // seq[q_seq[idx].idx] = previous;
                selected_seq.pop_back();
                return false;
            }
        } else {
            if (compute_cost(seq, q_seq, stack_seq, idx+1, cost, selected_seq)) {
                return true;
            } else {
                // seq[q_seq[idx].idx] = previous;
                selected_seq.pop_back();
                return false;
            }
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
                // seq[q_seq[idx].idx] = '(';
                selected_seq.push_back('(');
                cost += q_seq[idx].o_cost;
                return true;
            } else if ((isowork && iscwork && s2 > s1) || (iscwork && !isowork)) {
                stack_seq = s2;
                selected_seq.push_back(')');                
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
            vector<char> v1(selected_seq);
            vector<char> v2(selected_seq);
            v1.push_back('(');
            v2.push_back(')');       
            bool isowork = compute_cost(seq, q_seq, s1, temp_idx, temp_cost1, v1);
            bool iscwork = compute_cost(seq, q_seq, s2, temp_idx, temp_cost2, v2);
            if ((isowork && iscwork && temp_cost1 <= temp_cost2) || 
                (isowork && !iscwork)) {
                
                cost = temp_cost1;
                // seq[q_seq[idx].idx] = '(';
                selected_seq = vector<char>(v1);
                stack_seq = s1;
                return true;
            } else if ((isowork && iscwork && temp_cost1 > temp_cost2) || 
                (!isowork && iscwork)) {
                
                cost = temp_cost2;
                // seq[q_seq[idx].idx] = ')';
                // selected_seq.push_back(')');
                selected_seq = vector<char>(v2);
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