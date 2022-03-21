#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
using namespace std;
struct segmentTreePoint {
    vector<int64_t> v;
    vector<int64_t> vec;
    vector<int64_t> addLater;
 
    void upd(int dum, int tl, int tr, int &l, int &r, int64_t val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        int64_t mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }
 
    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }
 
    int64_t get(int x) {
        int cur = x + v.size();
        int64_t ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }
 
    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
    }
 
};
 
int64_t binPow (int64_t x, int64_t y, int64_t MOD) {
    int64_t res = x;
    int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x, int64_t MOD) {
    return binPow(x, MOD - 2, MOD);
}
class Hasher {
public:
    Hasher (int mod, int base, int n) {
        this->MOD = mod, this->BASE = base, this->s.assign(n, 0), this->pref.resz(n + 1);
        while (powr.size() != s.size() + 1) {
            powr.push_back(powr.back() * BASE);
            powr.back() %= MOD;
        }
    }
    int MOD;
    int BASE;
    vector<int> s;
    segmentTreePoint pref;
    vector<int64_t> powr = {1};
    void update (int x, char c) {
        int y = c - 'a' + 1;
        pref.upd(x + 1, (int)s.size() + 1, ((y - s[x] + MOD) % MOD * powr[s.size() - x]) % MOD);
        s[x] = y;
    }
    int64_t query (int l, int r) {
        int64_t res = (pref.get(r + 1) % MOD - pref.get(l) % MOD + MOD) % MOD;
        return (inv(powr[s.size() - r], MOD) * res) % MOD;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    string s;
    cin >> s;
    Hasher forward(1e9 + 9, 31, (int)s.length());
    Hasher backward(1e9 + 9, 31, (int)s.length());
    for (int i = 0; i < s.length(); i++) {
        forward.update(i, s[i]);
        backward.update(s.length() - i - 1, s[i]);
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k; char c;
            cin >> k >> c;
            k--;
            forward.update(k, c);
            backward.update(s.length() - k - 1, c);
        } else {
            int a, b;
            cin >> a >> b;
            a--, b--;
            if (forward.query(a, b) == backward.query((int)s.length() - b - 1, (int)s.length() - a - 1)) {
                cout << "YES\n";
                continue;
            }
            cout << "NO\n";
        }
    }
 
}
