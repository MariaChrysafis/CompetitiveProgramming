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
  pair<int,int> arr[n];
  vector<pair<int,char> > v;
  for(int i = 0; i < n; i++){
    cin >> arr[i].first >> arr[i].second;
    v.push_back(make_pair(arr[i].first,'S'));
    v.push_back(make_pair(arr[i].second,'E'));
  }
  sort(v.begin(),v.end());
  map<int,pair<int,int> > myMap;
  map<int,int> mm;
  int o = 0;
  int c = 0;
  for(int i = 0; i < 2 * n; i++){
    int x = v[i].first;
    char ch = v[i].second;
    //myMap[x - 1] = make_pair(o,c);
    if(ch == 'S'){
      o++;
      myMap[x] = make_pair(o,c);
    }else{
      c++;
      myMap[x] = make_pair(o,c);
      mm[x]++;
      //c++;
    }
  }
  int maxCount = 0;
  for(int i = 0; i < n; i++){
    int x = arr[i].first;
    int y = arr[i].second;
    int count = myMap[y].first - myMap[x].second + mm[x];
    //cout << myMap[y].first << " " << myMap[x - 1].second << endl;
    maxCount = max(maxCount,count);
  }
  cout << n - maxCount << endl;
}
int main(){
  IO
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
