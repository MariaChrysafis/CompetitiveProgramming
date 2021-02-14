#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;
class Problem3LightsOut {
public:
  struct coord{
    int x;
    int y;
  };
  struct edge{
    coord c1;
    coord c2;
  };
  char pos(edge e){
    if(e.c1.y == e.c2.y){
      //then we're down a horizontal move
      if(e.c1.x < e.c2.x){
        return 'D';
      }else{
        return 'U';
      }
    }
    if(e.c1.x == e.c2.x){
      //then we're doing a vertical move
      if(e.c1.y < e.c2.y){
        return 'L';
      }else{
        return 'R';
      }
    }
  }
  int length(edge e1){
    return abs(e1.c1.x - e1.c2.x) + abs(e1.c1.y - e1.c2.y);
  }
  bool flip(edge e1, edge e2, edge e3){
    return pos(e1) == pos(e3);
  }
  int dist(vector<int> v){
    int sum = 0;
    for(int i = 1; i < v.size(); i += 2){
      sum += v[i];
    }
    return sum;
  }
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    vector<coord> v1;
    vector<edge> v2;
    for(int i = 0; i < n; i++){
      int a,b;
      in >> a >> b;
      v1.push_back({a,b});
    }
    v2.push_back({v1[n - 1],v1[0]});
    for(int i = 0; i < n - 1; i++){
      v2.push_back({v1[i],v1[i + 1]});
    }
    int angle[n];
    angle[0] = 'b';
    for(int i = 1; i < n; i++){
      bool b = flip(v2[i],v2[(i + 1) % n],v2[(i + 2) % n]);
      if(!b){
        angle[i] = angle[i - 1];
      }else{
        angle[i] = !angle[i - 1];
      }
    }
    int minDist[n];
    for(int i = 0; i < n; i++){
      //we could go clockwise
      int dist1 = 0;
      for(int d = 0; d < n; d++){
        if((i + d) % n == 0){
          break;
        }
        dist1 += length(v2[(i + d + 1) % n]);
      }
      int dist2 = 0;
      for(int d = 0; d < n; d++){
        if((i - d + n) % n == 0){
          break;
        }
        dist2 += length(v2[(i - d) % n]);
      }
      minDist[i] = min(dist1,dist2);
    }
    vector<vector<int>> v(n);
    multiset<vector<int>> ms;
    for(int i = 0; i < n; i++){
      vector<int> myVec;
      myVec.push_back(angle[i]);
      for(int d = 0; d < n; d++){
        myVec.push_back(length(v2[(i + d + 1) % n]));
        myVec.push_back(angle[(i + d + 1) % n]);
        ms.insert(myVec);
        if((i + d) % n == 0){
          continue;
        }
      }
    }
    for(int i = 0; i < n; i++){
      vector<int> myVec;
      myVec.push_back(angle[i]);
      for(int d = 0; d < n; d++){
        if(ms.count(myVec) == 1 || (i + d) % n == 0){
          v[i] = myVec;
          break;
        }
        myVec.push_back(length(v2[(i + d + 1) % n]));
        myVec.push_back(angle[(i + d + 1) % n]);
      }
    }
    int myMax = 0;
    for(int i = 0; i < n; i++){
      int x = (v[i].size() - 1)/2;
      myMax = max(dist(v[i]) + minDist[(i + x) % n] - minDist[i],myMax);
    }
    out << myMax << endl;
  }
};
