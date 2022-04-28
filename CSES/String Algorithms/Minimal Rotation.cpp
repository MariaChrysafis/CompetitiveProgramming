#include <bits/stdc++.h>
using namespace std;
 
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
    this->pref.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      pref[i] =
          (pref[i - 1] + (powr[n - i] * (str[i - 1] - 'a' + 1)) % MOD) % MOD;
      pref[i] %= MOD;
    }
  }
  int sz;
  int MOD;
  int BASE;
  vector<int64_t> pref;
  int64_t query(int l, int r) {
    if (l <= r)
      return (ipowr[sz - r - 1] * (pref[r + 1] - pref[l] + MOD) % MOD) % MOD;
    else
      return 0;
  }
};
string s1;
Hasher h1;
int lcp(int l1, int r1, int l2, int r2) {
  int l = 0;
  int r = r1 - l1 + 1;
  while (l < r) {
    int m = (l + r + 1) / 2;
    if (h1.query(l1, l1 + m - 1) == h1.query(l2, l2 + m - 1)) {
      l = m;
    } else {
      r = m - 1;
    }
  }
  return l;
}
int main() {
  powr.push_back(1), ipowr.push_back(1);
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  while (powr.size() != 2e6 + 5) {
    powr.push_back(powr.back() * 31);
    powr.back() %= (int)1e9 + 9;
  }
  ipowr.resize(powr.size());
  ipowr[0] = 1;
  ipowr[1] = inv(powr[1], (int)1e9 + 9);
  for (int i = 2; i < powr.size(); i++) {
    ipowr[i] = (ipowr[i - 1] * ipowr[1]) % ((int)1e9 + 9);
  }
  cin >> s1;
  int n = s1.length();
  s1 += s1;
  h1.resz((int)1e9 + 9, 31, s1);
  int prev = 0;
  for (int i = 1; i < n; i++) {
    int x = lcp(i, i + n - 1, prev, prev + n - 1);
    if (x == n) continue;
    if (s1[i + x] < s1[prev + x]) {
      prev = i;
    }
  }
  for (int i = 0; i < n; i++) {
    cout << s1[(i + prev) % n];
  }
}
