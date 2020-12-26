#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
class Problem1Cowntagion {
public:
    int n;
    map<int, vector<int>> adj;
    map<int, bool> hv;
    int power(int x) {
      int dum = 1;
      int counter = 0;
      while (dum < x) {
        dum *= 2;
        counter++;
      }
      return counter;
    }
    int dfs(int x) {
      hv[x] = true;
      if (adj[x].size() == 1 && hv[adj[x][0]]) {
        return 1;
      }
      int sum = 0;
      for (int i: adj[x]) {
        if (hv[i]) {
          continue;
        }
        sum += dfs(i);
      }
      return sum + 1;
    }
	void solve(std::istream& in, std::ostream& out) {
      in >> n;
      for (int i = 0; i < n - 1; i++) {
        int a, b;
        in >> a >> b;
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
      }
      int cnt = 0;
      for(int i = 0; i < n; i++){
        int x = adj[i].size();
        if(i != 0) x--;
        cnt += power(x + 1);
      }
      out << cnt + n - 1 << endl;
	}
};
