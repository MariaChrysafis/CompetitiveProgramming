#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
using namespace std;
void solve(){
  int n;
  cin >> n;
  int arr[n];
  set<int> s;
  map<int,vector<int>> myMap;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
    myMap[arr[i]].push_back(i);
    s.insert(arr[i]);
  }
  int ans = n + 3;
  for(pair<int,vector<int>> p: myMap){
    int x = p.second.size();
    vector<int> v = p.second;
    int cntr = 0;
    for(int i = 0; i < v.size() - 1; i++){
      if(v[i + 1] - v[i] == 1){
        continue;
      }
      cntr++;
    }
    if(v[0] != 0){
      cntr++;
    }
    if(v[v.size() - 1] != n - 1){
      cntr++;
    }
    ans = min(ans,cntr);
  }
  cout << ans << endl;
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
