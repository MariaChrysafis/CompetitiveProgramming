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
void solve(){
  int n;
  cin >> n;
  int k;
  cin >> k;
  pair<int,int> arr[n];
  for(int i = 0; i < n; i++){
    int x,y;
    cin >> x >> y;
    arr[i] = mp(x,y);
  }
  int degree[n]; REP(i,n) degree[i] = 0;
  for(int i = 0; i < n; i++){
    for(int j = i + 1; j < n; j++){
      int dist = abs(arr[i].first - arr[j].first) + abs(arr[i].second - arr[j].second);
      if(dist <= k){
        degree[i]++;
        degree[j]++;
      }
    }
  }
  REP(i,n){
    if(degree[i] == n - 1){
      cout << 1 << endl;
      return;
    }
  }
  cout << -1 << endl;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
