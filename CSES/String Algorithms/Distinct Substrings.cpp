#include <bits/stdc++.h>
using namespace std;
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
 
 
int64_t binPow(int64_t x, int64_t y, int64_t MOD) {
  x %= MOD;
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
int64_t inv(int64_t x, int64_t MOD) { return binPow(x, MOD - 2, MOD); }
vector<int64_t> powr;
vector<int64_t> ipowr;
struct Hasher {
  void resz(int mod, int base, string str) {
    int n = str.size();
    this->sz = n;
    this->MOD = mod, this->BASE = base;
    powr.push_back(1);
    for (int i = 0; i <= n; i++) {
        powr.push_back(powr.back() * base), powr.back() %= MOD;
    }
    ipowr.push_back(1);
    ipowr.push_back(inv((int64_t)base, (int64_t)MOD));
    for (int i = 1; i <= n; i++) {
        ipowr.push_back((ipowr[i - 1] * ipowr[1]) % MOD);
    }
    pref.push_back(0);
    for (int i = 0; i < str.length(); i++) {
        pref.push_back((pref.back() * base + str[i]) % MOD);
    }
  }
  int sz;
  int MOD;
  int BASE;
  vector<int64_t> pref;
  int64_t query(int l, int r) {
    return (1 * (pref[r + 1] - (pref[l] * powr[r - l + 1]) % MOD + MOD) % MOD) % MOD;
  }
};
 
int lcp (int x, int y, Hasher& h) {
    int l = 0;
    int r = 1e5;
    while (l != r) {
        int m = (l + r + 1)/2;
        if (x + m - 1 >= h.sz || y + m - 1 >= h.sz || h.query(x, x + m - 1) != h.query(y, y + m - 1)) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    return l;
}
 
int main() {
    string s;
    cin >> s;
    Hasher h1;
    h1.resz((int)1e9 + 7, 31, s);
    SuffixArray sa(s);
    s += '$';
    int64_t ans = (int64_t) s.length() * (int64_t)(s.length() - 1)/2;
    for (int i = 2; i < sa.ans.size(); i++) {
        ans -= lcp(sa.ans[i], sa.ans[i - 1], h1);
    }
    cout << ans;
}
