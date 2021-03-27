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
class AAlexeyAndTrain {
  public:
  void f(std::istream& in, std::ostream& out) {
    int n;
    in >> n;
    int a[n];
    int b[n];
    for(int i = 0; i < n; i++){
      in >> a[i] >> b[i];
    }
    int c[n];
    for(int i = 0; i < n; i++){
      in >> c[i];
    }
    int cnt = 0;
    for(int i = 0; i < n; i++){
      if(i != 0) cnt += a[i] - b[i - 1] + c[i];
      else cnt += a[i] + c[i];
      if(i == n - 1) break;
      cnt = max(cnt + (b[i] - a[i] + 1)/2, b[i]);
    }
    out << cnt << endl;
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
	AAlexeyAndTrain solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
