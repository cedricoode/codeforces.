#include <iostream>  
#include <cstdio>  
#include <map>  
#include <queue>  
#include <algorithm>  
using namespace std;  
  
int main() {  
    int n;  
    scanf("%d", &n);  
  
    vector<int> height(n);  
    for (int i = 0; i < n; i++) scanf("%d", &(height[i]));  
    vector<int>::iterator highest = max_element(height.begin(), height.end());  
  
    //cut the circle, make a chain  
    vector<int> num(highest, height.end());  
    num.reserve(n);  
    copy(height.begin(), highest, num.end());  

    for (int i = 0; i < n; i++) {
        cout << num[i] << endl;
    }
  
    //left[i] is the nearest bigger number in the left of num[i]  
    vector<int> left(n, -1);  
    for (int i = 1; i < n; i++) {  
        int p = i - 1;  
        while (num[i] > num[p]) p = left[p];  
        left[i] = num[i] == num[p] ? left[p] : p;  
    }  
  
    //right[i] is the nearest bigger number in the right of num[i]  
    //same[i] is the number of the number equal to num[i] in [i, right[i]]  
    vector<int> right(n, n);  
    vector<int> same(n, 0);  
    for (int i = n - 2; i >= 0; i--) {  
        int p = i + 1;  
        while (p < n && num[i] > num[p]) p = right[p];  
  
        if (p >= n) {  
            right[i] = p;  
            continue;  
        }  
  
        right[i] = num[i] == num[p] ? right[p] : p;  
        same[i] = num[i] == num[p] ? same[p] + 1 : 0;  
    }  
  
    long long ans = 0;  
    for (int i = 0; i < n; i++) {  
        if (left[i] >= 0) ans += 1;  
        if (right[i] < n) ans += 1;  
        if (right[i] >= n && left[i] > 0) ans += 1;  
        ans += same[i];  
    }  
  
	cout << ans << endl;
    // printf("%I64d\n", ans);  
    return 0;  
}  