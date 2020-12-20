#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
struct Interval{
  int l,r;
};
const int INF = pow(10,9) + 7;
int n,m;
vector<int> v;
vector<pair<int,int>> arr;
vector<Interval> vec;
int np2(int x){
  int pwr = 1;
  while(x > pwr){
    pwr *= 2;
  }
  return pwr;
}
pair<int,int> Merge(pair<int,int> p1, pair<int,int> p2){
  if(p1.first == p2.first){
    return {p1.first,p1.second + p2.second};
  }
  if(p1.first < p2.first){
    return p1;
  }
  return p2;
}
pair<int,int> build(int i){
  if(i >= v.size() - 1){
    arr[i] = make_pair(v[i - v.size() + 1],1);
    return arr[i];
  }
  pair<int,int> p1 = build(2 * i + 1);
  pair<int,int> p2 = build(2 * i + 2);
  arr[i] = Merge(p1,p2);
  return arr[i];
}
Interval merge(Interval a, Interval b){
  return {a.l,b.r};
}
Interval build_interval(int i){
  if(i >= v.size() - 1){
    int x = v.size();
    vec[i] = {i - x + 1, i - x + 1};
    return vec[i];
  }
  Interval a = build_interval(2 * i + 1);
  Interval b = build_interval(2 * i + 2);
  vec[i] = merge(a,b);
  return vec[i];
}
pair<int,int> find_interval(int i, int L, int R){
  if(vec[i].l >= L && vec[i].r <= R){
    return arr[i];
  }
  if(vec[i].l > R || vec[i].r < L){
    return {INF + 1,0};
  }
  pair<int,int> p1 = find_interval(2 * i + 1,L,R);
  pair<int,int> p2 = find_interval(2 * i + 2,L,R);
  return Merge(p1,p2);
}
void update(int k, int x){
  int ind = k + v.size() - 1;
  arr[ind] = {x,1};
  while(ind != 0){
    ind = (ind - 1)/2;
    arr[ind] = Merge(arr[2 * ind + 1],arr[2 * ind + 2]);
  }
}
int main(){
  cin >> n >> m;
  int x = np2(n);
  v.resize(x);
  for(int i = 0; i < n; i++){
    cin >> v[i];
  }
  for(int i = n; i < x; i++){
    v[i] = 0;
  }
  arr.resize(2 * x);
  vec.resize(2 * x);
  build(0);
  build_interval(0);
  while(m--){
    int d;
    cin >> d;
    if(d == 1){
      int a1,a2;
      cin >> a1 >> a2;
      update(a1,a2);
    }else{
      int a1,a2;
      cin >> a1 >> a2;
      pair<int,int> p = find_interval(0,a1, a2 - 1);
      cout << p.first << " " << p.second << endl;
    }
  }
}
