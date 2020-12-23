 
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
  arr[ind] = max(build(2 * ind + 1),build(2 * ind + 2));
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
int interval(int i, int desMax){
  if(i >= v.size() - 1){
    return i;
  }
  int l = arr[2 * i + 1];
  int r = arr[2 * i + 2];
  if(l >= desMax){
    return interval(2 * i + 1, desMax);
  }
  if(r >= desMax){
    return interval(2 * i + 2, desMax);
  }
}
void update(int k, int u){
  //parent (ind - 1)/2
  int ind = (v.size() - 1) + k;
  arr[ind] = u;
  while(ind != 0){
    int parent = (ind - 1)/2;
    arr[parent] = max(arr[parent * 2 + 1],arr[parent * 2 + 2]);
    ind = parent;
  }
}
int main(){
  int n, q;
  cin >> n >> q;
  int x = cl(n);
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
  build2(0);
  while(q--){
    int b;
    cin >> b;
    if(b == 1){
      int k,u;
      cin >> k >> u;
      update(k,u);
    }else{
      int inp;
      cin >> inp;
      if(arr[0] < inp){
        cout << -1 << endl;
        continue;
      }
      int ans = interval(0,inp);
      int sz = v.size();
      cout << ans - sz + 1 << endl;
    }
  }
  return 0;
}
