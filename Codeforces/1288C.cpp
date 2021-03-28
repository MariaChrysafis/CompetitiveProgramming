#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <cmath>
#define maxM 10
#define maxN 1000
#define ll long long
#pragma GCC target("avx2")
#pragma GCC optimization("O3")
#pragma GCC optimization("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class CTwoArrays {
public:
  ll dp[maxM][maxN];
  ll sm[maxM][maxN];
  const int MOD = pow(10, 9) + 7;
  void memoize(std::istream &in, std::ostream &out) {
    for(int i = 0; i < maxM; i++){
      for(int j = 0; j < maxN; j++){
        if(i == 0){
          dp[i][j] = 1;
          if(j != 0){
            sm[i][j] = sm[i][j - 1] + dp[i][j];
          }else{
            sm[i][j] = dp[i][j];
          }
          continue;
        }
        dp[i][j] = sm[i - 1][j];
        if(j != 0){
          sm[i][j] = sm[i][j - 1] + dp[i][j];
        }else{
          sm[i][j] = dp[i][j];
        }
        sm[i][j] %= MOD;
        dp[i][j] %= MOD;
      }
    }
  }
  int power(int x, int y){
    return dp[x][y];
  }
  void solve(std::istream &in, std::ostream &out) {
    int n, m;
    in >> n >> m;
    memoize(in, out);
    //out << power(1, 1) << endl;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ll pwr1 = power(m - 1, i);
      ll pwr2 = sm[m - 1][n - i - 1];
      if(n - i < 0){
        pwr2 = 1;
      }
      ans += pwr1 * pwr2;
      ans %= MOD;
    }
    out << ans << endl;
  }
};
 
 
int main() {
	CTwoArrays solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
