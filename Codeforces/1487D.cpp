/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */
 
#include <iostream>
#include <fstream>
 
/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */
 
#include <iostream>
#include <fstream>
 
 
#include <cmath>
#include <vector>
using namespace std;
class DPythagoreanTriples {
public:
  vector<pair<int,int>> v;
  void f(std::istream &in, std::ostream &out){
    long long limit = pow(10,9);
    long long cntr = 0;
    for(long long n = 1; n <= limit; n++){
      for(long long m = n + 1; n * n + m * m <= limit; m++){
        if(n * (n + 1) == m * (m - 1)){
          v.push_back({n,m});
          cntr++;
        }
      }
    }
    //out << cntr << endl;
  }
  void q(std::istream &in, std::ostream &out){
    int n;
    in >> n;
    int cntr = 0;
    for(pair<int,int> p: v){
      long long x = (p.first * p.first + p.second * p.second);
      if(x <= n){
        cntr++;
      }
    }
    out << cntr << '\n';
  }
  void solve(std::istream &in, std::ostream &out) {
    int t;
    in >> t;
    f(in,out);
    while(t--){
      q(in, out);
    }
  }
};
 
int main() {
	DPythagoreanTriples solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
