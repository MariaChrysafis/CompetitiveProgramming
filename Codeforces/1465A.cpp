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
using namespace std;
void solve(){
  int n;
  cin >> n;
  string s;
  cin >> s;
  int counter = 0;
  for(int i = s.length() - 1; i >= 0; i--){
    if(s[i] == ')'){
      counter++;
    }else{
      break;
    }
  }
  //cout << counter << endl;
  if(counter * 2 > s.length()){
    cout << "Yes" << endl;
  }else{
    cout << "No" << endl;
  }
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
