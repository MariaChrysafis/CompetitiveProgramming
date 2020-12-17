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
long long b[200001][101];
const long long MOD = pow(10,9) + 7;
void binom(){
  for(long long i = 0; i < 2 * pow(10,5) + 1; i++){
    for(long long j = 0; j < 101; j++){
      if(j == 0){
        b[i][j] = 1;
        continue;
      }
      if(i < j){
        b[i][j] = 0;
        continue;
      }
      b[i][j] = b[i - 1][j - 1] + b[i - 1][j];
      b[i][j] %= MOD;
    }
  }
}
void solve(){
  long long n,m,k;
  cin >> n >> m >> k;
  long long arr[n];
  long long oc[n];
  long long pref[n];
  for(long long i = 0; i < n; i++){
    oc[i] = 0;
  }
  for(long long i = 0; i < n; i++){
    cin >> arr[i];
    arr[i]--;
    oc[arr[i]]++;
  }
  pref[0] = oc[0];
  for(long long i = 1; i < n; i++){
    pref[i] = pref[i - 1] + oc[i];
  }
  long long count = 0;
  for(long long a = 0; a < n; a++){
    if(oc[a] == 0) continue;
    //number of stuff from a to a + k --> pref[a + k] - pref[a - 1]
    long long l;
    if(a == 0) l = 0;
    else l = pref[a - 1];
    long long cnt = pref[min(a + k,n - 1)] - l;
    count += b[cnt][m] - b[cnt - oc[a]][m];
    count %= MOD;
  }
  cout << (count + MOD) % MOD << endl;
}
int main(){
  IO
  binom();
  long long t;
  cin >> t;
  while(t--){
    solve();
  }
}
 
