#include <iostream>
#include <map>
#include <set>

using namespace std;

void outputPositionMap(map<long long, set<int>> &);
void outputCountMap(map<long long, int> &);
void outputMap(map<int, long long> &);

int main() {
    int n;
    cin >> n;
    map<long long, set<int>> positionMap;
    map<long long, int> countMap;
    for (int i = 0; i < n ; i++) {
        long long key = 0;
        cin >> key;
        set<int> *atKey = &positionMap[key];
        atKey->insert(i);
        if (atKey->size() > 1) {
            countMap[key] = atKey->size();
        }
    }

    //outputPositionMap(positionMap);
    //outputCountMap(countMap);
    while (!countMap.empty()) {
       long long minKey = countMap.begin()->first; 
       //cout << "minKey: " << minKey << endl;
       // popInsert
       set<int> *atKey = &positionMap[minKey];
       set<int>::iterator it = atKey->begin();
       int first = *it++;
       int second = *it;
       //cout << "first: " << first << ", second: " << second << endl;
       atKey->erase(first);
       atKey->erase(second);
       if (atKey->empty()) {
           positionMap.erase(minKey);
       }
       long long newKey = 2LL * minKey;
       set<int> *newAtKey = &positionMap[newKey];
       newAtKey->insert(second);
       // update countMap
       countMap[minKey] -= 2;
       if (countMap[minKey] < 2) {
           countMap.erase(minKey);
       }
       if (newAtKey->size() > 1) {
           countMap[newKey] = newAtKey->size();
       }
       //outputPositionMap(positionMap);
       //outputCountMap(countMap);
    }
    map<int, long long> output;
    for (map<long long, set<int>>::iterator it = positionMap.begin(); it != positionMap.end(); it++) {
        long long key = it->first;
        int value = *it->second.begin();
        output[value] = key;
    }
    outputMap(output);
}


void outputPositionMap(map<long long, set<int>> & positionMap) {
     for (map<long long, set<int>>::iterator it = positionMap.begin(); it != positionMap.end(); it++) {
         cout << it->first << ", size: " << it->second.size() << ", countent: ";
         for (set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
             cout << *it2 << ", ";
         }
         cout << endl;
     } 
}



void outputCountMap(map<long long, int> &countMap) {
    for (map<long long, int>::iterator it = countMap.begin(); it != countMap.end(); it++) {
        cout << "key: " << it->first << ", value: " << it->second << endl;
    }
}


void outputMap(map<int, long long> &output) {
    for (map<int, long long>::iterator it = output.begin(); it != output.end(); it++) {
        cout << it->second << " ";
    }
    cout << endl;
}
