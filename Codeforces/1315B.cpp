#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
void solve() {
  int a, b, p;
  cin >> a >> b >> p;
  string s;
  cin >> s;
  reverse(s.begin(), s.end());
  vector<int> dp;
  dp.resize(s.size());
  vector<vector<pair<char, int> > > blocks;
  int cur = s[0];
  vector<pair<char, int> > soFar;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == cur) {
      soFar.push_back(make_pair(s[i], i));
    } else {
      blocks.push_back(soFar);
      soFar.clear();
      soFar.push_back(make_pair(s[i], i));
      cur = s[i];
    }
  }
  if (!soFar.empty()) {
    blocks.push_back(soFar);
  }
  vector<int> jump(s.length());
  for (int i = 0; i < s.length(); i++) {
    jump[i] = -1;
  }
  for (int i = 1; i < blocks.size(); i++) {
    jump[blocks[i][0].second] = blocks[i - 1][0].second;
    // cout << blocks[i][0].second << " " << blocks[i - 1][0].second << endl;
  }
  if (s[0] == 'A')
    dp[0] = a;
  else
    dp[0] = b;
  for (int i = 0; i < s.length(); i++) {
    // cout << s[i] << " ";
  }
  // cout << endl;
  // cout << 0 << " ";
  for (int i = 1; i < s.length(); i++) {
    dp[i] = dp[i - 1];
    if (jump[i] != -1) {
      if (i == 1) {
        if (s[i] == 'A')
          dp[i] = a;
        else
          dp[i] = b;
      } else if (s[i] == 'A')
        dp[i] = dp[jump[i]] + a;
      else
        dp[i] = dp[jump[i]] + b;
    }
    // cout << dp[i] << " ";
  }
  //cout << endl;
  dp[0] = 0;
  for (int i = 0; i < s.length(); i++) {
    if (dp[i] > p) {
      cout << s.length() - i + 1 << endl;
      return;
    }
  }
  cout << 1 << endl;
  return;
}
int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
