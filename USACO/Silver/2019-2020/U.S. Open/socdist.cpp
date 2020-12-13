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
long long N,M;
const long long INFTY = pow(10,18);
vector<pair<long long,long long>> v;
int valid(long long x){
  long long counter = 0;
  long long lastTaken = -x;
  for(pair<long long,int> p: v){
    long long px = max(p.first,lastTaken + x);
    long long py = p.second;
    if(py < px) continue;
    long long moves = (py - px)/x + 1;
    lastTaken = (moves - 1) * x + px;
    counter += moves;
  }
  if(counter < N) return 0;
  return 1;
}
long long gl(long long l, long long r, int x){
  long long m;
  while(r - l > 1){
    m = l + (r - l)/2;
    if(valid(m) == x){
      r = m;
    }else{
      l = m;
    }
  }
  return r;
}
int main(){
  freopen("socdist.in", "r", stdin); freopen("socdist.out", "w", stdout);
  IO;
  cin >> N >> M;
  v.resize(M);
  for(int i = 0; i < M; i++){
    long long l,r;
    cin >> l >> r;
    v[i] = make_pair(l,r);
  }
  sort(v.begin(),v.end());
  long long ans = gl(0,pow(10,18),0) - 1;
  cout << ans << endl;
}
