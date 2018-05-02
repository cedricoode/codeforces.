#include <iostream>
#include <climits>       

using namespace std;

int main() {
   long long maxB = INT_MIN;
   long long maxR = INT_MIN;
   long long prevB = INT_MIN;
   long long prevR = INT_MIN;
   long long prevP = INT_MIN;
   long long d = 0;
   long long dp = 0;
   long long coords;
   char city;
   long long count = 0;
   long long total = 0;
   cin >> total;
   while (count < total) {
       count++;
       cin >> coords >> city;
       if (city == 'P') {
           long long anchorB = prevB > prevP ? prevB : prevP;
           if (anchorB != INT_MIN) {
               d += coords - anchorB;
           }
           long long anchorR = prevR > prevP ? prevR : prevP;
           if (anchorR != INT_MIN) {
               d += coords - anchorR;
           }
           if (prevP != INT_MIN) {
               dp = coords - prevP;
               if (maxB == INT_MIN) maxB = dp;
               else if (coords - anchorB > maxB) maxB = coords - anchorB;
               if (maxR == INT_MIN) maxR = dp;
               else if (coords - anchorR > maxR) maxR = coords - anchorR;
//               cout << "distance " << d << endl;
               if ( maxB + maxR > dp) {
//                   cout << "using strategy 2" << endl;
                   d = d + (dp - maxR - maxB);
               }
//               if (prevB < prevP && prevR < prevP) {
//                   d -= dp;
//               }
//               cout << "maxB: " << maxB << ", maxR: " << maxR << endl;
//               cout << "dp: " << dp << ", distance: " << d << endl;
           }
           prevP = coords;
           maxB = maxR = INT_MIN;
           dp = 0;
       } else if (city == 'R') {
           long long anchor = prevR > prevP ? prevR : prevP;
           if (anchor != INT_MIN) {
               d += coords - anchor;
           }
           if (prevP != INT_MIN) {
               maxR = coords - anchor > maxR ? coords - anchor : maxR;
           }
           prevR = coords;
       } else {
           long long anchor = prevB > prevP ? prevB : prevP;
           if (anchor != INT_MIN) {
               d += coords - anchor;
           }
           if (prevP != INT_MIN) {
               maxB = coords - anchor > maxB ? coords - anchor : maxB;
           }
           prevB = coords;
       }
//       cout << "B: " << prevB << ", P: " << prevP << ", R: " << prevR << endl;
//       cout << "distance: " << d << endl; 
   }
   cout << d << endl;
}


