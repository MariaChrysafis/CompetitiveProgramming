/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */
 
#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <vector>
#include <cmath>
#define ll int
using namespace std;
class BMArrays {
  public:
    void f(std::istream& in, std::ostream& out) {
      ll n;
      in >> n;
      ll MOD;
      in >> MOD;
      ll oc[MOD];
      for(int i = 0; i < MOD; i++){
        oc[i] = 0;
      }
      for(int i = 0; i < n; i++){
        ll a;
        in >> a;
        oc[a % MOD]++;
      }
      ll cntr = (oc[0] > 0);
      for(int i = 1; i <= floor(MOD/2); i++){
        if(MOD % 2 == 0 && i == floor(MOD/2)){
          cntr += (oc[MOD/2] > 0);
          break;
        }
        ll x = abs(oc[i] - oc[MOD - i]);
        if(oc[i] == 0 && oc[MOD - i] == 0) continue;
        if(x <= 1){
          cntr++;
        }else{
          cntr += x;
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
	BMArrays solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
