#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <map>
#include <cmath>
#include <set>
#include <vector>
#pragma GCC target("avx2")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class AGoingHome {
public:
  void solve(std::istream &in, std::ostream &out) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    in >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      in >> v[i];
    }
    vector<vector<pair<int, int>>> oc(5 * pow(10,6) + 1);
    for (int i = 0; i < v.size(); i++) {
      for (int j = i + 1; j < v.size(); j++) {
        if(oc[v[i] + v[j]].size() <= 4) oc[v[i] + v[j]].push_back({i, j});
        pair<int, int> p = oc[v[i] + v[j]][0];
        if (p.first != j && p.second != i && p.first != i && p.second != j) {
          out << "YES" << endl;
          out << i + 1 << " " << j + 1 << " " << p.first + 1 << " "
              << p.second + 1 << endl;
          return;
        }
      }
    }
    out << "NO" << endl;
  }
};
 
 
int main() {
	AGoingHome solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
