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
bool valid(vector<int> v, int x){
  int counter = 0;
  for(int i = 0; i < v.size(); i++){
    if((counter + v[i] == x)){
      counter = 0;
      continue;
    }
    if((counter + v[i] > x)){
      return false;
    }
    counter += v[i];
  }
  return true;
}
vector<int> factors(long long n){
  vector<int> v;
  for(int i = 1; i <= sqrt(n); i++){
    if(n % i == 0){
      v.push_back(i);
    }
  }
  vector<int> u;
  for(int i: v){
    if(i * i == n) continue;
    u.push_back(n/i);
  }
  reverse(u.begin(),u.end());
  for(int i: u){
    v.push_back(i);
  }
  return v;
}
void solve(){
  int n;
  cin >> n;
  vector<int> arr(n);
  long long sum = 0;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
    sum += arr[i];
  }
  vector<int> v = factors(sum);
  reverse(v.begin(),v.end());
  for(int i: v){
    if(sum % i == 0){
      bool b = valid(arr,sum/i);
      if(b){
        cout << n - i << endl;
        return;
      }
    }
  }
  cout << endl;
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
