#include <iostream>
#include <algorithm>
#include <fstream>
#define endl '\n'
#include <iostream>
#include <set>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
void print(std::istream& in, std::ostream& out, pair<int,int> p){
  out << p.first + 1<< " " << p.second + 1;
}
class D3Coloring {
  public:
    void solve(std::istream& in, std::ostream& out) {
      vector<pair<int,int>> s1;
      vector<pair<int,int>> s2;
      int n;
      in >> n;
      for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
          if((i + j) % 2){
            s1.push_back({i,j});
          }else{
            s2.push_back({i, j});
          }
        }
      }
      int x;
      int x1 = 0; int x2 = 0;
      n *= n;
      while(n--){
        cin >> x;
        if(x == 1){
          if(x1 != s1.size()){
            //place on a black sqare
            cout << 2 << " ";
            print(in, out, s1[x1]), x1++;
            cout << endl;
            cout.flush();
          }else{
            cout << 3 << " ";
            print(in, out, s2[x2]), x2++;
            cout << endl;
            cout.flush();
          }
        }else if(x == 2){
          if(s2.size() != x2){
            //place on a white sqare
            cout << 1 << " ";
            print(in, out, s2[x2]), x2++;
            cout << endl;
            cout.flush();
          }else{
            cout << 3 << " ";
            print(in, out, s1[x1]), x1++;
            cout << endl;
            cout.flush();
          }
        }else{
          if(s2.size() != x2){
            //place on a white sqare
            cout << 1 << " ";
            print(in, out, s2[x2]), x2++;
            cout << endl;
            cout.flush();
          }else{
            cout << 2 << " ";
            print(in, out, s1[x1]), x1++;
            cout << endl;
            cout.flush();
          }
        }
      }
    }
};
 
 
int main() {
	D3Coloring solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
