#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class DRatingCompression {
public:
    bool isPermutation(vector<int> v){
      sort(v.begin(),v.end());
      for(int i = 0; i < v.size(); i++){
        if(v[i] != i + 1){
          return false;
        }
      }
      return true;
    }
    void f(std::istream& in, std::ostream& out){
      int n;
      in >> n;
      vector<int> arr(n);
      int cnt[n];
      int ans[n];
      for(int i = 0; i < n; i++){
        cnt[i] = 0;
      }
      for(int i = 0; i < n; i++){
        in >> arr[i];
        ans[i] = 0;
        cnt[arr[i]]++;
      }
      int l = 0;
      int r = n - 1;
      int i;
      for(i = 1; i <= n; i++) {
        if (cnt[i] == 0) {
          break;
        }
        ans[n - i] = 1;
        if (cnt[i] != 1) {
          break;
        }
        if (arr[l] == i) {
          l++;
        }else if (arr[r] == i) {
          r--;
        }else {
          break;
        }
      }
      out << isPermutation(arr);
      for(int j = 1; j < n; j++){
        out << ans[j];
      }
      out << endl;
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
	DRatingCompression solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
