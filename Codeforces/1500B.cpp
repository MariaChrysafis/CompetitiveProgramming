// Copy
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define ll long long
using namespace std;
vector<ll> v1;
vector<ll> v2;
ll GCD(ll x, ll y) {
  if (x == 0 || y == 0)
    return max(x, y);
  return GCD(max(x, y) % min(x, y), min(x, y));
}
ll LCM(ll x, ll y) { return (x * y) / GCD(x, y); }
struct NT {
  //CRT blackboxed and copy pasted from random submission
  ll extendedGCD(ll a, ll b, ll &x, ll &y) {
    if (!b) {
      x = 1, y = 0;
      return a;
    }
    ll d = extendedGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
  }
  ll crt(int n, ll *B, ll *A) {
    ll M = A[0], R = B[0], x, y, d;
    for (int i = 1; i < n; i++) {
      d = extendedGCD(M, A[i], x, y);
      if ((R - B[i]) % d)
        return -1;
      x = (R - B[i]) / d * x % A[i];
      R -= M * x;
      M = M / d * A[i];
      R %= M;
    }
    return (R % M + M) % M;
  }
};
vector<ll> v;
ll n, m, g;
vector<ll> ls;
ll smaller(ll n, ll key) {
  if (v.size() == 0) {
    return 0;
  }
  ll left = 0, right = n;
  ll mid;
  while (left < right) {
    mid = (right + left) >> 1;
    if (v[mid] == key) {
      while (mid + 1 < n && v[mid + 1] == key) {
        mid++;
      }
      break;
    }
    else if (v[mid] > key) {
      right = mid;
    }
    else {
      left = mid + 1;
    }
  }
  while (mid > -1 && v[mid] > key) {
    mid--;
  }
  return mid + 1;
}
ll sm(ll x) {
  ll prd = v.size() * (x / g);
  x %= g;
  ll lessThan = smaller(v.size(), x - 1);
  return prd + lessThan;
}
bool valid(ll x, ll k) { return (x - sm(x) >= k); }
ll binSearch(ll l, ll r, ll k) {
  while (l <= r) {
    ll mid = (l + r) / 2;
    if (valid(mid, k) == 1 && (mid == 0 || valid(mid - 1, k) == 0)) {
      return mid;
    }
    else if (valid(mid, k) == 1) {
      r = mid - 1;
    }
    else {
      l = mid + 1;
    }
  }
  return -1;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll k;
  cin >> n >> m >> k;
  g = LCM(n, m);
  vector<pair<ll, ll>> mp(2 * max(n, m) + 1);
  ls.resize(2 * max(n, m) + 1);
  for (int i = 0; i < 2 * max(n, m) + 1; i++) {
    ls[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    ll a;
    cin >> a;
    v1.push_back(a);
    mp[a].first = i + 1;
  }
  for (int i = 0; i < m; i++) {
    ll a;
    cin >> a;
    v2.push_back(a);
    mp[a].second = i + 1;
  }
  NT nt;
  for (int i = 0; i <= 2 * max(n, m); i++) {
    if (mp[i].first != 0 && mp[i].second != 0) {
      ll a = mp[i].first - 1;
      ll b = mp[i].second - 1;
      ll arr1[3];
      arr1[0] = n, arr1[1] = m;
      ll arr2[3];
      arr2[0] = a, arr2[1] = b;
      ll crt = nt.crt(2, arr2, arr1);
      //cout << crt << endl;
      if (crt == -1)
        continue;
      v.push_back(crt);
    }
  }
  sort(v.begin(), v.end());
  ll x = binSearch(0, pow(10, 18) + 20, k);
  cout << x << endl;
}
