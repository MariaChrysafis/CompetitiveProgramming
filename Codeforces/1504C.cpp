#include <iostream>
#include <algorithm>
#include <fstream>
#define endl '\n'
#include <iostream>
#include <algorithm>
#include <fstream>
 
#pragma GCC target("avx2")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class CBalanceTheBits {
public:
  string replaceAll( string s, const string search, const string replace ) {
    for( size_t pos = 0; ; pos += replace.length() ) {
      // Locate the substring to replace
      pos = s.find( search, pos );
      if( pos == string::npos ) break;
      // Replace by erasing and inserting
      s.erase( pos, search.length() );
      s.insert( pos, replace );
    }
    return s;
  }
  string rec(string s){
    for(int i = 0; i < s.length(); i++){
      if(s[i] == s[s.length() - 1 - i] && s[i] == '1'){
        s[i] = '(';
        s[s.length() - i - 1] = ')';
      }else{
        break;
      }
    }
    return s;
  }
  bool valid(string s){
    int cntr = 0;
    for(char c: s){
      if(c == '('){
        cntr++;
      }else{
        cntr--;
      }
      if(cntr < 0) return false;
    }
    if(cntr != 0) return false;
    return true;
  }
  string transform(string res, string s){
    string res1;
    for(int i = 0; i < res.size(); i++){
      if(s[i] == '1'){
        res1 += res[i];
      }else{
        if(res[i] == ')') res1 += '(';
        else res1 += ')';
      }
    }
    return res1;
  }
  void f(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    string orig;
    string s;
    in >> s;
    orig = s;
    s = rec(s);
    s = replaceAll(s,"11","()");
    int cntr = 0;
    for(int i = 0; i < s.length(); i++){
      if(s[i] == '1'){
        if(cntr % 2 == 0) s[i] = '(';
        else s[i] = ')';
        cntr++;
      }
    }
    cntr = 0;
    for(int i = 0; i < s.length(); i++) {
      if (s[i] == '0') {
        if (cntr % 2 == 0)
          s[i] = '(';
        else
          s[i] = ')';
        cntr++;
      }
    }
    if(valid(s) && valid(transform(s,orig))){
      out << "YES" << endl;
      out << s << endl;
      out << transform(s,orig) << endl;
      return;
    }
    out << "NO" << endl;
  }
  void solve(std::istream &in, std::ostream &out) {
    int t;
    in >> t;
    while (t--) {
      f(in, out);
    }
  }
};
 
int main() {
	CBalanceTheBits solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
