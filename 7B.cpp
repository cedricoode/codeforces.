#include <iostream>
#include <string>
#include <map>
#include <utility>

using namespace std;

typedef pair<int, int> Node;
typedef map<int, int>::iterator Iterator;
typedef map<int, int> Map;

bool alloc(int size, int);
bool erase(int pos);
void _erase(int pos);

int m, t, p, temp, mem[100][2];
Map tbl, r_tbl; // assigned table
Map lcd; // first byte size
Map avl; // available map

int main(void)
{
    cin >> t >> m;
    string op;
    // map<int, Node> locks;
    // list<vector<int> > locks;

    avl.insert(make_pair(0, m));

    for (int i = 0; i < t; i++)
    {
        cin >> op;
        if (op[0] == 'a')
        {
            cin >> temp;
            if (alloc(temp, p+1)) {
                p++;
                cout << p << endl;
            }else
                cout << "NULL" << endl;
        }
        else if (op[0] == 'e')
        {
            cin >> temp;
            if (!erase(temp))
                cout << "ILLEGAL_ERASE_ARGUMENT" << endl;
        }
        else
        {
            Iterator itr = avl.begin();
            while (avl.size() >= 1 && itr->first + itr->second != m)
            {
                temp = lcd[itr->first + itr->second];
                int p = r_tbl[itr->first+itr->second];
                erase(p);
                alloc(temp, p);
                itr = avl.begin();
            }
        }
    }
}

bool alloc(int t, int p)
{
    for (Iterator itr = avl.begin(); itr != avl.end(); ++itr)
    {
        if (itr->second >= t)
        {
            lcd.insert(make_pair(itr->first, t));
            tbl.insert(make_pair(p, itr->first));
            r_tbl.insert(make_pair(itr->first, p));

            if (itr->second > t)
            {
                avl.insert(make_pair(itr->first + t, itr->second - t));
            }

            avl.erase(itr);
            return true;
        }
    }
    return false;
}

bool erase(int id)
{
    Iterator itr = tbl.find(id);
    if (itr == tbl.end()) {
        return false;
    } else {
        _erase(itr->second);
        r_tbl.erase(itr->second);
        tbl.erase(itr);
        return true;
    }
}

void _erase(int pos)
{
    int end = lcd[pos];
    int start = pos;

    Iterator temp = avl.find(lcd[pos] + pos);
    if (temp != avl.end())
    {
        end += temp->second;
        int tod = temp->first;
        if (temp != avl.begin()) {
            --temp;
            if (temp->first + temp->second == pos) {
                start = temp->first;
                end += temp->second;
                avl.erase(temp->first);
            }
        }
        avl.erase(tod);        
    } else
    {
        for (Iterator itr = avl.begin(); itr != avl.end(); ++itr) {
            if (itr->first + itr->second == start) {
                start = itr->first;
                end += itr->second;
                avl.erase(itr);
                break;
            } else if (itr->first + itr->second > start) {
                break;
            }
        }
    }
    avl.insert(make_pair(start, end));
    lcd.erase(pos);
}
