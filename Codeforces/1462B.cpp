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
bool valid(string s1, string s2, string s){
  string str = s.substr(0,s1.length());
  string str1 = s.substr(s.length() - s2.length(),s2.length());
  if(str == s1 && str1 == s2){
    return 1;
  }
  return 0;
}
bool solve(){
  int n;
  cin >> n;
  string s;
  cin >> s;
  if(s.length() < 4) return 0;
  if(s[0] == '2' && s[1] == '0' && s[2] == '2' && s[3] == '0') return 1;
  reverse(s.begin(),s.end());
  if(s[0] == '0' && s[1] == '2' && s[2] == '0' && s[3] == '2') return 1;
  reverse(s.begin(),s.end());
  if(valid("2","020",s)) return 1;
  if(valid("20","20",s)) return 1;
  if(valid("202","0",s)) return 1;
  return 0;
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
