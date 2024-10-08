/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */
 
#include <iostream>
#include <fstream>
 
#include <iostream>
#include <fstream>
 
 
 
 
 
 
 
 
 
#include <set>
using namespace std;
class ERestoringThePermutation {
public:
  int ot = 0;
  void f(std::istream& in, std::ostream& out){
    int n;
    in >> n;
    int arr[n];
    bool val[n + 1];
    for(int i = 0; i < n; i++){
      in >> arr[i];
      val[i] = false;
    }
    val[n] = false;
    int ans[n];
    for(int i = 0; i < n; i++){
      ans[i] = -1;
    }
    for(int i = 0; i < n; i++){
      if(i == 0 || arr[i] != arr[i - 1]){
        ans[i] = arr[i];
        val[arr[i]] = true;
        continue;
      }
    }
    int x = 1;
    for(int i = 0; i < n; i++){
      if(ans[i] == -1){
        while(val[x]){
          x++;
        }
        ans[i] = x;
        x++;
      }
    }
    for(int i: ans){
      if(i == -1) continue;
      out << i << " ";
    }
    out << endl;
    set<int> s;
    for(int i = 1; i <= n; i++){
      if(!val[i]){
        s.insert(-i);
      }
    }
    for(int i = 0; i < n; i++){
      if(i == 0 || arr[i] != arr[i - 1]){
        out << arr[i] << " ";
        continue;
      }
      auto it = s.upper_bound(-arr[i]);
      out << -*it << " ";
      s.erase(s.find(*it));
    }
    out << endl;
  }
  void solve(std::istream& in, std::ostream& out) {
    int t;
    in >> t;
    ot = t;
    while(t--){
      f(in, out);
    }
  }
};
 
int main() {
	ERestoringThePermutation solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
