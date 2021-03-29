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
class AKThLargestValue {
  public:
    void solve(std::istream& in, std::ostream& out) {
      int n, q;
      in >> n >> q;
      int arr[n];
      int oc[2];
      oc[0] = oc[1] = 0;
      for(int i = 0; i < n; i++){
        in >> arr[i];
        oc[arr[i]]++;
      }
      while(q--){
        //out << oc[1] << endl;
        int t;
        in >> t;
        if(t == 1){
          int x; in >> x; x--;
          arr[x] = 1 - arr[x];
          oc[arr[x]]++;
          oc[1 - arr[x]]--;
          continue;
        }else{
          int k;
          in >> k;
          if(oc[1] >= k){
            out << 1 << endl;
          }else{
            out << 0 << endl;
          }
        }
      }
    }
};
 
 
int main() {
	AKThLargestValue solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
