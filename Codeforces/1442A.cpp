/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <iostream>
#include <vector>
using namespace std;
class AExtremeSubtraction {
public:
    bool f(std::istream& in, std::ostream& out) {
      int n;
      in >> n;
      vector<int> arr(n);
      for(int i = 0; i < n; i++){
        in >> arr[i];
      }
      for(int i = 1; i < n; i++){
        if(arr[i - 1] < arr[i]){
          int dif = arr[i] - arr[i - 1];
          //update everything to the right of i
          for(int j = n - 1; j >= i; j--){
            arr[j] -= dif;
          }
        }
        //out << endl;
      }
      for(int i: arr){
        if(i < 0){
          return false;
        }
      }
      return true;
    }
	void solve(std::istream& in, std::ostream& out) {
	  int t;
	  in >> t;
	  while(t--){
	    bool b = f(in, out);
	    if(b){
	      out << "YES" << endl;
	    }else{
	      out << "NO" << endl;
	    }
	  }
	}
};


int main() {
	AExtremeSubtraction solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
