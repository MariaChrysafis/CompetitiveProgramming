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
bool solve(){
  long long a,b,c;
  cin >> a >> b >> c;
  long long sum = (a + b + c);
  //x enhanced shots
  //y normal shots
  //3 * x + y = sum
  //(sum - 2 * x)/x = 7
  //sum/x = 9
  if(sum % 9 != 0){
    return false;
  }
  long long x = sum/9;
  if(a < x || b < x || c < x) return false;
  return true;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    bool b = solve();
    if(b){
      cout << "YES" << endl;
    }else{
      cout << "NO" << endl;
    }
  }
}
 
