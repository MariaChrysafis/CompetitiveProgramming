#include <iostream>
#include <algorithm>
#include <fstream>
 
#include <iostream>
#include <cmath>
#include <set>
#include <vector>
#define ll long long
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
class CPekoraAndTrampoline {
  public:
    const int INF = pow(10, 9);
    void print(std::istream& in, std::ostream& out, vector<ll> arr){
      for(ll i: arr){
        out << i << " ";
      }
      //out << endl;
    }
    void print(std::istream& in, std::ostream& out, set<int> s, vector<ll>
        arr){
      for(auto i = s.begin(); i != s.end(); i++){
        out << arr[*i] << " ";
      }
      out << endl;
    }
    void f(std::istream& in, std::ostream& out) {
      int n;
      in >> n;
      vector<ll> arr(n);
      for(int i = 0; i < n; i++){
        in >> arr[i];
      }
      ll ans = 0;
      int pos = 0;
      int curPos = 0;
      set<int> s;
      for(int i = 0; i < arr.size(); i++){
        if(arr[i] != 1){
          s.insert(i);
        }
      }
      ll t = n * n;
      while(t--){
        //print(in, out, s, arr);
        bool found = false;
        for(int i = curPos; i < n; i++){
          if(arr[i] != 1){
            found = true;
            pos = i;
            curPos = i;
            break;
          }
        }
        if(!found){
          out << ans << endl;
          return;
        }
        if(arr[pos] + pos >= n){
          ll orig = arr[pos];
          arr[pos] = max(n - pos - 1, 1);
          if(arr[pos] == 1 && s.find(pos) != s.end()){
            s.erase(s.find(pos));
          }
          ans += orig - arr[pos];
          continue;
        }
 
        while(pos < n){
          ll prev = arr[pos];
          if(arr[pos] == 1){
            //pos++;
            //continue;
            if(s.lower_bound(pos) == s.end()) break;
            pos = *s.upper_bound(pos);
            continue;
          }
          arr[pos] = max(arr[pos] - 1, 1ll);
          if(arr[pos] == 1 && s.find(pos) != s.end()){
            s.erase(s.find(pos));
          }
          pos = pos + prev;
        }
        ans++;
        //print(in, out, arr);
        //out << endl;
      }
      out << ans << endl;
 
    }
    void solve(std::istream& in, std::ostream& out) {
      ios_base::sync_with_stdio(false);
      cin.tie(NULL);
      int t;
      in >> t;
      while(t--){
        f(in, out);
      }
    }
};
 
 
int main() {
	CPekoraAndTrampoline solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
