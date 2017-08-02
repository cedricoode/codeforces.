#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

struct CycleInfo {
	int end;
	int len;
	bool isCycle;

	CycleInfo(int e, int l, bool i): end(e), len(l), isCycle(i) {}
	CycleInfo(): end(-1), len(0), isCycle(false) {}
};
typedef map<int, CycleInfo> Cycles;

int n, m;
Cycles cycles;
int points[55][2];

int find_end(int p, int dir) {
	int pb =  p;
	while (points[pb][dir] != pb) pb = points[pb][dir];
	return pb;
}

void swap_position(int p, int q) {
	int ps = p;
	while (ps != q) {
		swap(points[ps][0], points[ps][1]);
		ps = points[ps][0];
	}
	swap(points[ps][0], points[ps][1]);
}

bool insert(int p, int q) {
	int pb = p, pe = p, qb = q, qe = q;
	if (points[p][0] == p) {
		pe = find_end(p, 1);
	} else if(points[p][1] == p) {
		pb = find_end(p, 0);
	} else return false;
	
	if (points[q][0] == q) {
		qe = find_end(q, 1);
	} else if (points[q][1] == q) {
		qb = find_end(q, 0);
	} else return false;

	Cycles::iterator cp = cycles.find(pb);
	Cycles::iterator cq = cycles.find(qb);

	if (cp->second.isCycle || cq->second.isCycle) return false;
	
	CycleInfo cycleInfo;
	// IsCycle
	if (pb == qb) cycleInfo.isCycle = true;
	// Length
	cycleInfo.len += cp->second.len;
	cycleInfo.len += (pb == qb ? 0 : cq->second.len);
	if (p == q) cycleInfo.len--;
	// End && swap
	int start;
	if (p == pb && q == qb) {
		start = pe;
		cycleInfo.end = qe;
		swap_position(pb, pe);
		points[q][0] = p;
		points[p][1] = q;
	} else if (p == pb && q == qe) {
		start = qb;
		cycleInfo.end = pe;
		points[q][1] = p;
		points[p][0] = q;
	} else if (p == pe && q == qb) {
		start = pb;
		cycleInfo.end = qe;
		points[p][1] = q;
		points[q][0] = p;
	} else {
		start = pb;
		cycleInfo.end = qb;
		swap_position(qb, qe);
		points[p][1] = q;
		points[q][0] = p;
	}
	int end = cycleInfo.end;
	if (cycleInfo.end < start) {
		swap_position(start, end);
		cycleInfo.end = start;
		cycles[end] = cycleInfo;
		swap(start, end);
	} else {
		cycles[start] = cycleInfo;
	}
	if (pb != start) cycles.erase(pb);
	if (qb != start) cycles.erase(qb);
	
	return true;
}

int main(void) {
	cin >> n >> m;
	for (int i = 0; i < n+1; i++) {
		points[i][0] = i;
		points[i][1] = i;
		if (i != 0)
			cycles[i] = CycleInfo(i, 1, false);
	}


	for (int i = 0; i < m; i++) {
		int p, q;
		cin >> p >> q;
		if (!insert(p, q)) {
			cout << "NO" << endl;
			return 0;
		}
	}

	int path[102];
	int c = 0;
	while (cycles.size() > 0) {
		Cycles::iterator itrb = cycles.begin();
		if (itrb->second.isCycle) {
			if (cycles.size() != 1) {
				cout << "NO" << endl;
				return 0;
			} else break;
		}
		Cycles::iterator itre = ++cycles.begin();
		if (itre == cycles.end()) {
			path[c++] = itrb->first;
			path[c++] = itrb->second.end;
			if (!insert(itrb->first, itrb->second.end)) {
				cout << "NO" << endl; 
				return 0;
			}
		} else {
			path[c++] = itrb->first;
			path[c++] = itre->first;
			if (!insert(itrb->first, itre->first)) {
				cout << "NO" << endl;
				return 0;
			}
		}
	}

	cout << "YES" << endl;
	cout << c/2 << endl;
	for (int i = 0; i < c; i++) {
		cout << path[i] << " " << path[i+1] << endl;
		i++;
	}

	// for (Cycles::iterator itr = cycles.begin(); itr != cycles.end(); ++itr) {
	// 	int i = itr->first;
	// 	if (i == 0) continue;
	// 	int j = itr->second.end;
	// 	cout << (itr->second.isCycle ? "True: " : "False: ");
	// 	while (j != i) {
	// 		cout << i << ", ";
	// 		i = points[i][1];
	// 	}
	// 	cout << j << endl;
	// }
}