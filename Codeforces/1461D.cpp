#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
vector<long long> v;
vector<long long> pref;
set<long long> mySet;
int binSearch(int l, int r, long long key){
  while(l <= r){
    int m = (r + l)/2;
    if(v[m] <= key){
      l = m + 1;
    }else if(v[m] > key){
      r = m - 1;
    }
  }
  return r;
}
void pos(int l, int r){
  if(l < 0 || r >= v.size()){
    return;
  }
  //sum over the interval [l,r] will be pref[r] - pref[l - 1]
  long long sum;
  if(l != 0) {
    sum = pref[r] - pref[l - 1];
  }else{
    sum = pref[r];
  }
  mySet.insert(sum);
  int m = binSearch(l, r, (v[l] + v[r])/2);
  if(m + 1 > r){
    return;
  }
  pos(l,m);
  pos(m + 1,r);
}
void solve(){
  int n,q;
  cin >> n >> q;
  v.resize(n);
  pref.resize(n);
  for(int i = 0; i < n; i++){
    cin >> v[i];
  }
  sort(v.begin(),v.end());
  pref[0] = v[0];
  for(int i = 1; i < n; i++){
    pref[i] = pref[i - 1] + v[i];
  }
  vector<long long> s(q);
  pos(0, n - 1);
  for(int i = 0; i < q; i++){
    cin >> s[i];
    if(mySet.count(s[i])){
      cout << "Yes" << endl;
    }else{
      cout << "No" << endl;
    }
  }
  mySet.clear();
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
