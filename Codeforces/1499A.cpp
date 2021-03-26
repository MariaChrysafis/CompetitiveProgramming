#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class ADominoOnWindowsill {
  public:
    void f(std::istream& in, std::ostream& out) {
      int n, k1, k2;
      in >> n >> k1 >> k2;
      int w, b;
      in >> w >> b;
      if((k1 + k2) < 2 * w){
        out << "NO" << endl;
        return;
      }
      if((2 * n - k1 - k2) < 2 * b){
        out << "NO" << endl;
        return;
      }
      out << "YES" << endl;
    }
    void solve(std::istream& in, std::ostream& out) {
      int t;
      in >> t;
      while(t--){
        f(in, out);
      }
    }
};
 
 
int main() {
	ADominoOnWindowsill solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
