#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#define ll long long
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class CMinimumGridPath {
  public:
    ll min(ll a, ll b){
      if(a < b){
        return a;
      }
      return b;
    }
    ll INF = 100000000000000000;
    void f(std::istream& in, std::ostream& out) {
      int n;
      in >> n;
      ll arr[n];
      for(int i = 0; i < n; i++){
        in >> arr[i];
      }
      ll bestHorizontal = INF;
      ll bestVertical = INF;
      ll dp[n];
      dp[0] = INF, dp[1] = n * (arr[0] + arr[1]);
      bestHorizontal = arr[0], bestVertical = arr[1];
      for(int i = 2; i < n; i++){
        if(i % 2 == 0){
          //horizontal
          if(arr[i] >= bestHorizontal){
            dp[i] = dp[i - 1] + arr[i] - bestHorizontal;
          }else{
            int h = i/2;
            dp[i] = dp[i - 1] - bestHorizontal * (n - h) + arr[i] * (n - h);
            bestHorizontal = arr[i];
          }
        }else{
          if(arr[i] >= bestVertical){
            dp[i] = dp[i - 1] + arr[i] - bestVertical;
          }else{
            int h = i/2;
            dp[i] = dp[i - 1] - bestVertical * (n - h) + arr[i] * (n - h);
            bestVertical = arr[i];
          }
        }
      }
      ll myMin = INF;
      for(ll i: dp){
        myMin = min(i, myMin);
      }
      out << myMin << endl;
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
	CMinimumGridPath solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
