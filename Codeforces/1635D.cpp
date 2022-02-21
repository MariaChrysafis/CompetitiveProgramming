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

using namespace std;
const int MOD = 1e9 + 7;
vector<bool> ts (int64_t x) {
    int cnt = 0;
    int x1 = x;
    while (x1 > 0) {
        x1 /= 2;
        cnt++;
    }
    vector<bool> s;
    for (int i = cnt - 1; i >= 0; i--) {
        if (x & (1 << i)) {
            s.push_back(1);
        } else {
            s.push_back(0);
        }
    }
    return s;
}

vector<bool> f (vector<int64_t> v) {
    vector<bool> okay;
    okay.assign(v.size(), false);
    set<int > s;
    for (int i = 0; i < v.size(); i++) {
        //id[v[i]] = i;
        s.insert(v[i]);
    }
    for (int i1 = 0; i1 < v.size(); i1++) {
        int x = v[i1];
        while (x != 0) {
            if (x % 4 == 0) x /= 4;
            else if (x % 2 == 1) x /= 2;
            else break;
            if (s.count(x)) {
                okay[i1] = true;
            }
        }
    }
    return okay;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t n, p;
    cin >> n >> p;
    vector<int64_t> fib(p + 3);
    fib[0] = fib[1] = 1;
    for (int i = 2; i < fib.size(); i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
    }
    vector<int64_t> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<bool> okay = f(v);
    int64_t ans = 0;
    for (int i = 0; i < v.size(); i++) {
        if (!okay[i] && p >= ts(v[i]).size()) {
            ans += fib[p - ts(v[i]).size() + 2] - 1;
            ans %= MOD;
        }
    }
    cout << ans << '\n';
}
