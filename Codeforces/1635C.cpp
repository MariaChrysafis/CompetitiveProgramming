#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int64_t> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        vector<pair<pair<int64_t,int64_t>,int64_t>> vec;
        for (int i = n - 3; i >= 0; i--) {
            if (v[i] <= v[i + 1] - v.back()) {
                continue;
            }
            vec.push_back({{i + 1, i + 2}, n});
            v[i] = min(v[i], v[i + 1] - v.back());
        }
        vector<int64_t> v1 = v;
        sort(v1.begin(), v1.end());
        if (v1 != v) {
            cout << "-1\n";
            continue;
        }
        cout << vec.size() << '\n';
        for (auto& p: vec) {
            cout << p.first.first << " " << p.first.second << " " << p.second << '\n';
        }
        cout << '\n';
    }
}
