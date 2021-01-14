#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;
long long max(long long a, long long b){
  if(a > b) return a;
  return b;
}
class DBoboniuChatsWithDu {
public:
  void solve(std::istream& in, std::ostream& out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, d, m;
    in >> n >> d >> m;
    int arr[n];
    long long SUM = 0;
    for(int i = 0; i < n; i++){
      in >> arr[i];
      SUM += arr[i];
    }
    int cntr = 0;
    vector<int> bad;
    vector<int> good;
    for(int i: arr){
      if(i > m){
        cntr++;
        bad.push_back(i);
      }else{
        good.push_back(i);
      }
    }
    sort(good.begin(),good.end());
    sort(bad.begin(),bad.end());
    reverse(good.begin(),good.end());
    reverse(bad.begin(),bad.end());
    long long goodPref[good.size() + 1];
    goodPref[0] = 0;
    for(int j = 0; j < good.size(); j++){
      goodPref[j + 1] = goodPref[j] + good[j];
    }
    long long badPref[bad.size() + 1];
    badPref[0] = 0;
    for(int j = 0; j < bad.size(); j++){
      badPref[j + 1] = badPref[j] + bad[j];
    }
    long long sum;
    long long myMax = 0;
    for(int j = 1; j <= cntr; j++){
      long long mid = (cntr - j);
      long long gap = d * j - d;
      if(good.size() - max(gap - mid,0) < 0 || good.size() - max(gap - mid,0) > good.size()){
        continue;
      }
      sum = badPref[j] + goodPref[good.size() - max(gap - mid,0)];
      myMax = max(myMax,sum);
    }
    if(cntr == 0){
      out << SUM << endl;
      return;
    }
    //myMax = max(myMax,SUM - badPref[bad.size()] + bad[bad.size() - 1]);
    out << myMax;
  }
};
 
int main() {
	DBoboniuChatsWithDu solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
