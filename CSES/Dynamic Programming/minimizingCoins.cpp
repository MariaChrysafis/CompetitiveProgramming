/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */
 
//Created by Maria Chrysafis
#include <iostream>
#include <fstream>
 
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
using namespace std;
class MinimizingCoins {
public:
  void solve(std::istream& in, std::ostream& out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,x;
    in >> n >> x;
    int arr[n];
    for(int i = 0; i < n; i++){
      in >> arr[i];
    }
    int MAX = pow(10,7);
    int DP[x + 1];
    for(int i = 0; i <= x; i++){
      DP[i] = MAX;
    }
    DP[0] = 0;
    for(int i = 0; i <= x; i++){
      for(int j = 0; j < n; j++){
        if(i + arr[j] > x){
          continue;
        }
        DP[i + arr[j]] = min(DP[i + arr[j]],DP[i] + 1);
      }
    }
    if(DP[x] == MAX){
      out << -1 << endl;
      return;
    }
    out << DP[x] << endl;
  }
};
 
 
int main() {
	MinimizingCoins solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
