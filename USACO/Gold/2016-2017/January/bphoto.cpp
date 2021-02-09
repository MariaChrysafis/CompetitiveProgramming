#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
class Problem1BalancedPhoto {
public:
  set<int> s;
  ordered_set s1;
  vector<int> f(std::istream &in, std::ostream &out,vector<int> arr){
    s.clear();
    s1.clear();
    vector<int> v;
    map<int,int> oc;
    for(int i = 0; i < arr.size(); i++){
      oc[arr[i]] = i;
    }
    for(int i = 0; i < arr.size(); i++){
      s.insert(arr[i]);
      s1.insert(arr[i]);
      auto it = s.upper_bound(arr[i]);
      int x = s1.order_of_key(*it);
      if(s.find(*it) == s.end()){
        v.push_back(0);
        continue;
      }
      v.push_back(i - x + 1);
    }
    return v;
  }
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
      in >> arr[i];
    }
    vector<int> v1 = f(in, out, arr);
    reverse(arr.begin(),arr.end());
    vector<int> v2 = f(in, out, arr);
    //return;
    reverse(v2.begin(),v2.end());
    int cntr = 0;
    for(int i = 0; i < arr.size(); i++){
      int myMin = min(v1[i],v2[i]);
      int myMax = max(v1[i],v2[i]);
      //out << v1[i] << " " << v2[i] << endl;
      //out << myMin << " " << myMax << endl;
      if(2 * myMin < myMax){
        //out << arr[arr.size() - 1 - i] << endl;
        cntr++;
      }
    }
    out << cntr << endl;
  }
};


int main() {
  ios_base::sync_with_stdio(false);
        cin.tie(NULL);
	Problem1BalancedPhoto solver;
        ifstream in("bphoto.in");
    ofstream out("bphoto.out");
	solver.solve(in, out);
	return 0;
}

