#include <iostream>
#include <algorithm>
#include <fstream>
#define endl '\n'
#include <iostream>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class BFlipTheBits {
  public:
    void f(std::istream& in, std::ostream& out) {
      int n;
      in >> n;
      string s1, s2;
      in >> s1 >> s2;
      int pref[2][n];
      pref[0][0] = (s1[0] == '0');
      pref[1][0] = (s1[0] == '1');
      for(int i = 1; i < n; i++){
        pref[0][i] = pref[0][i - 1] + (s1[i] == '0');
        pref[1][i] = pref[1][i - 1] + (s1[i] == '1');
      }
      bool flip = false;
      for(int i = s1.length() - 1; i >= 0; i--){
        if(s1[i] != s2[i] && !flip){
          if(pref[0][i] != pref[1][i]){
            out << "NO" << endl;
            //out << i << endl;
            return;
          }
          flip = true;
        }else if(s1[i] == s2[i] && flip){
          if(pref[0][i] != pref[1][i]){
            out << "NO" << endl;
            //ut << i << endl;
            return;
          }
          flip = false;
        }
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
	BFlipTheBits solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
