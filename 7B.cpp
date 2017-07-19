#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

typedef pair<int, int> Node;

int m, t, p, mem[100][2];

int main(void) {
    cin >> m >> t;
    string op;
    // map<int, Node> locks;
    // list<vector<int> > locks;
    set<int> locks;

    for (int i = 0; i < t; i++) {
        cin >> op;
        if (op[0] == 'a') {
            int size;
            cin >> size;
            
            // allocate memory
            for (set<int>::iterator itr = locks.begin(); next(itr) != locks.end(); ++itr) {
                if (*next(itr) - *itr - mem[*itr] >= size) {}
            }



            int start = 0;
            bool found = false;
            if (size > memory) {
                cout << "NULL" << endl;
            } else {
                for (map<int, Node>::iterator itr = locks.begin(); itr != locks.end(); i++) {
                    if (next(itr) == locks.end() && m - itr->second.first - itr->second.second >= size) {
                        start = itr->second.first + itr->second.second;
                        found = true;
                    } else if (next(itr)->second.first - itr->second.first - itr->second.second >= size) {
                        start = itr->second.first + itr->second.second;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    locks.insert(++p, make_pair(start, size));
                } else if (locks.size() == 0 && m >= size) {
                    locks.insert(++p, make_pair(0, size));
                } else {
                    cout << "NULL" << endl;
                }
            }
        } else if (op[0] == 'e') {
            int pos;
            cin >> pos;
            bool found = false;
            for (map<int, Node>::iterator itr = locks.begin(); itr != locks.end(); ++itr) {
                if (itr->first == pos) {
                    found = true;
                    break;
                }
            }
            if (found) {

            }
        }
    }
}

map<int, Node>::iterator next(map<int, Node>::iterator itr) {
    return ++itr;
}