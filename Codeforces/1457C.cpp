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
  int n,p,k;
  cin >> n >> p >> k;
  int arr[n];
  string s;
  cin >> s;
  for(int i = 0; i < s.length(); i++){
    if(s[i] == '1') arr[i] = 1;
    else arr[i] = 0;
  }
  int x,y;
  cin >> x >> y;
  int pref[n];
  for(int i = 0; i < n; i++) pref[i] = -1;
  for(int i = 0; i < k; i++){
    pref[n - 1 - i] = (arr[n - 1 - i] == 0);
  }
  for(int i = n - k - 1; i >= 0; i--){
    pref[i] = pref[i + k] + (arr[i] == 0);
  }
  p--;
  long long myMin = pow(10,9);
  for(int i = p; i < n; i++){
    int num_delete = i - p;
    int num_add = pref[i];
    long long sm = num_delete * y + num_add * x;
    myMin = min(sm, myMin);
    //cout << num_delete * y + num_add * x << " ";
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
