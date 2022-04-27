#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
 
using namespace std;
const int MOD = 1e9 + 7;
int64_t binPow(int64_t x, int64_t y) {
  int64_t res = x;
  int64_t ans = 1;
  while (y > 0) {
    if (y & 1) {
      ans *= res, ans %= MOD;
    }
    res *= res, res %= MOD, y /= 2;
  }
  return ans;
}
int64_t inv(int64_t x) { return binPow(x, (int64_t)MOD - 2); }
int64_t gcd(int64_t a, int64_t b) {
  if (!a || !b) return max(a, b);
  return gcd(max(a, b) % min(a, b), min(a, b));
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<int64_t> fact;
  fact.push_back(1);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i <= n; i++) {
    fact.push_back(fact.back() * fact.size()), fact.back() %= MOD;
  }
  int64_t ans = 0;
  for (int i = 0; i < n; i++) {
    ans += binPow(m, gcd(i, n)), ans %= MOD;
  }
  cout << (ans * inv(n)) % MOD;
}
