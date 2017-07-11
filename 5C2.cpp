#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<int> generate_memory(map<int, vector<int> > &memories, string &brackets, int i);
// int collect_legacy(map<int, vector<int> > &memories, string &brackets, int &o);


int main(void) {
	string brackets;
	cin >> brackets;
	int len = brackets.length();

	int maxlen = 0;
	int accu = 0;
	map<int, vector<int> > memories; // brackets number, length
	int last_memories = -1;
	int max_length = 0;
	int max_occ = 0;
	for (int i =0; i < len; i++) {
		if (brackets[i] == '(') {
			if (accu < 0) {
				accu = 1;
			} else {
				accu++;
			}
		} else {
			vector<int> m = generate_memory(memories, brackets, i);
			if (m[1] > max_length) {
				max_length = m[1];
				max_occ = 1;
			} else if (m[1] == max_length){
				max_occ++;
			}
			memories.insert(pair<int, vector<int> >(i, m));
			accu--;
		}
	}

	cout << max_length << " ";
	if (max_length== 0)
		cout << 1 << endl;
	else
	  cout << max_occ << endl;
}

vector<int> generate_memory(map<int, vector<int> > &memories, string &brackets, int i) {
	vector<int> mem;
	if (i == 0) {
		mem.push_back(-1);
		mem.push_back(-1);
		return mem;
	} else if (brackets[i-1] == '(') {
		// extend legacy
		int o = i - 2;
		if (o > 0 && brackets[o] == ')') {
			vector<int> &previous = memories[o];
			if (previous[0] >= 0) {
				mem.push_back(previous[0]);
				mem.push_back(previous[1] + 2);
				return mem;
			}
		}
		mem.push_back(i-1);
		mem.push_back(2);
		return mem;
	} else {
		int o = i - 1;
		vector<int> &previous = memories[o];
		if (previous[0] <= 0) {
			mem.push_back(-1);
			mem.push_back(-1);	
		} else if (brackets[previous[0] - 1] == ')'){
			mem.push_back(-1);
			mem.push_back(-1);
		} else {
			o = previous[0] - 2;
			if (o > 0 && brackets[o] == ')' && memories[o][0] >= 0) {
				vector<int> &p_previous = memories[o];
				mem.push_back(p_previous[0]);
				mem.push_back(p_previous[1] + previous[1] + 2);
			} else {
				mem.push_back(previous[0]- 1);
				mem.push_back(previous[1] + 2);
			}
		}
		return mem;
	}
}

// int collect_legacy(map<int, vector<int> > &memories, string &brackets, int &o) {
// 	int legacy = 0;
// 	while (o >= 0 && brackets[o] == ')') {
// 		vector<int> &previous = memories[o];
// 		legacy += previous[1];			
// 		o = previous[0] - 1;
// 	}

// 	if (o < 0) {
// 		return 0;
// 	} else {
// 		return legacy;
// 	}
// }