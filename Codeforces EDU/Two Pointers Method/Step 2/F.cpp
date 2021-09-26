#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

#define ll long long
using namespace std;

struct segmentTreeMin {
    vector<ll> v;
    vector<ll> val;

    ll ID = 1e18 + 1;

    ll op(ll a, ll b) {
        return min(a,b);
    }

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), y);
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }
};

struct segmentTreeMax {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return max(a,b);
    }

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), y);
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }
};

void solve() {
    segmentTreeMin st1;
    segmentTreeMax st2;
    int n;
    cin >> n;
    st1.resz(n), st2.resz(n);
    long long k;
    cin >> k;
    vector<long long> vec(n);
    for(int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        vec[i] = x;
        st1.update(i, x);
        st2.update(i, x);
    }
    int l = 0;
    int r = 0;
    int atMost[n];
    long long myMin = vec[0];
    long long myMax = vec[0];
    while(true) {
        if (max(myMax, vec[r + 1]) - min(myMin, vec[r + 1]) <= k) {
            myMax = max(myMax, vec[r + 1]);
            myMin = min(myMin, vec[r + 1]);
            r++;
        } else {
            atMost[l] = r;
            l++;
            myMin = st1.query(l, r);
            myMax = st2.query(l, r);
        }
        if(r == n - 1) {
            break;
        }
    }
    while(l != n) {
        atMost[l] = n - 1;
        l++;
    }
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        //cout << i << ' ';
        ans += atMost[i] - i + 1;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
