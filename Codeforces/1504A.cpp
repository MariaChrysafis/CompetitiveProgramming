#include <iostream>
#include <algorithm>
#include <fstream>
#define endl '\n'
#include <iostream>
#include <string>
#include <algorithm>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class ADjVu {
  public:
    void f(std::istream& in, std::ostream& out) {
      string s;
      in >> s;
      int n = s.length();
      bool fine = false;
      string ans;
      int x;
      for(int i = 0; i < s.length(); i++){
        if(s[i] != 'a'){
          fine = true;
          x = s.length() - 1 - i;
          break;
        }
      }
      if(fine){
        out << "YES" << endl;
        //out << x << endl;
        for(int i = 0; i < s.length(); i++){
          out << s[i];
          if(i == x){
            out << 'a';
          }
        }
        out << endl;
      }else{
        out << "NO" << endl;
        return;
      }
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
	ADjVu solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
