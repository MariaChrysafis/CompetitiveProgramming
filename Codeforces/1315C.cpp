#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;
void solve() {
  int n;
  cin >> n;
  int arr[n];
  set<int> s1, s2;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    s1.insert(arr[i]);
  }
  for (int i = 1; i <= 2 * n; i++) {
    if (!s1.count(i)) {
      s2.insert(i);
    }
  }
  int ans[2 * n];
  for (int i = 0; i < n; i++) {
    ans[2 * i] = arr[i];
  }
  for (int i = 0; i < n; i++) {
    if (s2.lower_bound(ans[2 * i]) == s2.end()) {
      cout << -1 << endl;
      return;
    }
    ans[2 * i + 1] = *s2.lower_bound(ans[2 * i]);
    s2.erase(ans[2 * i + 1]);
  }
  for (int i = 0; i < 2 * n; i++) {
    cout << ans[i] << " ";
  }
  cout << endl;
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
