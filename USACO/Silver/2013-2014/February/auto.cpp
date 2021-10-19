#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iomanip>
#include <map>
#include <queue>
#include <set>

using namespace std;
bool commonPrefix(string s, string pref) {
    if (s.length() < pref.size()) return false;
    for (int i = 0; i < pref.length(); i++) {
        if (pref[i] != s[i]) {
            return false;
        }
    }
    return true;
}
int main() {
    freopen("auto.in", "r", stdin);
    freopen("auto.out", "w", stdout);
    int W, N;
    cin >> W >> N;
    vector<pair<string,int>> vec(W);
    set<pair<string,int>> vecs;
    map<pair<string,int>, int> oc;
    for (int i = 0; i < W; i++) {
        cin >> vec[i].first;
        vec[i].second = i;
        vecs.insert(vec[i]);
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < vec.size(); i++) {
        oc[vec[i]] = i;
    }
    while (N--) {
        int x;
        cin >> x;
        string s;
        cin >> s;
        auto it = vecs.upper_bound(make_pair(s, -1));
        if (it == vecs.end()) {
            cout << -1 << endl;
            continue;
        }
        auto ans = (*it);
        if (oc[ans] + x - 1 >= vec.size()) {
            cout << "-1\n";
            continue;
        }
        if (!commonPrefix(vec[oc[ans] + x - 1].first, s)) {
            cout << "-1\n";
            continue;
        }
        cout << vec[oc[ans] + x - 1].second + 1 << endl;
    }
}
