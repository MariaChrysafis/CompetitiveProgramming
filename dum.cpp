#include <iostream>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Problem3SquarePasture {
  struct coord{
    int x;
    int y;
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

  int overCount(vector<coord> v) {
    int n = v.size();
    int counter = 0;
    for (int i = 0; i < n; i++) {
      coord curMin0 = v[i];
      coord curMax0 = v[i];
      for (int j = i + 1; j < n; j++) {
        coord curMin1 = myMin(curMin0, v[j]);
        coord curMax1 = myMax(curMax0, v[j]);
        for (int k = j + 1; k < n; k++) {
          coord curMin2 = myMin(curMin1, v[k]);
          coord curMax2 = myMax(curMax1, v[k]);
          for (int l = k + 1; l < n; l++) {
            coord curMin = myMin(curMin2, v[l]);
            coord curMax = myMax(curMax2, v[l]);
            if (eq2(curMin, curMax, v[i]) != 1 || eq2(curMin,curMax,v[j]) != 1 || eq2(curMin, curMax, v[k]) != 1 || eq2(curMin, curMax, v[l]) != 1) {
              continue;
            }
            if (isSquare(curMin, curMax)) {
              counter++;
            }
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

  vector<coord> interval(int y1, int y2, int x1, int x2) {
    vector<coord> vec;
    for (int i = 0; i < v1.size(); i++) {
      if (inRange(y1, y2, v1[i].y) && inRange(x1, x2, v1[i].x)) {
        vec.push_back(v1[i]);
      }
    }
    return vec;
  }

  int merge(vector<coord> v2, vector<coord> v3) {
    int i2 = 0;
    int i3 = 0;
    int counter = 0;
    while (i2 != v2.size() || i3 != v3.size()) {
      counter++;
      if (i2 == v2.size()) {
        i3++;
      }
      else if (i3 == v3.size()) {
        i2++;
      }
      else if (v2[i2].y < v3[i3].y) {
        i2++;
      }
      else if (v2[i2].y > v3[i3].y) {
        i3++;
      }
      else {
        i2++;
        i3++;
      }
    }
    return counter;
  }

  int ans(std::istream &in, std::ostream &out, int n, vector<coord> v) {
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
        if (height >= width) {
          continue;
        }
        vector<coord> a = interval(y2 - width, y1 - 1, x1, x2); /* lower */
        vector<coord> b = interval(y2 + 1, y1 + width, x1, x2); /* upper */
        for (int i = 0; i < b.size(); i++) {
          b[i].y -= width;
        }
        for (int i = 0; i < a.size(); i++) {
          a[i].y++;
        }
        sum += merge(a, b) + 1;
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
    int x = ans(in, out, n, v);
    for (int i = 0; i < n; i++) {
      swap(v[i].x, v[i].y);
    }
    int y = ans(in, out, n, v);
    out << y + x + n + 1 + zerocount(v) - overCount(v) - doubleCount(v) << endl;
  }
};
