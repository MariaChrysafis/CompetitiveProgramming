/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#define ll long long
typedef __uint128_t L;
typedef unsigned long long ull;
using namespace std;
const ll MAX = 7501;
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
  ull reduce(ull a) {
    ull q = (ull)((L(m) * a) >> 64);
    ull r = a - q * b; // can be proven that 0 <= r < 2*b
    return r >= b ? r - b : r;
  }
};
FastMod F(2);
class Problem2Exercise {
public:
  ll MOD;
  unsigned long long n;
  ll subtract(ll a, ll b) { return (a - b + MOD) % MOD; }
  ll add(ll a, ll b) {
    if (a + b >= MOD) {
      return a + b - MOD;
    }
    return a + b;
  }
  ll mult(ll a, ll b) { return F.reduce(a * b); }
  ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
      if (b & 1) {
        res *= a;
        res %= (MOD + 1);
      }
      a = a * a;
      a %= (MOD + 1);
      b >>= 1;
    }
    return res;
  }
  vector<int> primes;
  void sieve(int mx) {
    primes.resize(mx);
    for (int i = 0; i < mx; i++) {
      primes[i] = 1;
    }
    primes[0] = 0;
    primes[1] = 0;
    for (int i = 2; i < mx; i++) {
      if (!primes[i]) {
        continue;
      }
      for (int j = 2 * i; j < mx; j += i) {
        primes[j] = false;
      }
    }
  }
  ll c[MAX + 1][MAX + 1];
  ll fact[MAX + 1];
  void fill() {
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++) {
      fact[i] = mult(fact[i - 1], i);
    }
    for (int i = 0; i < MAX; i++) {
      for (int j = 0; j < MAX; j++) {
        c[i][j] = 0;
      }
    }
    for (int i = 0; i < MAX; i++) {
      c[i][0] = 1;
    }
    for (int i = 1; i < MAX; i++) {
      for (int j = 1; j <= i; j++) {
        c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
      }
    }
  }
  void solve(std::istream &in, std::ostream &out) {
    in >> n >> MOD;
    MOD--;
    F = FastMod(MOD);
    sieve(MAX);
    fill();
    ll ans = 1;
    for (int p = 0; p <= n; p++) {
      if (!primes[p]) {
        continue;
      }
      for (int q = p; q <= n; q *= p) {
        ll DP1[n / q + 1];
        DP1[0] = 1;
        for (int i = 1; i <= n / q; i++) {
          DP1[i] = 0;
          for (int j = 0; j <= i; j++) {
            ll a = mult(fact[j * q - 1], c[q * i - 1][q * j - 1]);
            DP1[i] = add(DP1[i], mult(a,DP1[i - j]));
          }
        }
        ll DP2[n / q + 1];
        for (int i = n / q; i >= 0; i--) {
          DP2[i] = fact[n - i * q];
          for (int j = i + 1; j <= n / q; j++) {
            ll a = mult(DP2[j], DP1[j - i]);
            DP2[i] = subtract(DP2[i], mult(c[n - i * q][n - q * j],a));
          }
        }
        ans = (ans * binpow(p, subtract(fact[n],DP2[0]))) % (MOD + 1);
      }
    }
    out << ans << endl;
  }
};


int main() {
  ios_base::sync_with_stdio(false);
        cin.tie(NULL);
	Problem2Exercise solver;
        std::ifstream in("exercise.in");
	std::ofstream out("exercise.out");
	solver.solve(in, out);
	return 0;
}
