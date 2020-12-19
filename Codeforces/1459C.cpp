#include <iostream>
#include <algorithm>

using namespace std;

long long GCD(long long a, long long b) {
  if (a == 0) {
    return b;
  }
  if (b == 0) {
    return a;
  }
  return GCD(max(a, b) % min(a, b), min(a, b));
}

int main() {
  long long n, m;
  cin >> n >> m;
  long long a[n];
  long long b[m];
  for (long long i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n);
  for (long long i = 0; i < m; i++) {
    cin >> b[i];
  }
  long long pref[n];
  pref[0] = 0;
  for (long long i = 1; i < n; i++) {
    pref[i] = GCD(pref[i - 1], a[i] - a[0]);
  }
  for (long long i = 0; i < m; i++) {
    cout << GCD(pref[n - 1], b[i] + a[0]) << " ";
  }
}
