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
const int INF = pow(10,7);
void print(vector<int> v, int x){
  for(int i: v){
    cout << i + x << endl;
  }
  //cout << endl;
}
int N,M,K;
vector<pair<int,int>> swaps;
vector<int> solve(vector<int> arr){
  for(int i = 0; i < M; i++){
    int a = swaps[i].first;
    int b = swaps[i].second;
    vector<int> v1;
    for(int j = a; j <= b; j++){
      v1.push_back(arr[j]);
    }
    reverse(v1.begin(),v1.end());
    int k = 0;
    for(int j = 0; j < N; j++){
      if(j >= a && j <= b){
        arr[j] = v1[k];
        k++;
      }
    }
  }
  return arr;
}
vector<int> mult(vector<int> v1, vector<int> v2){
  vector<int> ans;
  ans.resize(v1.size());
  for(int i = 0; i < v1.size(); i++){
    ans[i] = v2[v1[i]];
  }
  return ans;
}
vector<int> f(vector<int> v){
  vector<int> powr(v.size());
  vector<int> ans(v.size());
  for(int i = 0; i < v.size(); i++) ans[i] = i;
  powr = v;
  int k = K;
  while(k > 0){
    if(k % 2 == 1){
      ans = mult(ans,powr);
    }
    k /= 2;
    powr = mult(powr,powr);
  }
  return ans;
}
int main(){
  IO
  freopen("swap.in", "r", stdin); freopen("swap.out", "w", stdout);
  cin >> N >> M >> K;
  swaps.resize(M);
  for(int i = 0; i < M; i++){
    int a,b;
    cin >> a >> b;
    a--;
    b--;
    swaps[i] = make_pair(a,b);
  }
  vector<int> arr(N);
  map<int,int> pos;
  vector<int> orig(N);
  for(int i = 0; i < N; i++){
    arr[i] = i;
    orig[i] = i;
  }
  arr = solve(arr);
  vector<int> ans = f(arr);
  print(ans,1);
}
