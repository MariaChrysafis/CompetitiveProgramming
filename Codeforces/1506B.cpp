#include <iostream>
#include <fstream>
 
#include <iostream>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class BPartialReplacement {
  public:
    string s;
    int n, k;
    void f(std::istream& in, std::ostream& out) {
      in >> n >> k;
      in >> s;
      int l = -1;
      for(int i = 0; i < s.length(); i++){
        if(s[i] == '*'){
          s[i] = 'x';
          l = i;
          break;
        }
      }
      int r = -1;
      for(int i = s.length() - 1; i >= 0; i--){
        if(s[i] == '*'){
          s[i] = 'x';
          r = i;
          break;
        }
      }
      if(l == -1){
        out << 0 << endl;
        return;
      }
      if(r == -1){
        out << 1 << endl;
        return;
      }
      s[l] = s[r] = 'x';
      int lastStar = l;
      int lastX = l;
      for(int i = l + 1; i < r; i++){
        //out << lastX << " " << lastStar << endl;
        if(s[i] == '*' && abs(i - lastX) == k){
          lastX = i;
          s[i] = 'x';
          continue;
        }
        if(abs(i - lastX) >= k){
          //out << "YES" << endl;
          s[lastStar] = 'x';
          lastX = lastStar;
          continue;
        }
        if(s[i] == '*'){
          if(abs(i - lastX) > k){
            s[lastStar] = 'x';
            lastX = lastStar;
            continue;
          }else{
            lastStar = i;
          }
        }
      }
      int cntr = 0;
      for(char c: s){
        if(c == 'x'){
          cntr++;
        }
      }
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
	BPartialReplacement solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
