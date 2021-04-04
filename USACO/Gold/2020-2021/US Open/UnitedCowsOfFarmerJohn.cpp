#include <iostream>
#include <algorithm>
#include <fstream>
#define endl '\n'
#include <iostream>
#include <algorithm>
#include <fstream>

#include <vector>
#include <map>
#define ll long long
using namespace std;
int n;
bool cstm(pair<int,int> p1, pair<int,int> p2){
  return p1.second < p2.second;
}
struct segTree{
  vector<int> v;
  vector<long long> arr;
  vector<pair<int,int>> vec;
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
  long long build(int ind){
    if(ind >= v.size() - 1){
      arr[ind] = v[ind - (v.size() - 1)];
      return arr[ind];
    }
    arr[ind] = build(2 * ind + 1) + build(2 * ind + 2);
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
  long long interval(int i, int L, int R){
    if(vec[i].first > R || vec[i].second < L){
      return 0;
    }
    if(vec[i].first >= L && vec[i].second <= R){
      return arr[i];
    }
    long long a = interval(2 * i + 1,L,R);
    long long b = interval(2 * i + 2,L,R);
    return a + b;
  }
  void update(int k, int u){
    int ind = (v.size() - 1) + k;
    arr[ind] = u;
    while(ind != 0){
      int parent = (ind - 1)/2;
      arr[parent] = (arr[2 * parent + 1] + arr[2 * parent + 2]);
      ind = parent;
    }
  }
};
class Problem1UnitedCowsOfFarmerJohn {
public:
  vector<ll> arr;
  vector<vector<ll>> myMap;
  vector<ll> nxt;
  vector<ll> prev;
  vector<int> end;
  vector<int> start;
  ll comp(int x){
    if(prev[x] == -1){
      return x;
    }
    return x - prev[x] - 1;
  }
  void fill(){
    end.resize(n), start.resize(n);
    for(int i = 0; i < n; i++) {
      if (nxt[i] == -1) {
        if (i != 0)
          start[i] = start[i - 1];
        else
          start[i] = 0;
      } else {
        start[i] = start[i - 1] + 1;
      }
      if (prev[i] == -1) {
        if(i != 0) end[i] = end[i - 1];
        else end[i] = 0;
      } else {
        end[i] = end[i - 1] + 1;
      }
    }
  }
  vector<pair<int,int>> transform(){
    vector<pair<int,int>> v;
    for(int i = 0; i < n; i++){
      if(nxt[i] == -1) continue;
      v.push_back({i, nxt[i]});
    }
    return v;
  }
  ll interval(int n){
    vector<pair<int,int>> vec = transform();
    segTree st;
    int x = st.cl(n);
    st.v.resize(x);
    st.arr.resize(2 * x);
    for(int i = 0; i < st.v.size(); i++) st.v[i] = 0;
    st.vec.resize(2 * x);
    st.build(0);
    st.build2(0);
    sort(vec.begin(), vec.end(),cstm);
    ll ans = 0;
    for(int i = 0; i < vec.size(); i++){
      vec[i] = {vec[i].first + 1, vec[i].second};
      ans += st.interval(0, vec[i].first, vec[i].second);
      st.update(vec[i].first, 1);
    }
    for(int i = 0; i < n; i++){
      if(prev[i] == -1){
        ans += end[i];
      }
    }
    return ans;
  }
  void solve(std::istream& in, std::ostream& out) {
    in >> n;
    arr.resize(n);
    myMap.resize(n);
    nxt.resize(n);
    prev.resize(n);
    for(int i = 0; i < n; i++){
      in >> arr[i];
      arr[i]--;
      myMap[arr[i]].push_back(i);
    }
    //return;
    for(int i = 0; i < n; i++){
      if(myMap[i].size() == 0) continue;
      for(int j = 0; j < myMap[i].size() - 1; j++){
        nxt[myMap[i][j]] = myMap[i][j + 1];
      }
      for(int j = 1; j < myMap[i].size(); j++){
        prev[myMap[i][j]] = myMap[i][j - 1];
      }
      nxt[myMap[i][myMap[i].size() - 1]] = -1;
      prev[myMap[i][0]] = -1;
    }
    ll sm = 0;
    for(int i = 0; i < n; i++){
      sm += comp(i);
      //out << comp(i) << ' ';
    }
    fill();
    out << sm - interval(n) << endl;
  }
};


int main() {
	Problem1UnitedCowsOfFarmerJohn solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
