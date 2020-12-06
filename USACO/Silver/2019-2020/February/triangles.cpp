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
#define pb push_back
#define pf push_front
#define ll long long
#define mp make_pair
#define REP(i,a) for(int i = 0; i < a; i++)
#define FOR(i,a,b) for(int i = a; i < b; i++)
#define trav(a,x) for(auto& a: x)
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define input freopen("triangles.in", "r", stdin); freopen("triangles.out", "w", stdout);
const ll  MOD = pow(10,9) + 7;
using namespace std;
struct thing{
  int lc,ls,rc,rs;
};
void pthing(thing a){
  cout << a.lc << ' ' << a.ls << ' ' << a.rc << ' ' << a.rs << endl;
}
long long SUM(thing t1){
  return t1.ls + t1.rs;
}
map<int,vector<pair<int,int>> > vertical;
map<int,vector<pair<int,int>> > horizontal;
map<pair<int,int>,thing> Vertical;
map<pair<int,int>,thing> Horizontal;
int main(){
  input
  IO
  vector<pair<int,int>>v;
  int N;
  cin >> N;
  REP(i,N){
    int a,b;
    cin >> a >> b;
    a += pow(10,4);
    b += pow(10,4);
    v.pb(mp(a,b));
    vertical[b].pb(mp(a,b));
    horizontal[a].pb(mp(a,b));
  }
  REP(i,20001){
    sort(vertical[i].begin(),vertical[i].end());
    sort(horizontal[i].begin(),horizontal[i].end());
  }
  REP(i,20001){
    if(vertical[i].size() <= 1) continue;
    int rightCount = 0;
    int rightSum = 0;
    REP(j,vertical[i].size()){
      rightSum += abs(vertical[i][j].first - vertical[i][0].first);
      rightCount++;
    }
    Vertical[vertical[i][0]] = {0,0,rightCount - 1,rightSum};
    for(int j = 1; j < vertical[i].size(); j++){
      thing thing1 = Vertical[vertical[i][j - 1]];
      int d = abs(vertical[i][j - 1].first - vertical[i][j].first);
      Vertical[vertical[i][j]] = {1,1,1,1};
      Vertical[vertical[i][j]] = {thing1.lc + 1 , thing1.lc * d + thing1.ls + d, thing1.rc - 1, thing1.rs - d * thing1.rc};
    }
  }
  REP(i,20001){
    if(horizontal[i].size() <= 1) continue;
    int upCount = 0;
    int upSum = 0;
    REP(j,horizontal[i].size()){
      upSum += abs(horizontal[i][j].second - horizontal[i][0].second);
      upCount++;
    }
    Horizontal[horizontal[i][0]] = {0,0,upCount - 1, upSum};
    for(int j = 1; j < horizontal[i].size(); j++){
      thing thing1 = Horizontal[horizontal[i][j - 1]];
      int d = abs(horizontal[i][j - 1].second - horizontal[i][j].second);
      Horizontal[horizontal[i][j]] = {thing1.lc + 1,thing1.lc * d + thing1.ls + d, thing1.rc - 1, thing1.rs - d * thing1.rc};
    }
  }
  long long ans = 0;
  trav(c,v){
    long long a = SUM(Horizontal[c]);
    long long b = SUM(Vertical[c]);
    a %= MOD;
    b %= MOD;
    long long prod = (a * b) % MOD;
    ans += prod;
    ans %= MOD;
  }
  cout << ans << endl;
  //cout << SUM(Horizontal[{10000,10000}]) << " " <<  SUM(Vertical[{10000,10000}]);
}
