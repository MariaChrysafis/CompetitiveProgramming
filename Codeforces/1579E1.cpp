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
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    deque<int> d;
    d.push_back(v[0]);
    for(int i = 1; i < n; i++) {
        if(v[i] < d.front()) {
            d.push_front(v[i]);
        } else {
            d.push_back(v[i]);
        }
    }
    for(int i = 0; i < n; i++) {
        cout << d.front() << " ";
        d.pop_front();
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
