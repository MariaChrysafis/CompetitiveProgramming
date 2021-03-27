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
class C1KLCMEasyVersion {
  public:
    void f(std::istream& in, std::ostream& out) {
      int n, k;
      in >> n >> k;
      if(n == 5){
        out << 1 << " " << 2 << " " << 2 << endl;
        return;
      }
      if(n % 3 == 0){
        out << n/3 << " " << n/3 << " " << n/3 << endl;
        return;
      }
      if(n % 4 == 0){
        out << n/4 << " " << n/4 << " " << n/2 << endl;
        return;
      }
      if(n % 2 == 1){
        out << 1 << " " << n/2 << " " << n/2 << endl;
        return;
      }
      if((n / 2 - 2) % 4 == 0){
        out << 4 << " " << n/2 - 2 << " " << n/2 - 2 << endl;
        return;
      }
      out << n/2 - 1 << " " << n/2 - 1 << " " << 2 << endl;
      return;
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
	C1KLCMEasyVersion solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
