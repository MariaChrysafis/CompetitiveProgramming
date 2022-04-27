#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int x = 0;
    for (int i = 0; i < n; i++) {
      int y;
      cin >> y;
      x ^= y;
    }
    if (x == 0)
      cout << "second\n";
    else
      cout << "first\n";
  }
}
