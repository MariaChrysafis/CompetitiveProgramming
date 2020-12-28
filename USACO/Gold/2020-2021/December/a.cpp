#include <iostream>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Problem3SquarePasture {
public:
  class coord {
  public:
    coord(int x, int y) : x(x), y(y) {}

  public:
    coord min(const coord & other) {
      return coord(std::min(other.x, this->x), std::min(other.y, this->y));
    }
    coord max(const coord & other) {
      return coord(std::max(other.x, this->x), std::max(other.y, this->y));
    }

  public:
    int x;
    int y;
  };

vector<coord> v1;
static int min3(int a, int b, int c) {
  return min(min(a, b), c);
}

static int max3(int a, int b, int c) {
  return max(max(a, b), c);
}

static bool comp(coord p1, coord p2) {
  return p1.y < p2.y;
}

bool inRange(int l, int r, int x) {
  return (x >= l && x <= r);
}

int eq2(int x1, int x2, int y1, int y2, coord p1) {
  int x = 0;
  if (p1.x == x1 || p1.x == x2) {
    x++;
  }
  int y = 0;
  if (p1.y == y1 || p1.y == y2) {
    y++;
  }
  return x + y;
}

int doubleCount(vector<coord> v) {
  int n = v.size();
  int counter = 0;
  for (int i = 0; i < n; i++) {
    coord curMin0 = v[i];
    coord curMax0 = v[i];
    for (int j = i + 1; j < n; j++) {
      coord curMin1 = curMin0.min(v[j]);
      coord curMax1 = curMax0.max(v[j]);
      for (int k = j + 1; k < n; k++) {
        coord curMin2 = curMin1.min(v[k]);
        coord curMax2 = curMax1.max(v[k]);
        int x1 = curMin2.x;
        int x2 = curMax2.x;
        int y1 = curMin2.y;
        int y2 = curMax2.y;
        if (eq2(x1, x2, y1, y2, v[i]) == 0 || eq2(x1, x2, y1, y2, v[j]) == 0 ||
            eq2(x1, x2, y1, y2, v[k]) == 0) {
          continue;
        }
        if (x2 - x1 == y2 - y1) {
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
      coord curMax1 = curMax0.max(v[j]);
      coord curMin1 = curMin0.min(v[j]);
      for (int k = j + 1; k < n; k++) {
        coord curMax2 = curMax1.max(v[k]);
        coord curMin2 = curMin1.min(v[k]);
        for (int l = k + 1; l < n; l++) {
          coord curMax = curMax2.max(v[l]);
          coord curMin = curMin2.min(v[l]);
          int x1 = curMin.x;
          int x2 = curMax.x;
          int y1 = curMin.y;
          int y2 = curMax.y;
          if (eq2(x1, x2, y1, y2, v[i]) != 1 || eq2(x1, x2, y1, y2, v[j]) != 1) {
            continue;
          }
          if (eq2(x1, x2, y1, y2, v[k]) != 1 || eq2(x1, x2, y1, y2, v[l]) != 1) {
            continue;
          }
          if (x2 - x1 == y2 - y1) {
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
      int width = max(v[i].x, v[j].x) - min(v[i].x, v[j].x);
      int height = max(v[i].y, v[j].y) - min(v[i].y, v[j].y);
      if (width == height) {
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
      continue;
    }
    if (i3 == v3.size()) {
      i2++;
      continue;
    }
    if (v2[i2].y < v3[i3].y) {
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

void solve(std::istream &in, std::ostream &out) {
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
  //out << '-' << endl;
  int y = ans(in, out, n, v);
  out << y + x + n + 1 + zerocount(v) - overCount(v) - doubleCount(v) << endl;
}
};
