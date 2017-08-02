#include <iostream>
#include <map>
#include <utility>

using namespace std;

struct CycleInfo {
	int end;
	int len;
	bool isCycle;
	CycleInfo() {end = -1; len = 0; isCycle = false;};
	CycleInfo(int e, int l, bool i): end(e), len(l), isCycle(i){}
};
typedef map<int, CycleInfo> Cycle;

int n, m;
int points[55][2]; // swapped, left, right
Cycle cycles; // (start, (end, size))


bool insert(int p1, int p2) {
	Cycle::iterator uc;
	if (points[p1][0] == p1) {
		if (points[p2][0] == p2) {
			points[p1][0] = p2;
			int p2E = p2;
			while (p2E != points[p2E][1]) {
				swap(points[p2E][0], points[p2E][1]);
				p2E = points[p2E][0];
			}
			swap(points[p2E][0], points[p2E][1]);
			points[p2][1] = p1;
			
			CycleInfo cycleInfo;
			if (p2E == p1) {
				cycleInfo.isCycle = true;
			}
			Cycle::iterator cp1 = cycles.find(p1);
			Cycle::iterator cp2 = cycles.find(p2);

			// update length;
			if (!cycleInfo.isCycle) {
				cycleInfo.len += (cp1 == cycles.end() ? 1 : cp1->second.len);
				if (p1 != p2)
					cycleInfo.len += (cp2 == cycles.end() ? 1 : cp2->second.len);
			}

			// insert and remove old cycle
			int p1E = (cp1 == cycles.)
			cycleInfo.end = cycleInfo.isCycle ? p2 : p1E;
			cycles[p2E] = cycleInfo;
			if (p2E != p1) cycles.erase(p1);
			if (p2E != p2) cycles.erase(p2);
			uc = cycles.find(p2E);

		} else if (points[p2][1] == p2) {
			int p2S = p2;
			while (points[p2S][0] != p2S) p2S = points[p2S][0];
			points[p1][0] = p2;
			points[p2][1] = p1;

			CycleInfo cycleInfo;
			if (p2S == p1) {
				cycleInfo.isCycle = true;
			}
			Cycle::iterator cp1 = cycles.find(p1);
			Cycle::iterator cp2 = cycles.find(p2S); // cp2 can not be cycles.end()

			// update length;
			if (!cycleInfo.isCycle) {
				cycleInfo.len += (cp1 == cycles.end() ? 1 : cp1->second.len);
				cycleInfo.len += cp2->second.len;
			}

			// insert and remove old cycle

			if (cp1 == cycles.end()) cycles[p2S].first = p1, cycles[p2S].second++;
			else {
				cycles[p2S].first = cp1->second.first;
				cycles[p2S].second += cp1->second.second;
				if (p2S != p1) cycles.erase(p1);
			}
			uc = cycles.find(p2S);
		} else return false;
	} else if (points[p1][1] == p1) {
		if (points[p2][0] == p2) {
			return insert(p2, p1);
		} else if (points[p2][1] == p2) {
			int p1S = p1;
			while (points[p1S][0] != p1S) {
				swap(points[p1S][0], points[p1S][1]);
				p1S = points[p1S][1];
			}
			points[p1][0] = p2;
			points[p2][1] = p1;
			swap(points[p1S][0], points[p1S][1]);
			int p2S = p2;
			while (points[p2S][0] != p2S) p2S = points[p2S][0];

			Cycle::iterator cp1 = cycles.find(p1S);
			Cycle::iterator cp2 = cycles.find(p2S);
			cp2->second.first = p1;
			cp2->second.second += cp1->second.second;
			cycles.erase(cp1);
			uc = cp2;
		} else return false;
	} else return false;

	if (uc->second.second > n) return false;
	else return true;
}

int main(void) {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		points[i][1] = i;
		points[i][0] = i;
	}

	for (int i = 0; i < m; ++i) {
		int p1, p2;
		cin >> p1 >> p2;
		if (!insert(p1-1, p2-1)) {
			cout << "NO" << endl;
			return 0;
		}
	}

	for (Cycle::iterator itr = cycles.begin(); itr != cycles.end(); ++itr) {
		int ps = itr->first;
		cout << "cycle: (" << itr->first << " " << itr->second.first << "), " << itr->second.second << ": \n";
		while (ps != points[ps][1]) {
			cout << (ps + 1) << ", ";
			ps = points[ps][1];
		}
		cout << (ps+1) << endl;
	}
}