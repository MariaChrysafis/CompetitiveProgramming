#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct interval{
  int l,r;
};
struct myStruct{
  long long pref;
  long long suf;
  long long sum;
  long long mx;
};
vector<int> v;
vector<interval> intervals;
vector<myStruct> arr;
int power(int x){
  int pwr = 1;
  while(pwr < x){
    pwr *= 2;
  }
  return pwr;
}
interval combine(interval a, interval b){
  return {a.l,b.r};
}
interval build(int i){
  if(i >= v.size() - 1){
    int x = v.size();
    intervals[i] = {i - x + 1, i - x + 1};
    return intervals[i];
  }
  intervals[i] = combine(build(2 * i + 1),build(2 * i + 2));
  return intervals[i];
}
myStruct merge(myStruct t1, myStruct t2){
  long long suffix = max(t2.suf,t2.sum + t1.suf);
  long long prefix = max(t1.pref,t1.sum + t2.pref);
  long long sm = t1.sum + t2.sum;
  long long myMax = max(max(t1.mx, t2.mx),t1.suf + t2.pref);
  return {prefix,suffix,sm,myMax};
}
myStruct fill(int i){
  if(i >= v.size() - 1){
    int sz = v.size();
    int x = i - (sz - 1);
    arr[i] = {max(0,v[x]),max(0,v[x]),v[x],max(0,v[x])};
    return arr[i];
  }
  myStruct t1 = fill(2 * i + 1);
  myStruct t2 = fill(2 * i + 2);
  arr[i] = merge(t1,t2);
  return arr[i];
}
long long search(int i, int L, int R){
  if(intervals[i].l >= L && intervals[i].r <= R){
    return arr[i].mx;
  }
  if(intervals[i].l > R || intervals[i].r < L){
    return 0;
  }
  long long x1 = search(2 * i + 1,L,R);
  long long x2 = search(2 * i + 2,L,R);
  return max(x1,x2);
}
void update(int i, int j){
  int ind = i + (v.size() - 1);
  arr[ind] = {max(0,j),max(0,j),j,max(0,j)};
  while(ind != 0){
    ind = (ind - 1)/2;
    arr[ind] = merge(arr[2 * ind + 1],arr[2 * ind + 2]);
  }
}
int main(){
  int n,q;
  cin >> n >> q;
  int x = power(n);
  v.resize(x);
  for(int i = 0; i < n; i++){
    cin >> v[i];
  }
  for(int i = n; i < x; i++){
    v[i] = 0;
  }
  arr.resize(2 * x);
  intervals.resize(2 * x);
  build(0);
  fill(0);
  long long ans = search(0,0,x - 1);
  cout << ans << endl;
  while(q--){
    int a,b;
    cin >> a >> b;
    update(a,b);
    ans = search(0,0,x - 1);
    cout << ans << endl;
  }
}
