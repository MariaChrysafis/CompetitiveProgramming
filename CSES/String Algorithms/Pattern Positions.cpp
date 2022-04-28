#include <bits/stdc++.h>
using namespace std;
class SparseTable {
public:
    vector<vector<int> > dp;
    int query (int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
    SparseTable (vector<int> arr) {
        dp.resize(arr.size());
        for (int i = 0; i < arr.size(); i++) {
            dp[i].resize(32);
            dp[i][0] = arr[i];
        }
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < arr.size(); i++) {
                dp[i][j] = min(dp[i][j - 1], dp[min(i + (1 << (j - 1)), (int)arr.size() - 1)][j - 1]);
            }
        }
    }
};
class SuffixArray {
public:
    vector<int> ans;
    SuffixArray(string s) {
        s += '$';
        int64_t n = s.length();
        vector<int> eq(s.length());
        vector<pair<char, int> > vec;
        for (int i = 0; i < s.length(); i++) {
            vec.push_back(make_pair(s[i], i));
        }
        sort(vec.begin(), vec.end());
        int cntr = 0;
        eq[vec[0].second] = 0;
        for (int i = 1; i < vec.size(); i++) {
            eq[vec[i].second] = eq[vec[i - 1].second] + (vec[i].first != vec[i - 1].first);
        }
        for (int i = 0; (1 << i) < n; i++) {
            vector<pair<int64_t, int> > tot;
            for (int j = 0; j < vec.size(); j++) {
                tot.push_back(make_pair((n + 1) * eq[j] + eq[(j + (1 << i)) % n], j));
            }
            sort(tot.begin(), tot.end());
            eq[tot[0].second] = 0;
            for (int j = 1; j < vec.size(); j++) {
                eq[tot[j].second] = eq[tot[j - 1].second] + (tot[j].first != tot[j - 1].first);
            }
        }
        vector<pair<int,int> > v;
        for (int i = 0; i < n; i++) {
            v.push_back(make_pair(eq[i], i));
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < v.size(); i++) {
            ans.push_back(v[i].second);
        }
    }
};
 
pair<int,int> range (SuffixArray& sfa, string &s, string &str) {
    if (str.length() > s.length()) {
        return make_pair(0, -1);
    }
    s += '$';
    pair<int,int> interval = make_pair(0, (int)sfa.ans.size() - 1);
    for (int i = 0; i < str.length(); i++) {
        int l = interval.first;
        int r = interval.second;
        while (l != r) {
            int m = (l + r)/2;
            if (s[sfa.ans[m] + i] >= str[i]) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        if (s[sfa.ans[l] + i] != str[i]) {
            s.pop_back();
            return make_pair(0, -1);
        }
        interval.first = l;
        l = interval.first;
        r = interval.second;
        while (l != r) {
            int m = (l + r + 1)/2;
            if (s[sfa.ans[m] + i] <= str[i]) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if (s[sfa.ans[l] + i] != str[i]) {
            s.pop_back();
            return make_pair(0, -1);
        }
        interval.second = l;
    }
    s.pop_back();
    return interval;
}
 
int main() {
    string s;
    cin >> s;
    SuffixArray sa(s);
    SparseTable st(sa.ans);
    int t;
    cin >> t;
    while (t--) {
        string str; cin >> str;
        pair<int,int> p = range (sa, s, str);
        if (p.first < 0 || p.second < 0) {
            cout << -1 << '\n';
            continue;
        }
        cout << st.query(p.first,p.second) + 1 << '\n';
    }
}
