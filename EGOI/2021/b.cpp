#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ar array
 
template<class T, int n> struct BIT { //try to always use long long
    vector<T> bit;
    BIT() {
        bit.resize(n + 1);
    }
    void upd(int i, T val) {
        for (++i; i <= n; i += i & -i)
            bit[i] += val;
    }
    T qry(int i) {T res = 0;
        for (++i; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }
    T qry(int l, int r) {
        return qry(r) - qry(l - 1);
    }
};
 
int n, a[1000000], oc[500000], ans[500000];
BIT<int, 1000000> b;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    fill(oc, oc + n, -1);
    for (int i = 0; i < 2 * n; ++i) {
        cin >> a[i], --a[i];
        if (oc[a[i]] == -1) {
            oc[a[i]] = i;
            b.upd(i, 1);
        }
        else {
            ans[a[i]] = b.qry(oc[a[i]] + 1, i - 1);
            b.upd(oc[a[i]], -2);
            b.upd(i, 1);
        }
    }
    long long cntr = 0;
    for (int i = 0; i < n; ++i) cntr += ans[i];
    cout << cntr/2 + n << endl;
    return 0;
}
