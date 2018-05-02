#include <iostream>
#include <list>
#include <map>

using namespace std;

void readInput(int, int, map<int, list<int> > &);
void outputAdj(map<int, list<int>> &);
void dfs(map<int, list<int>> &, int*, int*, int);
void dfsVisit(map<int, list<int>>&, int*, int*, int);
enum Color {white=0, grey, black};

int main() {
    int m,n;
    cin >> n >> m;
    int *color = new int[n]; // 0 -> white, 1 -> grep, 2 -> black
    int *pred = new int[n]; // preceding node
    map<int, list<int> > adj;
    // read in
    readInput(n, m, adj);
    outputAdj(adj);
    dfs(adj, color, pred, n);
}

void readInput(int n, int m, map<int, list<int>> &adj) {
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        list<int> & flist = adj[from];
        flist.push_back(to);
        list<int> & tlist = adj[to];
        tlist.push_back(from);
    }
}


void outputAdj(map<int, list<int>> &adj) {
    for (map<int, list<int>>::iterator it = adj.begin(); it != adj.end(); ++it) {
        list<int> &adjList = it->second;
        cout << it->first << " : ";
        for (list<int>::iterator itlist = adjList.begin(); itlist != adjList.end(); ++itlist) {
            cout << *itlist << ", ";
        }
        cout << endl;
    }
}

void dfs(map<int, list<int>>& adj, int* color, int* pred, int n) {
    for (int i = 0; i < n; i++) {
      color[i] = white;
      pred[i] = -1;
    }
    for (map<int, list<int>>::iterator it = adj.begin(); it != adj.end(); ++it) {
        if (color[it->first] == white) {
          dfsVisit(adj, color, pred, it->first);
        }
    }
}

void dfsVisit(map<int, list<int>>& adj, int* color, int* pred, int curr) {
    list<int>& currAdj = adj[curr];
    color[curr] = grey;
    for (list<int>::iterator it = currAdj.begin(); it != currAdj.end(); ++it) {
        if (color[*it] == white) {
            cout << "from: " << curr << endl;
            cout << "visit: " << *it << endl;
            pred[*it] = curr;
            dfsVisit(adj, color, pred, *it);
        } else {
            if (*it != pred[curr]) {
                list<int> cycle;
                cout << "**** printing cycle ***" << endl;
                int prev = pred[curr];
                cycle.push_back(*it);
                cycle.push_back(curr);
                while(prev != *it && prev != -1) {
                    cycle.push_back(prev);
                    prev = pred[prev];
                }
                if (prev != -1) {
                    cycle.sort();
                    for(list<int>::iterator c = cycle.begin(); c != cycle.end(); ++c) {
                        cout << *c << endl;
                    }
                }
                cout << "**** finish printing ****" << endl;
            }
            //if (*it != pred[tcurr]) {
            //    cout << "cycle detected! " << "from: " << curr << ", to: " << *it << endl;
            //}
        }
    }
    color[curr] = black;
}
