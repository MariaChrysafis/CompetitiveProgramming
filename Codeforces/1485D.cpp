#include <iostream>
#include <fstream>
 
#include <iostream>
#include <cmath>
using namespace std;
int L = 720720;
class DMultiplesAndPowerDifferences {
public:
  void solve(std::istream &in, std::ostream &out) {
    int n, m;
    in >> n >> m;
    int a[n][m];
    for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        in >> a[i][j];
      }
    }
    for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        if((i + j) % 2 == 0){
          a[i][j] = L;
        }else{
          a[i][j] = L - pow(a[i][j],4);
        }
      }
    }
    for(int i = 0; i < n; i++){
      for(int j = 0; j < m; j++){
        out << a[i][j] << " ";
      }
      out << endl;
    }
  }
};
 
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
	DMultiplesAndPowerDifferences solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
