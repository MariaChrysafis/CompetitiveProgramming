#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <set>
#include <cmath>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class BMinimalCost {
public:
  void solve(std::istream& in, std::ostream& out) {
    int t;
    in >> t;
    while(t--){
      int n, u, v;
      in >> n >> u >> v;
      vector<int> arr;
      for(int i = 0; i < n; i++){
        int a;
        in >> a;
        arr.push_back(a);
      }
      int ans = 3 * pow(10, 9);
      for(int i = 1; i < n; i++){
        int dif = abs(arr[i] - arr[i - 1]);
        if(dif >= 2){
          ans = 0;
          break;
        }
        ans = min(ans, min(u, v) + (dif == 0) * v);
      }
      out << ans << endl;
    }
  }
};
 
 
int main() {
	BMinimalCost solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
