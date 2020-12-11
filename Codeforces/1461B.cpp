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
bool inBounds(int i, int j, int n, int m){
  return (i >= 0 && j >= 0 && i < n && j < m);
}
vector<vector<char>> arr;
vector<vector<int>> longest;
int f(int i1, int j1, int st){
  int n = arr.size();
  int m = arr[0].size();
  if(arr[i1][j1] == '.') return 0;
  int i = i1;
  for(int sz = max(st,2); sz <= m + 1; sz++){
    int fl = sz - 1;
    i = i1 + sz - 1;
    if(!inBounds(i,j1 - fl,n,m)) return sz - 1;
    if(longest[i][j1 - fl] < 2 * fl + 1){
      return sz - 1;
    }
  }
}
void solve(){
  int n,m;
  cin >> n >> m;
  vector<vector<int>> val;
  arr.resize(n);
  val.resize(n);
  longest.resize(n);
  for(int i = 0; i < n; i++){
    arr[i].resize(m);
    val[i].resize(m);
    longest[i].resize(m);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      cin >> arr[i][j];
    }
  }
  int count = 0;
  for(int i = 0; i < n; i++){
    longest[i][m - 1] = (arr[i][m - 1] == '*');
    for(int j = m - 2; j >= 0; j--){
      if(arr[i][j] == '.'){
        longest[i][j] = 0;
        continue;
      }
      longest[i][j] = longest[i][j + 1] + 1;
    }
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      int x = f(i,j,1);
      count += x;
    }
  }
  cout << count << endl;
}
int main(){
  IO;
  int t;
  cin >> t;
  while(t--){
    solve();
    arr.clear();
  }
}
