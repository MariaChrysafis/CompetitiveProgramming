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
int f(vector<int> v, int x, int k){
  int curCount = 0;
  int ans = 0;
  for(int i = 0; i < v.size(); i++){
    if(curCount == 0 && v[i] == x) continue;
    curCount++;
    if(curCount == k){
      ans++;
      curCount = 0;
    }
  }
  return ans + (curCount != 0);
}
void solve(){
  int n,k;
  cin >> n >> k;
  vector<int> arr(n);
  for(int i = 0; i < n; i++) cin >> arr[i];
  int myMin = n;
  for(int i = 1; i <= 100; i++){
    int x = f(arr,i,k);
    myMin = min(x,myMin);
  }
  cout << myMin << endl;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
 
