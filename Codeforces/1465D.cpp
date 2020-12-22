#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
long long solve(string str, string s, long long x, long long y){
  int n = str.length();
  long long pref[2][n];
  pref[0][0] = (str[0] == '0');
  pref[1][0] = (str[0] == '1');
  for (int i = 1; i < n; i++) {
    pref[0][i] = pref[0][i - 1] + (str[i] == '0');
    pref[1][i] = pref[1][i - 1] + (str[i] == '1');
  }
  long long suf[2][n + 1];
  suf[0][n] = suf[1][n] = 0;
  for (int i = n - 1; i >= 0; i--) {
    suf[0][i] = suf[0][i + 1] + (str[i] == '0');
    suf[1][i] = suf[1][i + 1] + (str[i] == '1');
  }
  long long sum = 0;
  for (int i = 1; i < n; i++) {
    if (str[i] == '0') {
      sum += y * pref[1][i - 1];
    }
    else {
      sum += x * pref[0][i - 1];
    }
  }
  long long myMin = sum;
  vector<int> v;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '?') {
      v.push_back(i);
    }
  }
  reverse(v.begin(), v.end());
  int other = 0;
  for (int i: v) {
    long long subtract,add;
    if(i != 0) {
      subtract = pref[1][i - 1] * y + (suf[1][i + 1] + other) * x;
      add = pref[0][i - 1] * x + (suf[0][i + 1] - other) * y;
    }else{
      subtract = (suf[1][i + 1] + other) * x;
      add = (suf[0][i + 1] - other) * y;
    }
    sum += add - subtract;
    if(sum < myMin){
      myMin = sum;
    }
    other++;
  }
  return myMin;
}
string conv(string s){
  string str = s;
  for(int i = 0; i < s.length(); i++){
    if(s[i] == '?'){
      str[i] = '0';
    }
  }
  return str;
}
string reflect(string s){
  for(int i = 0; i < s.length(); i++){
    if(s[i] == '0'){
      s[i] = '1';
    }else if(s[i] == '1'){
      s[i] = '0';
    }
  }
  return s;
}
int main() {
  string s;
  cin >> s;
  long long x, y;
  cin >> x >> y;
  long long a = solve(conv(s),s,x,y);
  long long b = solve(conv(reflect(s)),s,y,x);
  cout << min(a,b) << endl;
}
