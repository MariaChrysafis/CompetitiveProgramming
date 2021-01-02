/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <iostream>
#include <map>
using namespace std;
class ENecklaceAssembly {
public:
    int GCD(int a, int b){
      if(a > b){
        swap(a,b);
      }
      if(a == 0){
        return b;
      }
      return GCD(b % a, a);
    }
    int LCM(int a, int b){
      return a * b/GCD(a,b);
    }
    void f(std::istream& in, std::ostream& out) {
      int n, k;
      in >> n >> k;
      string s;
      in >> s;
      map<char,int> oc;
      for(char c: s){
        oc[c]++;
      }
      for(int i = n; i >= 1; i--){
        //every GCD(i,k) it must repeat
        int x = GCD(i, k);
        //k/x of them must be the same
        int sum = 0;
        for(char c = 'a'; c <= 'z'; c++){
          sum += oc[c]/(i/x);
        }
        if(sum >= x){
          out << i << endl;
          return;
        }
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
	ENecklaceAssembly solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
