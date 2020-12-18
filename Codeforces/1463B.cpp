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
  int myMin = pow(10,9) + 1;
  int ind = 0;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
  }
  long long sum1 = 0;
  long long sum2 = 0;
  for(int i = 0; i < n; i++){
    if(i % 2 == 0){
      sum1 += arr[i] - 1;
    }else{
      sum2 += arr[i] - 1;
    }
  }
  if(sum1 < sum2){
    for(int i = 0; i < n; i++){
      if(i % 2 == 0){
        cout << 1 << " ";
      }else{
        cout << arr[i] << " ";
      }
    }
    cout << endl;
    return;
  }
  for(int i = 0; i < n; i++){
    if(i % 2 == 1){
      cout << 1 << " ";
    }else{
      cout << arr[i] << " ";
    }
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
