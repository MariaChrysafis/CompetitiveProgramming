#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    multiset<int> ms;
    int v[n];
    for (int i = 0; i < n; i++) {
      cin >> v[i];
      ms.insert(v[i]);
    }
    for (int i = 0; i < n; i++) {
      auto it = ms.upper_bound(v[i]);
      if (it == ms.end()) it = ms.begin();
      cout << *it << ' ';
      ms.erase(it);
    }
    cout << '\n';
  }
}
