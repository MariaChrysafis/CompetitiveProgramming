#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;
int N;
vector<pair<int,int>> cows;
vector<vector<long long>> adj;
vector<int> vec;
map<int,bool> hv;
void dfs(int i, int min_dist){
  hv[i] = 1;
  for(int j = 0; j < N; j++){
    if(!hv[j] && adj[i][j] <= min_dist){
      dfs(j,min_dist);
    }
  }
}
bool pos(int min_dist){
  hv.clear();
  dfs(0,min_dist);
  for(int i = 0; i < N; i++){
    if(!hv[i]){
      return false;
    }
  }
  return true;
}
int binSearch(int l, int r){
  int m;
  while(r - l > 1){
    m = l + (r - l)/2;
    if(pos(vec[m])){
      r = m;
    }else{
      l = m;
    }
  }
  return r;
}
int main(){
  freopen("moocast.in", "r", stdin);
  freopen("moocast.out", "w", stdout);
  cin >> N;
  for(int i = 0; i < N; i++){
    int a,b;
    cin >> a >> b;
    cows.push_back({a,b});
  }
  adj.resize(N);
  for(int i = 0; i < N; i++){
    adj[i].resize(N);
    for(int j = 0; j < N; j++){
      adj[i][j] = pow(cows[i].first - cows[j].first,2) + pow(cows[i].second - cows[j].second,2);
      if(i < j) vec.push_back(adj[i][j]);
    }
  }
  sort(vec.begin(),vec.end());
  int a = binSearch(0,vec.size());
  cout << vec[a] << endl;
}
