/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */
 
#include <iostream>
#include <fstream>
 
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
class BLastMinuteEnhancements {
public:
    void f(std::istream& in, std::ostream& out) {
      int n;
      in >> n;
      vector<int> arr(n);
      for(int i = 0; i < n; i++){
        in >> arr[i];
      }
      sort(arr.begin(),arr.end());
      reverse(arr.begin(),arr.end());
      arr[0]++;
      for(int i = 1; i < n; i++){
        if(arr[i] != arr[i - 1] && arr[i - 1] - arr[i] != 1){
          arr[i]++;
        }
      }
      set<int> s;
      for(int i = 0; i < n; i++){
        s.insert(arr[i]);
        //out << arr[i] << " ";
      }
      //out << endl;
      out << s.size() << endl;
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
	BLastMinuteEnhancements solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
