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
long long summ(vector<long long> arr){
  long long ans = 0;
  FOR(i,0,arr.size() - 1){
    ans += abs(arr[i] - arr[i + 1]);
  }
  return ans;
}
void solve(){
  int n;
  cin >> n;
  vector<long long> arr(n);
  long long sum = 0;
  REP(i,n) cin >> arr[i];
  long long myMax = 0;
  int ind = 0;
  for(int i = 1; i < arr.size() - 1; i++){
    long long before = abs(arr[i + 1] - arr[i]) + abs(arr[i] - arr[i - 1]);
    long long x = (arr[i + 1] + arr[i - 1])/2;
    long long after = abs(arr[i + 1] - x) + abs(arr[i - 1] - x);
    //cout << before << " " << after << "; " << endl;
    //cout << before - after << endl;
    if(myMax < before - after){
      myMax = before - after;
      ind = i;
    }
  }
  //what happens at the endpoints
  myMax = max(abs(arr[1] - arr[0]),myMax);
  myMax = max(abs(arr[arr.size() - 1]-arr[arr.size() - 2]),myMax);
  //cout << endl;
  //cout << ind << endl;
  //return;
  //cout << myMax << endl;
  long long stuff = summ(arr);
  cout << stuff - myMax << endl;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
