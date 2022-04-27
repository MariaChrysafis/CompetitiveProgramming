#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  int arr[k];
  for (int i = 0; i < k; i++) {
    cin >> arr[i];
  }
  string s;
  s.assign(n + 1, 0);
  s[0] = 'L';
  for (int i = 1; i <= n; i++) {
    s[i] = 'L';
    for (int x : arr) {
      if (i - x >= 0 && s[i - x] == 'L') {
        s[i] = 'W';
      }
    }
  }
  for (int i = 1; i < s.length(); i++) {
    cout << s[i];
  }
}
