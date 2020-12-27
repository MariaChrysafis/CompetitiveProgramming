#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
class Problem3SquarePasture {
public:
  int min4(int a, int b, int c, int d){
    return min(min(a, b), min(c, d));
  }
  int max4(int a, int b, int c, int d){
    return max(max(a, b), max(c, d));
  }
  int min3(int a, int b, int c){
    return min(min(a,b),c);
  }
  int max3(int a, int b, int c){
    return max(max(a,b),c);
  }
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
  int double_count(vector<pair<int,int>> v){
    int n = v.size();
    int counter = 0;
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        for(int k = j + 1; k < n; k++){
          int x1 = min3(v[i].first, v[j].first, v[k].first);
          int x2 = max3(v[i].first, v[j].first, v[k].first);
          int y1 = min3(v[i].second, v[j].second, v[k].second);
          int y2 = max3(v[i].second, v[j].second, v[k].second);
          if(x2 - x1 == y2 - y1){
            counter++;
          }
        }
      }
    }
    return counter;
  }
  int over_count(vector<pair<int,int>> v){
    int n = v.size();
    int counter = 0;
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        for(int k = j + 1; k < n; k++){
          for(int l = k + 1; l < n; l++){
            int x1 = min4(v[i].first, v[j].first, v[k].first, v[l].first);
            int x2 = max4(v[i].first, v[j].first, v[k].first, v[l].first);
            int y1 = min4(v[i].second, v[j].second, v[k].second, v[l].second);
            int y2 = max4(v[i].second, v[j].second, v[k].second, v[l].second);
            if(x2 - x1 == y2 - y1){
              counter++;
            }
          }
        }
      }
    }
    return counter;
  }
  int zero_count(vector<pair<int,int>> v){
    int counter = 0;
    int n = v.size();
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        int width = max(v[i].first, v[j].first) - min(v[i].first, v[j].first);
        int height = max(v[i].second, v[j].second) - min(v[i].second, v[j].second);
        if(width == height){
          counter++;
        }
      }
    }
    return counter;
  }
  vector<pair<int, int>> interval(int y1, int y2, int x1, int x2){
    vector<pair<int, int>> vec;
    for(int i = 0; i < v1.size(); i++){
      if(inRange(y1, y2, v1[i].second) && inRange(x1, x2, v1[i].first)){
        vec.push_back(v1[i]);
      }
    }
    return vec;
  }
  vector<pair<int,int>> merge(vector<pair<int,int>> v2, vector<pair<int, int>> v3){
    vector<pair<int,int>> vec;
    sort(v2.begin(), v2.end(), comp);
    sort(v3.begin(), v3.end(), comp);
    int i2 = 0;
    int i3 = 0;
    while(i2 != v2.size() || i3 != v3.size()){
      if(i2 == v2.size()) {
        vec.push_back(v3[i3]);
        i3++;
        continue;
      }
      if(i3 == v3.size()) {
        vec.push_back(v2[i2]);
        i2++;
        continue;
      }
      if(v2[i2].second < v3[i3].second){
        vec.push_back(v2[i2]);
        i2++;
      }
      else if(v2[i2].second > v3[i3].second){
        vec.push_back(v3[i3]);
        i3++;
      }else{
        vec.push_back(v2[i2]);
        i2++;
        i3++;
      }
    }
    return vec;
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
        vector<pair<int,int>> a = interval(y2 - width, y1 - 1, x1, x2); /* lower */
        vector<pair<int,int>> b = interval(y2 + 1, y1 + width, x1, x2); /* upper */
        for(int i = 0; i < b.size(); i++){
          b[i].second -= width;
        }
        for(int i = 0; i < a.size(); i++){
          a[i].second--;
        }
        vector<pair<int, int>> vec = merge(a, b);
        sum += vec.size() + 1;
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
    for(int i = 0; i < n; i++) {
      swap(v[i].first, v[i].second);
    }
    //out << '-' << endl;
    int y = ans(in, out, n, v);
    out << y + x + n + 1 + zero_count(v) - over_count(v) - double_count(v) << endl;
  }
};
