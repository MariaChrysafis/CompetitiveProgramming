#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
vector<int> v;
vector<int> arr;
vector<pair<int,int>> vec;
const int INF = pow(10,9);
int cl(int x){
  int pwr = 1;
  while(pwr < x){
    pwr *= 2;
  }
  return pwr;
}
pair<int,int> merge(pair<int,int> p1, pair<int,int> p2){
  return make_pair(p1.first,p2.second);
}
int build(int ind){
  if(ind >= v.size() - 1){
    arr[ind] = v[ind - (v.size() - 1)];
    return arr[ind];
  }
  arr[ind] = build(2 * ind + 1) ^ build(2 * ind + 2);
  return arr[ind];
}
pair<int,int> build2(int ind){
  if(ind >= v.size() - 1){
    int x = ind - (v.size() - 1);
    vec[ind] = make_pair(x,x);
    return vec[ind];
  }
  vec[ind] = merge(build2(2 * ind + 1),build2(2 * ind + 2));
  return vec[ind];
}
int interval(int i, int L, int R){
  if(vec[i].first > R || vec[i].second < L){
    return 0;
  }
  if(vec[i].first >= L && vec[i].second <= R){
    return arr[i];
  }
  int a = interval(2 * i + 1,L,R);
  int b = interval(2 * i + 2,L,R);
  return a ^ b;
}
int main(){
  int n, q;
  cin >> n >> q;
  int x = cl(n);
  v.resize(x);
  for(int i = 0; i < n; i++){
    cin >> v[i];
  }
  for(int i = n + 1; i < x; i++){
    v[i] = 0;
  }
  arr.resize(2 * x);
  vec.resize(2 * x);
  build(0);
  build2(0);
  while(q--){
    int a,b;
    cin >> a >> b;
    a--;
    b--;
    int ans = interval(0,a,b);
    cout << ans << endl;
  }
  return 0;
}
