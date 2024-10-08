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
using namespace std;
class BInflation {
public:
  long long f(std::istream& in, std::ostream& out){
    int n, k;
    in >> n >> k;
    long long arr[n];
    for (int i = 0; i < n; i++) {
      in >> arr[i];
    }
    long long pref[n];
    pref[0] = arr[0];
    for(int i = 1; i < n; i++){
      pref[i] = pref[i - 1] + arr[i];
    }
    long long cur = 0;
    for (int i = 1; i < n; i++) {
      cur = max(arr[i] * 100 - k * (pref[i - 1] - 1) - 1, cur);
    }
    return cur / k;
  }
  void solve(std::istream& in, std::ostream& out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    in >> t;
    while(t--) {
      long long a = f(in, out);
      out << a << endl;
    }
  }
};


int main() {
	BInflation solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
