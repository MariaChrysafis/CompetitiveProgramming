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
#define pb push_back
#define pf push_front
#define ll long long
#define mp make_pair
#define REP(i,a) for(int i = 0; i < a; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define trav(a,x) for(auto& a: x)
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;
bool sorted(vector<int> arr){
  vector<int> v = arr;
  sort(v.begin(),v.end());
  return v == arr;
}
void solve(){
  int n,x;
  cin >> n >> x;
  vector<int> arr(n);
  REP(i,n) cin >> arr[i];
  int cntr = 0;
  REP(i,n){
    if(sorted(arr)) break;
    if(arr[i] > x){
      swap(arr[i],x);
      cntr++;
    }
  }
  if(!sorted(arr)){
    cout << -1 << endl; return;
  }
  cout << cntr << endl;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
