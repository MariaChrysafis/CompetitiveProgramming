#include <iostream>
#include <set>
#include <vector>
#define ll long long
using namespace std;
void solve(){
  ll n;
  cin >> n;
  if(n == 1){
      int a;
      cin >> a;
      cout << 0 << endl;
      return;
  }
  vector<ll> arr(n);
  for(int i = 0; i < n; i++){
      cin >> arr[i];
  }
  set<ll> dif;
  for(int i = 1; i < n; i++){
      dif.insert(arr[i] - arr[i - 1]);
  }
  if(dif.size() >= 3){
      cout << -1 << endl;
      return;
  }
  vector<ll> v;
  for(auto it = dif.begin(); it != dif.end(); ++it){
      v.push_back(*it);
  }
  if(v.size() == 1){
      cout << 0 << endl;
      return;
  }
  ll c = -min(v[0], v[1]);
  ll m = max(v[0], v[1]);
  c += m;
  swap(m, c);
  c %= m;
  //cout << m << " " << c << endl;
  //return;
  vector<ll> newArr(n);
  newArr[0] = arr[0] % m;
  for(int i = 1; i < n; i++){
      newArr[i] = newArr[i - 1] + c;
      newArr[i] %= m;
  }
  /*
  for(int i: newArr){
      cout << i << " ";
  }
  */
  //cout << endl;
  //cout << (newArr == arr) << endl;
  if(newArr != arr){
      cout << -1 << endl;
      return;
  }
  cout << m << " " << c << endl;
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
