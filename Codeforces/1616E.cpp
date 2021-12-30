#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

struct segmentTreePoint {
    vector<ll> v;
    vector<ll> vec;
    vector<ll> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    ll get(int x) {
        int cur = x + v.size();
        ll ans = 0;
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

string sub (string s, int l, int r) {
    string str;
    for (int i = l; i <= r; i++) {
        str += s[i];
    }
    return str;
}

void solve() {
    int n;
    cin >> n;
    string s1, s2;
    cin >> s1 >> s2;
    segmentTreePoint st;
    st.resz(n + 1);
    if (s1 < s2) {
        cout << 0 << '\n';
        return;
    }
    map<int, vector<int>> oc;
    for (int i = 0; i < s1.length(); i++) {
        oc[s1[i]].push_back(i);
    }
    for (auto& p: oc) {
        reverse(oc[p.first].begin(), oc[p.first].end());
    }
    ll ans = 1e12;
    ll cost = 0;
    for (int i = 0; i < n; i++) {
        int nxt = 1e9;
        for (char c = 'a'; c < s2[i]; c++) {
            if (!oc[c].empty()) {
                nxt = min(nxt, oc[c].back());
            }
        }
        if (nxt != 1e9) {
            ans = min(ans, cost + abs(i - (nxt + st.get(nxt))));
        }
        if (oc[s2[i]].empty()) {
            break;
        }
        int x = oc[s2[i]].back();
        oc[s2[i]].pop_back();
        cost += abs(i - (x + st.get(x)));
        st.upd(0, x, 1);
    }
    if (ans == 1e12) {
        ans = -1;
    }
    cout << ans << '\n';
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
