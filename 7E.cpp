#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

#define endl '\n'

typedef vector<bool> Macro; // is_sus, is_number, +, -, *, / 
typedef vector<string> Terms;
typedef map<string, Macro> Map;
typedef Map::iterator Itr;

Macro generate_macro();

Map macros;
Terms terms;
int n, len;
string construct;

int main(void) {
	cin >> n;
	cin.ignore(1000, '\n');
	while (n--) {
		getline(cin, construct);
		int i = 0;
		while (construct[i] != '#') i++;
		i++;
		while (construct[i] == ' ') i++;
		i = i + 6;
		while (construct[i] == ' ') i++;
		int j = i;
		while (construct[j] != ' ' && construct[j] != '(') j++;
		string name = construct.substr(i, j-i);
		construct = construct.substr(j);

		// Generate macro
		Macro m = generate_macro();
		macros.insert(make_pair(name, m));
	}

	getline(cin, construct);
	
	Macro m = generate_macro();
	if (m[0]) {
		cout << "Suspicious" << endl;
	} else {
		cout << "OK" << endl;
	}

}

void latex() {
	len = construct.length();
	terms.clear();	
	for (int j = 0; j < len; j++) {
		while (j < len && construct[j] == ' ') j++;

		if (j >= len) break;
		
		switch(construct[j]) {
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
			case ')':
				terms.push_back(string(1, construct[j]));
				break;
			default:
				string name = "";
				while (j < len && construct[j] != '+' && construct[j] != '-' && construct[j] != '*' && construct[j] != '/' && construct[j] != '(' && construct[j] != ')' && construct[j] != ' ')
					name += construct[j++];
				j--;
				terms.push_back(name);
				break;
		}
	}

	// for (int i = 0; i < terms.size(); i++) cout << terms[i] << endl;
}

Macro generate_macro() {
	int j, i;
	latex();
	Macro macro(6, 0);
	int brackets_stack = 0;
	bool ismiddlezero = false;
	for (i = 0; i < terms.size(); i++) {
		if (terms[i][0] == '(') {
			brackets_stack++;
		} else if (terms[i][0] == ')') {
			brackets_stack--;
			if (i != terms.size()-1 && brackets_stack == 0) {
				ismiddlezero = true;
			} 
		} else if (terms[i][0] >= '0' && terms[i][0] <= '9') {
			// number. ignore
		} else if (terms[i][0] == '+') {
			if (!brackets_stack) macro[2] = 1;
		} else if (terms[i][0] == '-') {
			if (!brackets_stack) macro[3] = 1;
		} else if (terms[i][0] == '*') {
			if (!brackets_stack) macro[4] = 1;
		} else if (terms[i][0] == '/') {
			if (!brackets_stack) macro[5] = 1;
		} else {
			// variable and macro.
			Itr itr = macros.find(terms[i]);
			if (itr != macros.end()) {
				// macro
				if (itr->second[0]) {
					macro[0] = 1;
					break;
				}

				if (itr->second[1]) {
					continue;  // is_number
				}
				
				// check before
				if (i>0){
					// check precedence
					if (itr->second[2]+itr->second[3] && (terms[i-1][0] == '*' || terms[i-1][0] == '/')) {
						macro[0] = 1;
						break;
					}

					// check order
					if (terms[i-1][0] == '-' && (itr->second[2]+itr->second[3])) {
						macro[0] = 1;
						break;
					}
					if (terms[i-1][0] == '/' && (itr->second[4]+itr->second[5])) {
						macro[0] = 1;
						break;
					}
				}
				// check after
				if (i<terms.size() - 1) {
					// check precedence
					if (itr->second[2]+itr->second[3] && (terms[i+1][0] == '*' || terms[i+1][0] == '/')) {
						macro[0] = 1;
						break;
					}
				}

				// inherit simbols
				if (!brackets_stack) {
					for (int i = 2; i < 6; i++) {
						if (itr->second[i]) macro[i] = 1;
					}
				}
			} else {
				//variable. ignore
			}
		}
	}

	if (terms[0][0] == '(' && !ismiddlezero) {
		macro[1] = 1;
	}
	bool is_number = true;
	for (int i = 2; i < 6; i++) {
		if (macro[i]) {
			is_number = false;
			break;
		}
	}
	if (is_number) macro[1] = 1;
	return macro;
}
