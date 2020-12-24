#include <iostream>
#include <vector>
#include <map>
using namespace std;
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
struct segmentTree{
  vector<pair<int,int>> vec;
  vector<int> v;
  vector<int> arr;
  int INF = 1000000000;
  int build(int ind){
    if(ind >= v.size() - 1){
      arr[ind] = v[ind - (v.size() - 1)];
      return arr[ind];
    }
    arr[ind] = min(build(2 * ind + 1),build(2 * ind + 2));
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
      return INF;
    }
    if(vec[i].first >= L && vec[i].second <= R){
      return arr[i];
    }
    int a = interval(2 * i + 1,L,R);
    int b = interval(2 * i + 2,L,R);
    return min(a,b);
  }
};
segmentTree segTree;
int binSearch(int l, int r, int key, int i){
  while(r >= l){
    int m = (r + l)/2;
    int val = segTree.interval(0, i, m);
    if(val == key){
      return m;
    }else if(val > key){
      l = m + 1;
    }else{
      r = m - 1;
    }
  }
  return -1;
}
void solve(){
  int n;
  cin >> n;
  int x = cl(n);
  vector<int> v1(x);
  for(int i = 0; i < n; i++){
    cin >> v1[i];
  }
  for(int i = n; i < x; i++){
    v1[i] = 0;
  }
  vector<int> arr1 (2 * x);
  vector<pair<int,int>> vec1(2 * x);
  segTree.v = v1;
  segTree.vec = vec1;
  segTree.arr = arr1;
  segTree.build(0);
  segTree.build2(0);
  int suf[n + 1];
  suf[n] = 0;
  map<int,pair<int,int>> myMap;
  for(int i = n - 1; i >= 0; i--){
    suf[i] = max(suf[i + 1],v1[i]);
    myMap[suf[i]] = {-1,-1};
  }
  for(int i = 0; i < n; i++){
    if(myMap[suf[i]].first == -1){
      myMap[suf[i]].first = i;
    }
    myMap[suf[i]].second = i;
  }
  int cumMax = 0;
  for(int i = 0; i < n; i++){
    cumMax = max(cumMax,v1[i]);
    int l = myMap[cumMax].first;
    int r = myMap[cumMax].second;
    l = max(l - 1, i + 1);
    r--;
    /*
    if(l == n) continue;
    for(int j = l; j <= r; j++){
      if(segTree.interval(0,i + 1,j) == cumMax){
        cout << "YES" << endl;
        cout << i + 1 << " " << j - i << " " << n - j - 1 << endl;
        return;
      }
    }
    */
    if(l >= n) continue;
    int j = binSearch(l, r, cumMax,i + 1);
    if(j != -1){
      cout << "YES" << endl;
      cout << i + 1 << " " << j - i << " " << n - j - 1 << endl;
      return;
    }

  }
  cout << "NO" << endl;
}
int main(){
  int t;
  cin >> t;
  while(t--){
    solve();
  }
}
