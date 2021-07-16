#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
void print(priority_queue<int> q) {
  while (!q.empty()) {
    cout << q.top() << " ";
    q.pop();
  }
  cout << "\n";
}
void solve() {
  int n;
  cin >> n;
  vector<pair<long long, long long> > v(n);
  map<long long, vector<long long> > myMap;
  long long myMax = 0;
  for (int i = 0; i < n; i++) {
    cin >> v[i].first;
    myMax = max(v[i].first, myMax);
  }
  set<int> s;
  for (int i = 0; i < n; i++) {
    cin >> v[i].second;
    myMap[v[i].first].push_back(v[i].second);
    s.insert(v[i].first);
  }
  long long cntr = 0;
  long long pref = 0;
  priority_queue<int> pq;
  for (auto it = s.begin(); it != s.end(); it++) {
    int i = *it;
    if (myMap[i].size() != 0) {
      for (int j = 0; j < myMap[i].size(); j++) {
        pq.push(myMap[i][j]);
        pref += myMap[i][j];
      }
    }
    long long cur = i;
    long long nxt = -1;
    if(s.upper_bound(i) != s.end()) nxt = *(s.upper_bound(i));
    while (!pq.empty() && cur != nxt) {
      pref -= pq.top();
      pq.pop();
      cntr += pref;
      cur++;
    }
  }
  cout << cntr << endl;
}
int main() { solve(); }
