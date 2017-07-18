#include <iostream>
#include <list>
#include <map>
#include <cmath>

using namespace std;

typedef pair<int, int> Node;
typedef pair<Node, int> value_type;

struct mycompare {
	bool operator()(const Node &n1, const Node &n2) const{
		return (n1.first < n2.first || (n1.first == n2.first && n1.second < n2.second));
	}
};

int n, k;
int h[100001];
int periods[100001][2];

int main(void) {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}

	list<int> books;
	map<Node, int, mycompare> orders;
	orders.insert(value_type(Node(h[0], 0), 0));

	books.push_back(0);

	int max_length = 1;
	int count = 1;
	int last_i = 1;
	int maxh = h[0];
	int minh = h[0];

	for (int i = 0; i < n - max_length + 1; i++) {
		int index = last_i;
		int temp_lasti = last_i;
		int temp_maxh = maxh;
		int temp_minh = minh;
		while (index < n) {
			if (h[index] > temp_maxh) {
				temp_maxh = h[index];
			}
			if (h[index] < temp_minh) {
				temp_minh = h[index];
			}

			if (temp_maxh - temp_minh <= k) {
				books.push_back(index);
				orders.insert(value_type(Node(h[index], index), index));
				temp_lasti++;
				if (temp_lasti - i > max_length) {
					count = 1;
					periods[count-1][0] = i;
					periods[count-1][1] = temp_lasti - 1;
					max_length = temp_lasti - i;
				} else if (temp_lasti - i == max_length) {
					count++;
					periods[count-1][0] = i;
					periods[count-1][1] = temp_lasti - 1;
				}
				last_i = temp_lasti;
				minh = temp_minh;
				maxh = temp_maxh;
				index++;
			} else {
				break;
			}
		}

		// move to next
		books.pop_front();
		orders.erase(Node(h[i], i));

		if (books.size() == 0) {
			books.push_back(i);
			orders.insert(value_type(Node(h[i], i), i));
			last_i = i + 2;
			maxh = h[i+1];
			minh = h[i+1];
			if (max_length == 1 && i+1 < n) {
				periods[count][0] = i+1;
				periods[count][1] = i+1;
				count++;
			}
		} else {
			maxh = orders.rbegin()->first.first;
			minh = orders.begin()->first.first;
		}
	}

	cout << max_length << " " << count << endl;
	// for (int i = 0; i < count; i++) {
	// 	cout << periods[i][0]+1 << " " << periods[i][1]+1 << endl;
	// }
}