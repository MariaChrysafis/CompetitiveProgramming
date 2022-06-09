#include <bits/stdc++.h>
using namespace std;
struct SparseTable {
    vector<vector<int> > dp_max, dp_min;
    int queryMin (int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp_min[l][sz], dp_min[r - (1 << sz) + 1][sz]);
    }
    int queryMax (int l, int r) {
        int sz = log2(r - l + 1);
        return max(dp_max[l][sz], dp_max[r - (1 << sz) + 1][sz]);
    }
    void resz (vector<int> v) {
        dp_max.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp_max[i].resize(32);
            dp_max[i][0] = v[i];
        }
        dp_min = dp_max;
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < v.size(); i++) {
                dp_max[i][j] = max(dp_max[i][j - 1], dp_max[min(i + (1 << (j - 1)), (int)dp_max.size() - 1)][j - 1]);
                dp_min[i][j] = min(dp_min[i][j - 1], dp_min[min(i + (1 << (j - 1)), (int)dp_max.size() - 1)][j - 1]);
            }
        }
    }
};
int first_oc (SparseTable& st, int val, int left) {
    //find the first occurence of val which appears after left
    if (st.queryMin(left, st.dp_max.size() - 1) > val) {
        return -1;
    }
    int l = left;
    int r = st.dp_max.size() - 1;
    while (l != r) {
        int m = (l + r)/2;
        if (st.queryMin(left, m) < val) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return l;
}
vector<int> intersection (vector<int> a, vector<int> b) {
    set<int> ma;
    for (int i: a) {
        ma.insert(i);
    }
    vector<int> tot;
    for (int i: b) {
        if (ma.count(i)) {
            tot.push_back(i);
        }
    }
    return tot;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    SparseTable st[n];
    map<int,vector<int> > myMap[n];
    for (int i = 0; i < n; i++) {
        vector<int> pref; pref.push_back(0);
        string s;
        cin >> s;
        for (int j = 0; j < k; j++) {
            pref.push_back(pref.back() + ((s[j] == ')') ?  -1 : 1));
        }
        for (int j = 0 ; j < pref.size(); j++) {
            myMap[i][pref[j]].push_back(j);
        }
        st[i].resz(pref);
    }
    int ans = 0;
    for (int i = 0; i <= k - 1; i++) {
        //cout << "CAN FIND " << i << '\n';
        vector<vector<int> > vec(n);
        for (int j = 0; j < n; j++) {
            for (int x: myMap[j][st[j].queryMax(i, i)]) {
                if (x <= i) continue;
                //cout << "A\n";
                if (st[j].queryMin(i, x) == st[j].queryMin(i, i)) {
                    vec[j].push_back(x);
                }
                //cout << "B\n";
            }
        }
        vector<int> dum = vec[0];
        for (int j = 0; j < vec.size(); j++) {
            dum = intersection(dum, vec[j]);
        }
        ans += dum.size();
    }
    cout << ans;

}
