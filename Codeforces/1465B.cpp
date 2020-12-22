#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;
//140183543337950
bool okay(long long n) {
  vector<int> v;
  long long x = n;
  while (x > 0) {
    v.push_back(x % 10);
    x /= 10;
  }
  for (int i: v) {
    if (i == 0) {
      continue;
    }
    if (n % i != 0) {
      return false;
    }
  }
  return true;
}
void solve() {
  long long n;
  cin >> n;
  for (int i = 0; i < 20000; i++) {
    bool b = okay(n + i);
    if (b) {
      cout << n + i << endl;
      return;
    }
  }
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
