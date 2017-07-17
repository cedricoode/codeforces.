#include <iostream>

using namespace std;

int next_index(int total, int index, int dir);

int main(void) {
	int total;
	cin >> total;
	int max_v = -1;
	int max_i = -1;
	long long max_count = 0;
	int *a = new int[1000000];
	int *same_i = new int[1000000];	
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

	int begin = next_index(total, max_i, 1);
	for (int i = begin; i != max_i; i = next_index(total, i, 1)) {
		int p = next_index(total, i, -1);
		while (a[i] > a[p]) p = lr[0][p];
		lr[0][i] = 	a[i] == a[p] ? lr[0][p] : p;
	}

	begin = next_index(total, max_i, -1);
	for (int i = begin; i != max_i; i = next_index(total, i, -1)) {
		int p = next_index(total, i, 1);
		while (a[i] > a[p]) p = lr[1][p];
		lr[1][i] = a[i] == a[p] ? lr[1][p] : p;
		same_i[i] = a[i] == a[p] ? same_i[p]+1 : 0;
	}

	long long total_count = 0;
	for (int i = 0; i < total; i++) {
		if (lr[0][i] != -1) total_count++;
		if (lr[1][i] != -1 && lr[1][i] != lr[0][i]) total_count++;
		if (same_i[i] != 0) total_count += same_i[i];
	}

	cout << total_count << endl;

}

int next_index(int total, int index, int dir) {
	return (index+dir+total) % total;
}