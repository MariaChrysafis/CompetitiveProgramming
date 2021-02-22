/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
template <typename T> void pop_front(std::vector<T> &v) {
  if (v.size() > 0) {
    v.erase(v.begin());
  }
}
class Problem2Dishwashing {
public:
  vector<int> glob;
  vector<deque<int>> counter;
  vector<int> cur;
  vector<int> remap(vector<int> vec) {
    vector<pair<int, int>> ind;
    for (int i = 0; i < vec.size(); i++) {
      ind.push_back({vec[i], i});
    }
    sort(ind.begin(), ind.end());
    vector<int> ans(vec.size());
    for (int i = 0; i < ind.size(); i++) {
      ans[ind[i].second] = i;
    }
    return ans;
  }
  deque<int> create(int x) {
    deque<int> d;
    d.push_back(x);
    return d;
  }
  int best(int des) {
    for (int i = 0; i < counter.size(); i++) {
      if (!counter[i].empty()) {
        int x = counter[i].back();
        if (des < x) {
          return i;
        }
      }
    }
    return -1;
  }
  int bs(int l, int r, int des) {
    // find first element >= des
    while (l != r) {
      int mid = (l + r) / 2;
      if (counter[mid].back() >= des) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    if (cur[l] > des) {
      return l;
    }
    return -1;
  }
  bool valid(int pref) {
    cur.resize(pref);
    vector<int> vec;
    for (int i = 0; i <= pref; i++) {
      vec.push_back(glob[i]);
    }
    counter.clear();
    int ind = 0; /* the index of the first non-empty deque */
    int x = 0;   /* the smallest unpicked one */
    vec = remap(vec);
    int dum = 0;
    while (dum < vec.size() && vec[dum] == dum) {
      dum++;
      x++;
    }
    for (int i = dum; i < vec.size(); i++) {
      if (counter.empty()) {
        //nothing for elsie to do, so start a stack
        counter.push_back(create(vec[i]));
        cur[0] = vec[i];
        continue;
      }
      if (vec[i] == x) {
        x++;
        while (!counter[ind].empty() && counter[ind].back() == x) {
          x++;
          counter[ind].pop_back();
          if (counter[ind].empty()) {
            cur[ind] = -1;
            if (counter.size() > ind + 1) {
              ind++;
            }
          }else{
            cur[ind] = counter[ind].back();
          }
        }
        continue;
      }
      if (counter[ind].empty()) {
        counter.clear();
        ind = 0;
        counter.push_back(create(vec[i]));
        cur[ind] = vec[i];
        continue;
      }
      // We place the plate in some other stack
      int bind = bs(ind, counter.size() - 1, vec[i]);
      if (bind == -1) {
        counter.push_back(create(vec[i]));
        cur[counter.size() - 1] = vec[i];
      } else {
        counter[bind].push_back(vec[i]);
        cur[bind] = vec[i];
      }
    }
    vector<int> myVec;
    for (int i = 0; i < counter.size(); i++) {
      deque<int> d = counter[i];
      while (!d.empty()) {
        myVec.push_back(d.front());
        d.pop_front();
      }
    }
    //return 0;
    vector<int> temp = myVec;
    sort(temp.begin(), temp.end());
    return (temp == myVec);
  }
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    vector<int> v;
    for (int i = 0; i < n; i++) {
      int a;
      in >> a;
      v.push_back(a);
    }
    glob = v;
    int l = 0;
    int r = v.size() - 1;
    while (l < r) {
      int m = (l - r) / 2 + r;
      if (valid(m)) {
        l = m;
      } else {
        r = m - 1;
      }
    }
    out << l + 1 << endl;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
	Problem2Dishwashing solver;
	std::ifstream in("dishes.in");
	std::ofstream out("dishes.out");
	solver.solve(in, out);
	return 0;
}
