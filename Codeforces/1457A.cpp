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
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;
int dist(pair<int,int> p, int r, int c){
  return abs(p.second - c) + abs(p.first - r);
}
void solve(){
  int n,m;
  cin >> n >> m;
  int r,c;
  cin >> r >> c;
  pair<int,int> c1 = {n,1};
  pair<int,int> c2 = {1,m};
  pair<int,int> c3 = {n,m};
  pair<int,int> c4 = {1,1};
  int x = max(dist(c1,r,c),dist(c2,r,c));
  int y = max(dist(c3,r,c),dist(c4,r,c));
  cout << max(x,y) << endl;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
