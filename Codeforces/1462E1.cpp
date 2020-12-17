Copy
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
  long long n;
  cin >> n;
  long long arr[n];
  map<long long,long long> myMap;
  for(long long i = 0; i < n; i++){
    cin >> arr[i];
    myMap[arr[i]]++;
  }
  long long count = 0;
  set<long long> s;
  for(long long i = 0; i < n; i++){
    long long ps = s.size();
    s.insert(arr[i]);
    if(s.size() == ps) continue;
    long long a = arr[i];
    count += (myMap[a] * (myMap[a] - 1) * (myMap[a] - 2))/6;
    count += myMap[a] * myMap[a + 1] * myMap[a + 2];
    count += myMap[a] * myMap[a + 1] * (myMap[a + 1] - 1)/2;
    count += myMap[a] * myMap[a + 2] * (myMap[a + 2] - 1)/2;
    count += myMap[a] * (myMap[a] - 1) * myMap[a + 1]/2;
    count += myMap[a] * (myMap[a] - 1) * myMap[a + 2]/2;
  }
  cout << count << endl;
}
int main(){
  IO
  //{a,a,a}
  //{a,a+1,a+2}
  //{a,a+1,a+1}
  //{a,a+2,a+2}
  //{a,a,a+1}
  //{a,a,a+2}
  long long t;
  cin >> t;
  while(t--){
    solve();
  }
}
