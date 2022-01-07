#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

vector<int> duplicate (vector<int> v) {
    vector<int> vec = v;
    for (int i: v) {
        vec.push_back(i);
    }
    return vec;
}

int gcd (int a, int b) {
    assert(a >= 0 && b >= 0);
    if (!a || !b) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}

vector<int> factors (int x) {
    set<int> s;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            s.insert(i), s.insert(x/i);
        }
    }
    vector<int> v;
    for (int i: s) {
        v.push_back(i);
    }
    return v;
}

int comp (vector<int> v) {
    v = duplicate(v);
    int myMin = 1e9;
    for (int i: factors(v.size()/2)) {
        for (int offset = 0; offset < i; offset++) {
            set<int> s;
            for (int j = offset; j < v.size(); j += i) {
                s.insert(v[j]);
                if (s.size() >= 2) {
                    break;
                }
            }
            if (s.size() == 1) {
                myMin = min(myMin, i);
            }
        }
    }
    return myMin;
}

void solve () {
    int n;
    cin >> n;
    vector<vector<int>> cycle;
    int p[n], c[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    set<int> s;
    for (int i = 0; i < n; i++) {
        if (!s.count(i)) {
            cycle.emplace_back();
            int cur = i;
            while (!s.count(cur)) {
                cycle.back().push_back(c[cur]);
                s.insert(cur);
                cur = p[cur];
            }
        }
    }
    int ans = 1e9;
    for (int i = 0; i < cycle.size(); i++) {
        ans = min(ans, comp(cycle[i]));
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //cout << comp({2, 4, 2, 4}) << '\n';
    //return 0;
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}
