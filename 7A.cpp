#include <iostream>

using namespace std;

const int n = 8;
char map[8][8];

int main(void) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> map[i][j];
        }
    }

    int h = 0;
    int v = 0;
    for (int i = 0; i < 8; i++) {
        bool stroke = true;
        bool astroke = true;
        if (map[0][i] == 'B' || map[i][0] == 'B') {
            for (int j = 1; j < 8; j++) {
                if (map[j][i] != 'B') {
                    stroke = false;
                }
                if (map[i][j] != 'B') {
                    astroke = false;
                }
            }
            if (stroke && map[0][i] == 'B') {
                h++;
            }
            if (astroke && map[i][0] == 'B') {
                v++;
            }
        }
    }

    if (h==8) {
        cout << 8 << endl;
    } else cout << h + v << endl;
}