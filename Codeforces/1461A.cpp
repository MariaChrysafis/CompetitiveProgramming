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
void solve(){
  int n,k;
  cin >> n >> k;
  for(int i = 0; i < n; i++){
    if(i % 3 == 1) cout << 'a';
    if(i % 3 == 2) cout << 'b';
    if(i % 3 == 0) cout << 'c';
  }
  cout << endl;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
