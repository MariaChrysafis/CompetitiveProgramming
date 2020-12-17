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
void f(int x){
  int orig = x;
  int nxt = 9;
  while(x - nxt > 0 && nxt != 0){
    x -= nxt;
    nxt--;
  }
  if(nxt == 0){
    cout << -1;
    return;
  }
  cout << x;
  for(int i = nxt + 1; i <= 9; i++){
    cout << i;
  }
  return;
}
void solve(){
  int x;
  cin >> x;
  if(x % 10 == x){
    cout << x;
    return;
  }
  f(x);
  return;
}
 
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
    cout << endl;
  }
}
 
