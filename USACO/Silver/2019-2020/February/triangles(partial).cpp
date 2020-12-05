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
struct coord{
  int x,y;
};
int max3(int a, int b, int c){
  return max(max(a,b),c);
}
long long area(int x1, int y1, int x2, int y2, int x3, int y3){
  int x = max3(abs(x1 - x2), abs(x2 - x3), abs(x1 - x3));
  int y = max3(abs(y1 - y2), abs(y2 - y3), abs(y1 - y3));
  return x * y;
}
bool formstriangle(int x1, int y1, int x2, int y2, int x3, int y3){
  if(x1 == x2 && y1 == y2) return false;
  if(x2 == x3 && y2 == y3) return false;
  if(x3 == x1 && y1 == y3) return false;
  int hasX = (x1 == x2) + (x2 == x3) + (x3 == x1);
  int hasY = (y1 == y2) + (y2 == y3) + (y3 == y1);
  if(hasY == 1 && hasX == 1){
    return true;
  }
  return false;
}
bool operator == (coord a, coord b){
  return ((a.x == b.x) && (a.y == b.y));
}
map<int,vector<coord> > vertical;
map<int,vector<coord> > horizontal;
int main(){
  //input
  IO
  vector<coord>v;
  int N;
  cin >> N;
  REP(i,N){
    int a,b;
    cin >> a >> b;
    a += pow(10,4);
    b += pow(10,4);
    coord c;
    c.x = a;
    c.y = b;
    v.pb(c);
    vertical[b].pb(c);
    horizontal[a].pb(c);
  }
  long long ans = 0;
  trav(p,vertical){
    trav(q,p.second){
      //cout << q.x << " " << q.y << endl;
      //now we've found a vertical point of interest
      long long countery = 0;
      trav(r,vertical[q.y]){
        countery += abs(r.x - q.x);
        countery %= MOD;
      }
      long long counterx = 0;
      trav(r,horizontal[q.x]){
        counterx += abs(r.y - q.y);
        counterx %= MOD;
      }
      ans += counterx * countery;
      ans = ans % MOD;
    }
  }
  cout << ans << endl;
}
