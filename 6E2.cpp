#include <iostream>
#include <set>

using namespace std;

int n, k, h[100001], p[100001], maxlen, cnt;

int main(void) {

    cin >> n >> k;
    multiset<int> selections;

    int first = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        int len = selections.size();
        selections.insert(h[i]);
        len++;

        while (*(selections.rbegin()) - *(selections.begin()) > k) {
            multiset<int>::iterator itr = selections.find(h[first]);
            selections.erase(itr);
            len--;
            first++;
        }

        if (len > maxlen) {
            maxlen = len;
            p[0] = first;
            cnt = 1;
        } else if (len == maxlen) {
            p[cnt] = first;
            cnt++;
        }
    }

    cout << maxlen << " " << cnt << endl;

    for (int i = 0; i < cnt; i++) {
        cout << p[i]+1 << " " << p[i] + maxlen << endl;
    }

}