#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;
class Problem3SquarePasture {
public:
  unordered_map<int,pair<int,int>> y;
  int count(int x1, int x2, int y1, int y2){
    if(x1 > x2){
      swap(x1,x2);
    }
    if(y1 > y2){
      swap(y1,y2);
    }
    int ans = 0;
    for(int i = y1; i <= y2; i++){
      if(y[i].first >= x1 && y[i].first <= x2){
        ans++;
      }
    }
    return ans;
  }
  int e(int n, vector<pair<int,int>> v){
    int cntr = 0;
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        int width = v[i].first - v[j].first;
        int height = v[i].second - v[j].second;
        if(abs(height) == abs(width)){
          cntr++;
        }
      }
    }
    return cntr;
  }
  int g(int n, vector<pair<int,int>> v){
    int counter = 0;
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        for(int k = 0; k < n; k++){
          if(i == j || i == k || j == k){
            continue;
          }
          int leftmost = min(v[i].first,min(v[j].first,v[k].first));
          int rightmost = max(v[i].first,max(v[j].first,v[k].first));
          int downmost = min(v[i].second,min(v[j].second,v[k].second));
          if(leftmost != v[i].first || rightmost != v[j].first || downmost != v[k].second){
            continue;
          }
          if(v[k].first > rightmost || v[k].first < leftmost){
            continue;
          }
          int width = - leftmost + rightmost;
          if(y[downmost + width].first > leftmost && y[downmost + width].first < rightmost){
            //cout << i << " " << j << " " << k << " " << width << endl;
            counter++;
          }
        }
      }
    }
    return counter;
  }
  int f(vector<pair<int,int>> v, int n, std::istream& in, std::ostream& out){
    int counter = 0;
    y.clear();
    for(int i = 0; i < n; i++){
      y[v[i].second] = v[i];
    }
    for(int i = 0; i < n; i++){
      for(int j = i + 1; j < n; j++){
        //chose a rectangle with greater width than height
        int width = abs(v[i].first - v[j].first);
        int height = abs(v[i].second - v[j].second);
        if(width <= height){
          continue;
        }
        //width > height
        int rectCount = count(v[i].first,v[j].first,v[i].second, v[j].second);
        int x1 = min(v[i].first,v[j].first);
        int x2 = max(v[i].first,v[j].first);
        int y2 = max(v[i].second,v[j].second);
        int y1 = min(v[i].second,v[j].second);
        int squareCount = count(x1,x2,y2,y2 - width);
        counter++;
        //out << i << " " << j << " " << squareCount << endl;
        for(int lo = y2 - width + 1; lo <= y1; lo++){
          int hi = lo + width;
          //squareCount = num[hi] - num[lo - 1]
          int numHigh = (y[hi].first >= x1 && y[hi].first <= x2);
          int numLow = (y[lo - 1].first >= x1 && y[lo - 1].first <= x2);
          squareCount += numHigh - numLow;
          if(numHigh == 1 || numLow == 1){
            //out << i << " " << j << endl;
            counter++;
          }
        }
      }
    }
    return counter;
  }
  void solve(std::istream& in, std::ostream& out) {
    int n;
    in >> n;
    vector<pair<int,int>> v;
    for(int i = 0; i < n; i++){
      int a, b;
      in >> a >> b;
      a++;
      b++;
      v.push_back({a,b});
    }
    int x = f(v, n, in, out);
    int d = g(n, v);
    //out << x << endl;
    for(int i = 0; i < n; i++){
      swap(v[i].first, v[i].second);
    }
    int z = f(v, n, in, out);
    out << x + z + n + 1 - d + e(n,v) << endl;
  }
};
