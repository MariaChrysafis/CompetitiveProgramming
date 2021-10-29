#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
bool dif (pair<int,int> p1, pair<int,int> p2) {
    return (p1.first != p2.second && p1.first != p2.first && p1.second != p2.second && p1.second != p2.first);
}
int main() {
    int N, X;
    cin >> N >> X;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    map<int,vector<pair<int,int>>> myMap;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            myMap[v[i] + v[j]].push_back({i + 1, j + 1});
        }
    }
    for (auto &p: myMap) {
        sort(myMap[p.first].begin(), myMap[p.first].end());
    }
    for (auto &p: myMap) {
        if (myMap[p.first].empty() || myMap[X - p.first].empty()) {
            continue;
        }
        int x = p.first;
        if (x + x == X) {
            if (dif(p.second.back(), p.second[0])) {
                cout << p.second.back().first << " " << p.second.back().second << " " << p.second[0].first << " " << p.second[0].second << endl;
                return 0;
            }
        } else {
            if (dif(p.second.back(), myMap[X - p.first][0])) {
                cout << p.second.back().first << " " << p.second.back().second << " " << myMap[X - p.first][0].first << " " << myMap[X - p.first][0].second << endl;
                return 0;
            }
        }
    }
    cout << "IMPOSSIBLE";
}
