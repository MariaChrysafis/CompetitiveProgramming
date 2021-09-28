#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

string sorted(string s) {
    sort(s.begin(), s.end());
    return s;
}

void print (vector<pair<int,int>> vec) {
    cout << vec.size() << '\n';
    for (pair<int,int> p: vec) {
        cout << p.first + 1 << " " << p.second + 1 << '\n';
    }
    cout << '\n';
}

void print (vector<vector<char>> v) {
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[0].size(); j++) {
            cout << v[i][j];
        }
        cout << endl;
    }
}

struct triple {
    int x, y, z;
};

void solve () {
    int n;
    cin >> n;
    multiset<pair<int,int>> ms;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(x == 0) continue;
        ms.insert({x, i});
    }
    vector<pair<int,int>> vec;
    int ans = 0;
    while(ms.size() >= 2) {
        auto it = ms.end();
        it--;
        pair<int,int> p1 = *it;
        ms.erase(it);
        it = ms.end();
        it--;
        pair<int,int> p2 = *it;
        ms.erase(it);
        vec.emplace_back(p1.second, p2.second);
        if(p1.first - 1 != 0) ms.insert({p1.first - 1, p1.second});
        if(p2.first - 1 != 0) ms.insert({p2.first - 1, p2.second});
    }
    cout << vec.size() << endl;
    for(pair<int,int> p: vec) {
        cout << p.first + 1 << " " << p.second + 1 << endl;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
