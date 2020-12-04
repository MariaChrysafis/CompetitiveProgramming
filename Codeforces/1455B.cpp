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
int arr[1000001];
void prelim(){
  int x = 2;
  arr[0] = 0;
  for(int i = 1; i <= pow(10,6); i++){
    if(i == x * (x - 1)/2){
      arr[i] = x;
      x++;
      continue;
    }
    arr[i] = x;
  }
  REP(i,pow(10,6) + 1) arr[i]--;
}
void solve(){
  int x;
  cin >> x;
  int right = arr[x];
  int curPos = arr[x] * (arr[x] + 1)/2;
  int off = curPos - x;
  cout << arr[x] + (off == 1) << endl;
}
int main(){
  IO
  prelim();
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
 
 
