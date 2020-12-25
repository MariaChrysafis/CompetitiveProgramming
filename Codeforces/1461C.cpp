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
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL)
using namespace std;
void solve(){
  int n,m;
  cin >> n >> m;
  int arr[n];
  for(int i = 0; i < n; i++){
    cin >> arr[i];
    arr[i]--;
  }
  vector<pair<int,double>> v;
  for(int i = 0; i < m; i++){
    double pi;
    int ri;
    cin >> ri >> pi;
    v.push_back(make_pair(ri,pi));
  }
  int longestPrefix = n;
  for(int i = n - 1; i >= 0; i--){
    if(arr[i] != i){
      break;
    }else{
      longestPrefix--;
    }
  }
  if(longestPrefix == 0){
    cout << 1 << endl;
    return;
  }
  //cout << longestPrefix << endl;
  double p1 = 1;
  for(int i = 0; i < m; i++){
    int x = v[i].first;
    if(x >= longestPrefix){
      p1 *= (1 - v[i].second);
    }
  }
  cout << 1  - p1 << endl;
}
int main(){
  IO;
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
 
