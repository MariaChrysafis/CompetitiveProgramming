#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
vector<int> generate (vector<int> v, set<int> s) {
    vector<int> pref = {0};
    for (int i = 0; i < v.size(); i++) {
        pref.push_back(pref.back());
        if (s.upper_bound(v[i]) != s.end()) {
            pref.back()++;
            s.erase(s.upper_bound(v[i]));
        }
    }
    return pref;
}
int main () {
    freopen("cardgame.in", "r", stdin);
    freopen("cardgame.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<int> v(N);
    set<int> s;
    for (int i = 1; i <= 2 * N; i++) {
        s.insert(i);
    }
    for (int i = 0; i < N; i++) {
        cin >> v[i];
        s.erase(v[i]);
    }
    vector<int> pref = generate(v, s);
    s.clear();
    for (int i = 1; i <= 2 * N; i++) {
        s.insert(-i);
    }
    for (int i = 0; i < v.size(); i++) {
        s.erase(v[i] = -v[i]);
    }
    reverse(v.begin(), v.end());
    vector<int> suf = generate(v, s);
    reverse(suf.begin(), suf.end());
    int ans = 0;
    for (int i = 0; i < pref.size(); i++) {
        ans = max(ans, pref[i] + suf[i]);
    }
    cout << ans;
}
