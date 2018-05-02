#include <iostream>
#include <math.h>
#include <string>

using namespace std;

bool isPerfectSquare(int num) {
    int root = sqrt(num);
    return root * root == num;
}


int main() {
    string num;
    cin >> num;
    int length = num.length();

    int cases = int (pow(2, length));
    bool* visitMap = new bool[cases];
    int* digitMap = new int[length];
    int maxDel = -10000;
    for (int i = 0; i < (1 << length); i++) {
        int currLen = 0;
        for (int j = 0; j < length; j++) {
            if ((i & ( 1 << j)) > 0) {
                digitMap[currLen++] = j;
            }
        }
        if (currLen > 0 ) {
            if (num[digitMap[0]] != '0') {
                int currNum = 0;
                for (int k = 0; k < currLen; k++) {
       //             cout << num[digitMap[k]];
                    currNum = 10 * currNum + (num[digitMap[k]] - '0');
                }
         //       cout << currNum << endl;
                if (isPerfectSquare(currNum) && currLen > maxDel) {
     //               cout << "Found perfect square: " << currNum << endl;
                    maxDel = currLen;
                }
            }
        }
    }
    if ( maxDel < 0 ) {
        cout << -1 << endl;
    } else {
        cout << length - maxDel << endl;
    }
}

