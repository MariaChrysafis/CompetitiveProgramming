#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class ProblemAFlatterLand {
public:
  void solve(std::istream& in, std::ostream& out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,x;
    in >> n >> x;
    out << (n - 1) * x << endl;
  }
};
