#include <iostream>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

class Problem3SquarePasture {
  struct coord{
    int x;
    int y;
    bool operator<(const coord& c) const{
      return (c.y < this->y);
    }
    bool operator==(coord c) const{
      return (c.y == y);
    }
  };
  coord myMin(coord a, coord b) {
    return {min(a.x,b.x),min(a.y, b.y)};
  }
  coord myMax(coord a, coord b) {
    return {max(a.x,b.x),max(a.y, b.y)};
  }
  bool isSquare(coord a, coord b){
    return (abs(a.x - b.x) == abs(a.y - b.y));
  }
  vector<coord> v1;

  static bool comp(coord p1, coord p2) {
    return p1.y < p2.y;
  }

  bool inRange(int l, int r, int x) {
    return (x >= l && x <= r);
  }

  int eq2(coord c1, coord c2, coord p1) {
    return (p1.x == c1.x || p1.x == c2.x) + (p1.y == c1.y || p1.y == c2.y);
  }

  int doubleCount(vector<coord> v) {
    int n = v.size();
    int counter = 0;
    for (int i = 0; i < n; i++) {
      coord curMin0 = v[i];
      coord curMax0 = v[i];
      for (int j = i + 1; j < n; j++) {
        coord curMin1 = myMin(curMin0, v[j]);
        coord curMax1 = myMax(curMax0, v[j]);
        for (int k = j + 1; k < n; k++) {
          coord curMin = myMin(curMin1, v[k]);
          coord curMax = myMax(curMax1, v[k]);
          //cout << curMax.x << " " << curMax.y << endl;
          if (eq2(curMin, curMax, v[i]) == 0 || eq2(curMin, curMax, v[j]) == 0 || eq2(curMin, curMax, v[k]) == 0) {
            continue;
          }
          if (isSquare(curMin, curMax)) {
            counter++;
          }
        }
      }
    }
    return counter;
  }

  int zerocount(vector<coord> v) {
    int counter = 0;
    int n = v.size();
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (isSquare(v[i],v[j])) {
          counter++;
        }
      }
    }
    return counter;
  }
  int count = 0;
  set<int> interval(int y1, int y2, int x1, int x2, int delta) {
    set<int> vec;
    for (int i = 0; i < v1.size(); i++) {
      if (inRange(y1, y2, v1[i].y) && inRange(x1, x2, v1[i].x)) {
        vec.insert(v1[i].y + delta);
      }
    }
    return vec;
  }
  int ans(std::istream &in, std::ostream &out, int n, vector<coord> v, bool b) {
    v1 = v;
    sort(v1.begin(), v1.end(), comp);
    int sum = 0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int x1 = min(v[i].x, v[j].x);
        int x2 = max(v[i].x, v[j].x);
        int y1 = min(v[i].y, v[j].y);
        int y2 = max(v[i].y, v[j].y);
        int width = x2 - x1;
        int height = y2 - y1;
        if(height > width){
          continue;
        }
        set<int> a = interval(y2 - width, y1 - 1, x1, x2, 1); /* lower */
        set<int> b = interval(y2 + 1, y1 + width, x1, x2, -width); /* upper */
        set<int> a1 = interval(y2 - width, y1 - 1, x1, x2, 0);
        vector<int> unite;
        set_union(a.begin(),a.end(),b.begin(),b.end(), std::back_inserter(unite));
        if(width != height){
          sum += unite.size() + 1;
        }else{
          count--;
        }
        unite.clear();
        set_union(a1.begin(),a1.end(),b.begin(),b.end(), std::back_inserter(unite));
        count += a.size() + b.size() - unite.size();
      }
    }
    return sum;
  }

public: void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    vector<coord> v;
    for (int i = 0; i < n; i++) {
      int a, b;
      in >> a >> b;
      v.push_back({a, b});
    }
    int x = ans(in, out, n, v, 0);
    for (int i = 0; i < n; i++) {
      swap(v[i].x, v[i].y);
    }
    int y = ans(in, out, n, v, 1);
    out << y + x + n + 1 - count/2 - doubleCount(v) << endl;
  }
};
