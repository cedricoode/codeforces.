#include <iostream>

using namespace std;

int fillOnePerson(int able, int a) {
     int expected = (able + 1) / 2;
     if (a > expected) {
       return expected;
     } else {
       return a;
     }
}

int main() {
    int n;
    int a, b;
    cin >> n >> a >> b;
    int count = 0, index = 0;
    int t = a;
    if (a < b) {
        a = b;
        b = t;
    }
    while (index < n && (a > 0 || b > 0)) {
      //cout << "starting looping: " << index << ", " << a << ", " << b << endl;
      char prev = -1;
      char seat;
      int able = 0;
      do {
          cin >> seat;
          index++;
          //cout << "prev is: " << prev << ", current is: " << seat <<endl;
          if (prev == -1) {
              prev = seat;
              able++;
          } else if (prev != seat) {
              break;
          } else {
              able++;
          }
      } while (index < n);
      if (prev != seat) {
        cin.putback(seat);
        index--;
      }
      //cout << "currently handing: " << prev << ", available seats: " << able << endl;
      if (prev == '.') {
          if ( b == 0 ) {
              int fitted = fillOnePerson(able, a);
              count += fitted;
              a -= fitted;
            //cout << "branch 1: " << able << " " << a << " " << b << " " << count << endl; 
          } else if (b * 2 <= able) {
            able -= b * 2;
            count += b * 2;
            a -= b;
            b = 0;
            int fitted = fillOnePerson(able, a);
            count += fitted;
            a -= fitted;
            //cout << "branch 2: " << able << " " << a << " " << b << " " << count << endl;  
          } else {
              int seatb = able / 2;
              if (b < seatb) {
                able -= b*2;
                count += b * 2;
                a -= b;
                b = 0;
                int fitted = fillOnePerson(able, a);
                count += fitted;
                a -= fitted;
              } else {
                count += able;
                b -= seatb;
                a -= (able - seatb);
                able = 0;
              }
//              cout << "branch 3: " << able << " " << a << " " << b << " " << count << endl;  
          }
          t = a;
          if (a < b) {
              a = b;
              b = t;
          }
 //         cout << " In the middle of calculation: " << count << endl;
      }
    }
    cout << count << endl;
}



