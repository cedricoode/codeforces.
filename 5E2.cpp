#include <iostream>
#include <set>

using namespace std;

int next_index(int, int index, int dir);

int main(void) {
	int total;
	cin >> total;
	int max_v = -1;
	int max_i = -1;
	long long max_count = 0;
	int *a = new int[1000000];	
	int **lr = new int*[2];
	lr[0] = new int[1000000];
	lr[1] = new int[1000000];
	for (int i = 0; i < total; i++) {
		cin >> a[i];
		if (a[i] > max_v) {
			max_v = a[i];
			max_i = i;
			max_count = 1;
		} else if (a[i] == max_v) {
			max_count++;
		}
		lr[0][i] = -1;
		lr[1][i] = -1;
	}

	set<int> same_i;

	long long total_count = 0;
	for (int i = next_index(total, max_i, 1); i != max_i; i = next_index(total, i, 1)) {
		if (a[i] == max_v || lr[0][i] != -1) {
			continue;
		}
		same_i.clear();
		same_i.insert(i);
		int right = next_index(total, i, 1);
		int left = next_index(total, i, -1);
		long long same_count = 1;
		while(a[right] <= a[i]) {
			if (a[right] == a[i]) {
				same_count++;
				same_i.insert(right);
			}
			
			if (lr[1][right] != -1) {
				right = lr[1][right];
			} else {
				right = next_index(total, right, 1);
			}
		}
		
		while(a[left] <= a[i]) {
			if (a[left] == a[i]) {
				same_i.insert(left);
				same_count++;
			}

			if (lr[0][left] != -1) {
				left = lr[0][left];
			} else {
				left = next_index(total, left, -1);
			}
		}
		for(set<int>::iterator k = same_i.begin(); k != same_i.end(); k++) {
			lr[1][*k] = right;
			lr[0][*k] = left;
		}
		
		if (lr[0][i] == lr[1][i]) {
			total_count--;
		}
		total_count += (2 * same_count) + (same_count * (same_count - 1) / 2);
	}

	total_count += (max_count * (max_count -1) / 2);
	cout << total_count << endl;
}


int next_index(int total, int index, int dir) {
	return (index+dir+total) % total;
}