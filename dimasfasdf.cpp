#include <bits/stdc++.h>
using namespace std;
struct SparseTable {
    vector<vector<int> > dp_min;
    int queryMin (int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp_min[l][sz], dp_min[r - (1 << sz) + 1][sz]);
    }
    void resz (vector<int> v) {
        dp_min.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp_min[i].resize(17);
            dp_min[i][0] = v[i];
        }
        for (int j = 1; j < dp_min[0].size(); j++) {
            for (int i = 0; i < v.size(); i++) {
                dp_min[i][j] = min(dp_min[i][j - 1], dp_min[min(i + (1 << (j - 1)), (int)dp_min.size() - 1)][j - 1]);
            }
        }
    }
};
int rng (vector<int>&v, int l, int r) {
    int ans = 0;
    for (int i: v) {
        ans += (i >= l && i <= r);
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    SparseTable st[n];
    int64_t hash[k + 1];
    for (int i = 0; i <= k; i++) {
        hash[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        vector<int> pref; pref.push_back(0);
        string s;
        cin >> s;
        for (int j = 0; j < k; j++) {
            pref.push_back(pref.back() + ((s[j] == ')') ?  -1 : 1));
        }
        st[i].resz(pref);
    }
    int64_t MOD = 1e9 + 9;
    int64_t powr = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            hash[j] += (st[i].queryMin(j, j) + MOD) % MOD * powr;
            hash[j] %= MOD;
        }
        powr *= 100;
        powr %= MOD;
    }
    map<int,vector<int> > myMap;
    for (int i = 0; i <= k; i++) {
        myMap[hash[i]].push_back(i);
    }
    int ans = 0;
    for (int i = 0; i <= k - 1; i++) { //k is small
        int myMax = k;
        for (int j = 0; j < n; j++) {
            if (st[j].queryMin(i, k) >= st[j].queryMin(i, i)) continue;
            int l = i + 1;
            int r = k;
            while (l != r) {
                int m = (l + r + 1)/2;
                if (st[j].queryMin(i, m) < st[j].queryMin(i, i)) {
                    r = m - 1;
                } else {
                    l = m;
                }
            }
            myMax = min(myMax, l);
        }
        ans += rng(myMap[hash[i]], i + 1, myMax);
    }
    cout << ans;

}
