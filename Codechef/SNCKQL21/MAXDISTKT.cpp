#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#define ll int
using namespace std;
void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    int ans[n];
    for (int i = 0; i < n; i++) {
        ans[i] = 0;
    }
    int cntr = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v[i].first > cntr) {
            v[i].first = cntr;
            cntr++;
        } else if (v[i].first == cntr) {
            v[i].first = cntr;
        }
        swap(v[i].first, v[i].second);
    }
    sort(v.begin(), v.end());
    for(auto p: v) {
        cout << p.second << " ";
    }
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
