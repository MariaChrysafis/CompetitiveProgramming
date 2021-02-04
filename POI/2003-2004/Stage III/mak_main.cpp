#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
const int MAX = 10003;
vector<int> primes = {
    1,
    2,
    3,
    5,
    7,
    11,
    13,
    17,
    19,
    23,
    29,
    31,
    37,
    41,
    43,
    47,
    53,
    59,
    61,
    67,
    71,
    73,
    79,
    83,
    89,
    97,
    101,
    103,
    107,
    109,
    113,
    127,
    131,
    137,
    139,
    149,
    151,
    157,
    163,
    167,
    173,
    179,
    181,
    191,
    193,
    197,
    199,
    211,
    223,
    227,
    229,
    233,
    239,
    241,
    251,
    257,
    263,
    269,
    271,
    277,
    281,
    283,
    293,
    307,
    311,
    313,
    317,
    331,
    337,
    347,
    349,
    353,
    359,
    367,
    373,
    379,
    383,
    389,
    397,
};
double dp[200][MAX + 1];
long long inv[200][MAX + 1];
map<int, int> myMap;
int rt(int p){
  for(int i = 1; i < primes.size(); i++){
    if(p % primes[i] == 0){
      return primes[i];
    }
  }
  return -1;
}
vector<int> ans(int a) {
  int sum = 0;
  vector<int> v;
  int x = primes.size() - 1;
  while (x > 0) {
    int b = inv[x][a - sum];
    if (b == 0) {
      break;
    }
    v.push_back(b);
    x = myMap[rt(b)] - 1;
    //cout << x << " " << b << endl;
    sum += b;
  }
  //cout << endl;
  return v;
}

vector<int> convert(vector<int> v, int n) {
  vector<int> myVec;
  for (int i = 0; i < n; i++) {
    myVec.push_back(i + 1);
  }
  vector<vector<int>> vec;
  vec.resize(v.size());
  int cntr = 1;
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v[i]; j++) {
      vec[i].push_back(cntr);
      cntr++;
    }
  }
  myVec.clear();
  for (int i = 0; i < vec.size(); i++) {
    for (int j = 0; j < vec[i].size() - 1; j++) {
      myVec.push_back(vec[i][j] + 1);
    }
    myVec.push_back(vec[i][0]);
  }
  return myVec;
}
int main() {
  for (int i = 0; i < primes.size(); i++) {
    for (int j = 0; j < MAX; j++) {
      dp[i][j] = 0;
    }
  }
  for (int i = 1; i < primes.size(); i++) {
    for (int j = 0; j < MAX; j++) {
      dp[i][j] = dp[i - 1][j];
      inv[i][j] = inv[i - 1][j];
      long long pwr = primes[i];
      while (pwr <= j) {
        double pos1 = dp[i - 1][j - pwr] + log(1.0 * pwr);
        if (dp[i][j] < pos1) {
          inv[i][j] = pwr;
          dp[i][j] = pos1;
        }
        pwr *= primes[i];
      }
    }
  }
  for (int i = 0; i < primes.size(); i++) {
    myMap[primes[i]] = i;
  }
  int t;
  cin >> t;
  while (t--) {
    int a;
    cin >> a;
    if (a == 1) {
      cout << 1 << endl;
      continue;
    }
    vector<int> v = ans(a);
    int sum = 0;
    for (int i : v) {
      sum += i;
    }
    while (sum != a) {
      v.push_back(1);
      sum++;
    }
    sort(v.begin(), v.end());
    vector<int> vec = convert(v, a);
    for (int i : vec) {
      cout << i << " ";
    }
    cout << endl;
  }
}
