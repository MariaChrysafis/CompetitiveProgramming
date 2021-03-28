#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <algorithm>
#include <string>
#define ll long long
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class BYetAnotherMemeProblem {
  public:
    ll bruteForce(std::istream& in, std::ostream& out, ll A, ll B){
      ll l = to_string(B).length() - 1;
      return A * l;
    }
    void f(std::istream& in, std::ostream& out) {
      ll A, B;
      in >> A >> B;
      ll cntr = bruteForce(in, out, A, B + 1);
      out << cntr << endl;
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
	BYetAnotherMemeProblem solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
