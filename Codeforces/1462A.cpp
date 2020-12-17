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
  int n;
  cin >> n;
  int arr[n];
  for(int i = 0; i < n; i++){
    cin >> arr[i];
  }
  int l = 0;
  int r = n - 1;
  for(int i = 0; i < n; i++){
    if(i % 2 == 0){
      cout << arr[l] << " ";
      l++;
    }else{
      cout << arr[r] << " ";
      r--;
    }
  }
  cout << '\n';
  return;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
 
