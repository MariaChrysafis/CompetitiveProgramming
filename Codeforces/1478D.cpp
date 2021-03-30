#include <iostream>
#include <algorithm>
#include <fstream>
#define endl '\n'
#include <iostream>
#include <cmath>
#define ll long long
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class DNezzarAndBoard {
  public:
    ll gcd(ll a, ll b){
      ll mx = max(a,b);
      ll mn = min(a,b);
      if(mn == 0) return mx;
      return gcd(mn, mx % mn);
    }
    void solve(std::istream& in, std::ostream& out) {
      int t;
      in >> t;
      //out << gcd(1000000000000000000,3) << endl;
      //return;
      //out << abs(-1000000000000000000) << endl;
      //return;
      while(t--){
        ll n;
        in >> n;
        ll k;
        in >> k;
        //k = abs(k);
        ll arr[n];
        for(int i = 0; i < n; i++){
          in >> arr[i];
        }
        sort(arr, arr + n);
        ll g = 0;
        for(int i = 1; i < n; i++){
          g = gcd(g,arr[i] - arr[0]);
        }
        if ((k-arr[0]) % g == 0){
          out << "YES" << endl;
        }else{
          out << "NO" << endl;
        }
      }
    }
};
 
 
int main() {
	DNezzarAndBoard solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
