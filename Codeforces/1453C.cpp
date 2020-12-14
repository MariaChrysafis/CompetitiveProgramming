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
pair<int,int> DOWN(pair<int,int> p1, pair<int,int> p2){
  if(p1.first == -1) return p2;
  if(p2.first == -1) return p1;
  if(p1.first > p2.first) return p1;
  return p2;
}
pair<int,int> UP(pair<int,int> p1, pair<int,int> p2){
  if(p1.first == -1) return p2;
  if(p2.first == -1) return p1;
  if(p1.first < p2.first) return p1;
  return p2;
}
pair<int,int> RIGHT(pair<int,int> p1,pair<int,int> p2){
  if(p1.first == -1) return p2;
  if(p2.first == -1) return p1;
  if(p1.second > p2.second) return p1;
  return p2;
}
pair<int,int> LEFT(pair<int,int> p1, pair<int,int> p2){
  if(p1.first == -1) return p2;
  if(p2.first == -1) return p1;
  if(p1.second < p2.second) return p1;
  return p2;
}
void print(pair<int,int> p){
  cout << p.first << " " << p.second << endl;
}
int max4(int a, int b, int c, int d){
  return max(max(a,b),max(c,d));
}
void solve(){
  int n;
  cin >> n;
  vector<string> arr;
  arr.resize(n);
  string s;
  for(int i = 0; i < n; i++){
    s += " ";
  }
  for(int i = 0; i < n; i++){
    cin >> arr[i];
  }
  vector<map<char,int> > v; //vertical bases
  for(int i = 0; i < n; i++){
    //this gives us a column
    map<char,int> myMap;
    for(int j = 0; j < n; j++){
      int dist;
      dist = max(n - 1 - j, j);
      myMap[arr[j][i]] = max(myMap[arr[j][i]],dist);
    }
    v.push_back(myMap);
  }
  vector<map<char,int> > h; //horizontal bases
  for(int i = 0; i < n; i++){
    map<char,int> myMap;
    for(int j = 0; j < n; j++){
      int dist;
      dist = max(n - 1 - j, j);
      myMap[arr[i][j]] = max(myMap[arr[i][j]], dist);
    }
    h.push_back(myMap);
  }
  map<char,pair<int,int> > Left;
  map<char,pair<int,int> > Right;
  map<char,pair<int,int> > Up;
  map<char,pair<int,int> > Down;
  for(char c = '0'; c <= '9'; c++){
    Left[c] = Right[c] = Up[c] = Down[c] = make_pair(-1,-1);
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      pair<int,int> p = make_pair(i,j);
      char c = arr[i][j];
      Left[c] = LEFT(p,Left[c]);
      Right[c] = RIGHT(p,Right[c]);
      Up[c] = UP(p,Up[c]);
      Down[c] = DOWN(p,Down[c]);
    }
  }
  for(char c = '0'; c <= '9'; c++){
    int best = 0;
    for(int i = 0; i < n; i++){
      int left1 = abs(i - Left[c].second);
      int right1 = abs(i - Right[c].second);
      if(Left[c].second == -1) left1 = 0;
      if(Right[c].second == -1) right1 = 0;
      best = max(best,max(left1,right1) * v[i][c]);
 
      int up1 = abs(i - Up[c].first);
      int down1 = abs(i - Down[c].first);
      if(Up[c].second == -1) up1 = 0;
      if(Down[c].second == -1) down1 = 0;
      best = max(best,max(up1,down1) * h[i][c]);
    }
    cout << best << " ";
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
