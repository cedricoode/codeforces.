#include <iostream>
#include <math.h>
using namespace std;

int findEquator(long long start, long long end, long long middle, long long* arr) {
   // cout << "finding new: " << start << ", " << end << ", value: " << middle << endl;
    if (start > end) { /*cout << "branch 1" << endl; */return -1; }
    if (start == end && arr[start]*2 >= middle) { /*cout << "branch 2" << endl;*/ return start;}
    if (start + 1 == end) {
        if (arr[start] * 2 == middle) { /*cout << "branch 3" << endl;*/ return start; }
        else { /*cout << "branch 4" << endl;*/ return end; }
    }

    long long mid = (start + end) / 2;
    if (arr[mid]*2 <= middle) return findEquator(mid, end, middle, arr);
    else return findEquator(start, mid, middle, arr);
}
 
int main() {
  long long n;
  cin >> n;
  long long* questions  = new long long [n];
  long long questionNo;
  cin >> questionNo;
  questions[0] = questionNo;
  for (long long i = 1; i < n; i++) {
      cin >> questionNo;
      questions[i] = questions[i-1] + questionNo;
  }
  /*
  for (int i = 0; i < n; i++)
      cout << questions[i];
  cout << endl;
  */
  long long middle = questions[n-1]; 

  cout << 1 + findEquator(0, n-1, middle, questions)<< endl;

}


