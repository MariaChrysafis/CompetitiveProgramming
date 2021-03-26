#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <algorithm>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class BBinaryRemovals {
public:
  void f(std::istream& in, std::ostream& out) {
    string s;
    in >> s;
    int frst = -1;
    for(int i = 0; i < s.length() - 1; i++){
      if(s[i] == '1' && s[i + 1] == '1'){
        frst = i;
        break;
      }
    }
    if(frst == -1){
      out << "YES" << endl;
      return;
    }
    int scnd = -1;
    for(int i = 0; i < s.length() - 1; i++){
      if(s[i] == '0' && s[i + 1] == '0'){
        scnd = i;
      }
    }
    if(scnd == -1){
      out << "YES" << endl;
      return;
    }
    for(int i = frst; i < s.length() - 1; i++){
      if(s[i] == '0' && s[i + 1] == '0'){
        out << "NO" << endl;
        return;
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
	BBinaryRemovals solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
