#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
class Problem3SquarePasture {
public:
  static bool comp(pair<int, int> p1, pair<int,int> p2){
    return p1.second < p2.second;
  }
  vector<pair<int,int>> v1;
  bool inRange(int l, int r, int x){
    return (x >= l && x <= r);
  }
  int contains(int y1){
    int r = v1.size() - 1;
    int l = 0;
    while(r >= l){
      int mid = (r + l)/2;
      if(v1[mid].second == y1){
        return mid;
      }
      if(v1[mid].second < y1){
        l = mid + 1;
      }
      if(v1[mid].second > y1){
        r = mid - 1;
      }
    }
    return -1;
  }
  int interval(int y1, int y2, int x1, int x2){
    int counter = 0;
    for(int i = 0; i < v1.size(); i++){
      if(inRange(y1, y2, v1[i].second) && inRange(x1, x2, v1[i].first)){
        counter++;
      }
    }
    return counter;
  }
  int ans(std::istream& in, std::ostream& out, int n, vector<pair<int,int>> v){
    v1 = v;
    sort(v1.begin(), v1.end(),comp);
    int sum = 0;
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        int x1 = min(v[i].first, v[j].first);
        int x2 = max(v[i].first, v[j].first);
        int y1 = min(v[i].second, v[j].second);
        int y2 = max(v[i].second, v[j].second);
        int width = x2 - x1;
        int height = y2 - y1;
        if(height >= width) {
          continue;
        }
        //find out how much stuff is in the range [y2 - dx, y1]
        //find out how much stuff is in the interval [y2, y1 + dx]
        int a = interval(y2 - width, y1, x1, x2);
        int b = interval(y2, y1 + width, x1, x2);
        sum += a + b - 1;
        out << i << " " << j << " " << a + b - 1 << endl;
      }
    }
    return sum;
  }
  void solve(std::istream& in, std::ostream& out) {
    int n;
    in >> n;
    vector<pair<int,int>> v;
    for(int i = 0; i < n; i++){
      int a, b;
      in >> a >> b;
      v.push_back(make_pair(a,b));
    }
    int x = ans(in, out, n, v);
    v1 = v;
    sort(v1.begin(), v1.end(),comp);
    //out << x << endl;
    for(int i = 0; i < n; i++) {
      swap(v[i].first, v[i].second);
    }
    out << '-' << endl;
    int y = ans(in, out, n, v);
    out << y + x + n + 1 << endl;
  }
};
