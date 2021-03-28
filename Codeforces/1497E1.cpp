#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <map>
#include <set>
#include <cmath>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class E1SquareFreeDivisionEasyVersion {
  public:
  int nxt(int x){
    if(floor(sqrt(x)) * floor(sqrt(x)) == x){
      return 1;
    }
    int m = sqrt(x/11);
    int s2 = floor(sqrt(x/2) )* floor(sqrt(x/2));
    if(s2 != 0 && x % s2 == 0){
      x /= s2;
    }
    int s3 = floor(sqrt(x/3)) * floor(sqrt(x/3));
    if(s3 != 0 && x % s3 == 0){
      x /= s3;
    }
    int s5 = floor(sqrt(x/5)) * floor(sqrt(x/5));
    if(s5 != 0 && x % s5 == 0){
      x /= s5;
    }
    int s7 = floor(sqrt(x/7)) * floor(sqrt(x/7));
    if(s7 != 0 && x % s7 == 0){
      x /= s7;
    }
    for(int i = m; i >= 1; i--){
      if(x % (i * i) == 0){
        x /= (i * i);
      }
    }
    return x;
  }
    void f(std::istream& in, std::ostream& out) {
      int n, k;
      in >> n >> k;
      int arr[n];
      map<int,int> oc;
      for(int i = 0; i < n; i++){
        in >> arr[i];
        arr[i] = nxt(arr[i]);
        //out << arr[i] << ' ';
      }
      //out << endl;
      set<int> s;
      int cntr = 1;
      for(int i = 0; i < n; i++){
        if(s.count(arr[i])){
          cntr++;
          s.clear();
          s.insert(arr[i]);
        }else{
          s.insert(arr[i]);
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
	E1SquareFreeDivisionEasyVersion solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
