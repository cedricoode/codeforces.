#include <set>
#include <iostream>
#include <string>

using namespace std;

int main(void) {
	string line;
	set<string> users;
	int traffic = 0;
	while (getline(cin, line)) {
		if (line[0] == '+') {
			line = line.substr(1);
			users.insert(line);
		} else if (line[0] == '-') {
			line = line.substr(1);
			users.erase(line);
		} else {
			int pos = line.find_first_of(':');
			line = line.substr(pos+1);
			int msg_length = line.length();
			traffic += msg_length * (users.size());
		}
	}
	cout << traffic << endl;
}