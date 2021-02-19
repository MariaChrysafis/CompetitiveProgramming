/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;
vector<int> vertical, horizontal;
int n, m;
class Problem3FencedIn {
public:
  void solve(std::istream &in, std::ostream &out) {
    int A,B;
    in >> A >> B >> n >> m;
    for(int i = 0; i < n; i++){
      int a;
      in >> a;
      vertical.push_back(a);
    }
    vertical.push_back(A);
    vertical.push_back(0);
    sort(vertical.begin(),vertical.end());
    for(int i = 0; i < m; i++){
      int a;
      in >> a;
      horizontal.push_back(a);
    }
    horizontal.push_back(0);
    horizontal.push_back(B);
    sort(horizontal.begin(),horizontal.end());
    vector<int> h(horizontal.size() - 1);
    vector<int> v(vertical.size() - 1);
    for(int i = 0; i < vertical.size() - 1; i++){
      v[i] = vertical[i + 1] - vertical[i];
    }
    for(int i = 0; i < horizontal.size() - 1; i++){
      h[i] = horizontal[i + 1] - horizontal[i];
    }
    sort(v.begin(),v.end());
    sort(h.begin(),h.end());
    int vv = 1, hh = 1;
    n++;
    m++;
    long long ans = v[0] * (m - 1) + h[0] * (n - 1);
    while(hh < h.size() && vv < v.size()){
      if(h[hh] > v[vv]){
        ans += v[vv] * (m - hh);
        vv++;
      }else{
        ans += h[hh] * (n - vv);
        hh++;
      }
    }
    out << ans << endl;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
	Problem3FencedIn solver;
	std::ifstream in("fencedin.in");
	std::ofstream out("fencedin.out");
	solver.solve(in, out);
	return 0;
}
