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
const int MOD = 1e9 + 9;

int gcd (int x, int y) {
    if (!x || !y) return max(x,y);
    return gcd(max(x, y) % min(x, y), min(x, y));
}

struct segmentTreePoint {
    vector<int> v;
    vector<int> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, int val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    int get(int x) {
        int cur = x + v.size();
        int ans = 0;
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
        addLater.resize(v.size() * 2);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int cnt[n + 1];
    for (int i = 0; i <= n; i++) {
        cnt[i] = 0;
    }
    int mx = 10;
    vector<vector<segmentTreePoint>>v(mx);
    for (int i = 1; i < mx; i++) {
        v[i].resize(i);
        for (int j = 0; j < i; j++) {
            v[i][j].resz(n/i + 3);
        }
    }
    while (k--) {
        int a, l, d;
        cin >> a >> l >> d;
        a--;
        if (d >= mx) {
            for (int i = a; i <= a + (l - 1) * d; i += d) {
                cnt[i]++;
            }
        } else {
            v[d][a % d].upd((a - a % d)/d, (a - a % d)/d + l - 1, 1);
            //cout << d << " " << a % d << " " << (a - a % d)/d << " " << (a - a % d)/d + l - 1 << '\n';
            //cout << st.get((a - a % d)/d + l - 1) << '\n';
        }
    }
    for (int i = 1; i < mx; i++) {
        for (int j = 0; j < i; j++) {
            for (int x = 0; x <= n/i + 2; x++) {
                cnt[i * x + j] += v[i][j].get(x);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << cnt[i] << ' ';
    }
}
