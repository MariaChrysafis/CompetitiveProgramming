#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  long double arr[n];
  long double tot = 1;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    tot *= arr[i];
  }
  double ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= arr[i]; j++) {
      for (int k = i + 1; k < n; k++) {
        ans += min((long double)j - 1, arr[k]) * tot / (arr[i] * arr[k]);
      }
    }
  }
  ans /= tot;
  printf("%.6f\n", ans);
}
