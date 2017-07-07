#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vehicle {
	int order;
	int capacity;

	Vehicle() {}
	Vehicle(int a, int b=0): order(a), capacity(b) {}
};

struct Optimal {
	int capacity;
	int choice;
	int v1_last, v2_last;

	Optimal() {}

	Optimal(int a, int b, int c, int d): capacity(a), choice(b), v1_last(c), v2_last(d) {}
};

void choose_vehicle(vector<Optimal> &result, vector<Vehicle> &v1, vector<Vehicle> &v2);

void print_choice(vector<Optimal> &result, vector<Vehicle> &v1, vector<Vehicle> &v2 );

bool comp(Vehicle &v1, Vehicle &v2);

int main(void) {
	int n, volume;
	cin >> n >> volume;
	vector<Vehicle> v1;
	vector<Vehicle> v2;
	for (int i = 0; i < n; i++) {
		Vehicle v(i+1);
		int type = 1;
		cin >> type;
		cin >> v.capacity;
		if (type == 1) {
			v1.push_back(v);
		} else {
			v2.push_back(v);
		}
	}

	sort(v1.begin(), v1.end(), comp);
	sort(v2.begin(), v2.end(), comp);	


	int v1_last = v1.size() - 1;
	int v2_last = v2.size() - 1;
	vector<Optimal> result;
	Optimal op1(0, -1, v1_last, v2_last);
	if (v1_last == -1) {
		cout << 0 << endl;
		return 0;
	}
	Optimal op2(v1[v1_last].capacity, 1, v1_last - 1, v2_last);
	result.push_back(op1);
	result.push_back(op2);
	for (int i = 2; i <= volume; i++) {
		if (result[i-1].v1_last == -1 && result[i-1].v2_last == -1) {
			break;
		}
		choose_vehicle(result, v1, v2);
	}

	print_choice(result, v1, v2);
}

void choose_vehicle(vector<Optimal> &result, vector<Vehicle> &v1, vector<Vehicle> &v2) {
	int last = result.size() - 1;
	Optimal &o1 = result[last], &o2 = result[last-1], optimal;
	
	int cap1 = 0, cap2 = 0;
	if (o1.v1_last == -1) {
		cap1 = o1.capacity;
	} else {
		cap1 = o1.capacity + v1[o1.v1_last].capacity;
	}
	if (o2.v2_last == -1) {
		cap2 = o2.capacity;
	} else {
		cap2 = o2.capacity + v2[o2.v2_last].capacity;		
	}

	if (cap1 > cap2) {
		optimal.capacity = cap1;
		if (o1.v1_last == -1) {
			optimal.choice = -1;
			optimal.v1_last = -1;			
		} else {
			optimal.choice = 1;
			optimal.v1_last = o1.v1_last - 1;			
		}
		optimal.v2_last = o1.v2_last;
	} else {
		optimal.capacity = cap2;
		if (o2.v2_last == -1) {
			optimal.choice = -1;
			optimal.v2_last = -1;						
		} else {
			optimal.choice = 2;
			optimal.v2_last = o2.v2_last - 1;			
		}
		optimal.v1_last = o2.v1_last;
	}
	result.push_back(optimal);
}

void print_choice(vector<Optimal> &result, vector<Vehicle> &v1, vector<Vehicle> &v2 ) {
	int idx = result.size() - 1;
	Optimal &last = result[idx];

	cout << last.capacity << endl;

	while (true) {
		if (idx == 0) {
			break;
		}
		if (last.choice == 1) {
			cout << v1[last.v1_last + 1].order << endl;
			last = result[idx - 1];
			idx -= 1;
		} else if (last.choice = 2) {
			cout << v2[last.v2_last + 1].order << endl;
			last = result[idx - 2];
			idx -=2;
		} else { // == -1
			if (last.v1_last == result[idx - 1].v1_last && last.v2_last == result[idx-1].v2_last) {
				last = result[idx - 1];
				idx -= 1;
			} else {
				last = result[idx - 2];
				idx -= 2;
			}
		}
	}
}

bool comp(Vehicle &v1, Vehicle &v2) {
	return v1.capacity < v2.capacity;
}
