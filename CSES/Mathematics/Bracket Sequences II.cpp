#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
const int MOD = 1e9 + 7;
int64_t binPow(int64_t x, int64_t y) {
  int64_t res = x;
  int64_t ans = 1;
  while (y > 0) {
    if (y & 1) {
      ans *= res;
      ans %= MOD;
    }
    res *= res, res %= MOD;
    y /= 2;
  }
  return ans;
}
int64_t inv(int64_t x) { return binPow(x, MOD - 2); }
vector<int64_t> fact;
int64_t combo(int a, int b) {
  if (a == b || b == 0) return 1;
  if (a < b) return 0;
  return (fact[a] * inv((fact[a - b] * fact[b]) % MOD)) % MOD;
}
int64_t c(int n) { return (combo(2 * n, n) - combo(2 * n, n + 1) + MOD) % MOD; }
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  fact.push_back(1);
  for (int i = 0; i <= 2e6; i++) {
    fact.push_back((fact.back() * fact.size()) % MOD);
  }
  int n;
  cin >> n;
  string s;
  cin >> s;
  if (n % 2 == 1) {
    cout << 0;
    return 0;
  }
  int open = 0, closed = 0;
  for (int i = 0; i < s.length(); i++) {
    open += (s[i] == '(');
    closed += (s[i] == ')');
    if (open - closed < 0) {
      cout << 0;
      return 0;
    }
  }
  if ((open - closed) * 2 > n) {
    cout << 0;
    return 0;
  }
  if (n == s.length() || (!closed && open == n / 2)) {
    cout << 1;
    return 0;
  }
  cout << (combo(n - open - closed, n / 2 - open) -
           combo(n - open - closed, n / 2 - open - 1) + MOD) %
              MOD
       << '\n';
}
