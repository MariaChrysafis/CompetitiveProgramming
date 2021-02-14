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
  int dist(string s){
    if(s.length() == 0){
      return 0;
    }
    string str;
    int sum = 0;
    for(int i = 0; i < s.length(); i++){
      if(s[i] == 'a' || s[i] == 'b'){
        if(str.length() != 0) sum += stoi(str);
        str = " ";
      }else{
        str += s[i];
      }
    }
    if(str.length() != 0){
      sum += stoi(str);
    }
    return sum;
  }
  int len(string s){
    int cntr = 0;
    for(char c: s){
      if(c == 'a' || c == 'b'){
        cntr++;
      }
    }
    return cntr;
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
    char angle[n];
    angle[0] = 'a';
    for(int i = 1; i < n; i++){
      bool b = flip(v2[i],v2[(i + 1) % n],v2[(i + 2) % n]);
      if(b == false){
        angle[i] = angle[i - 1];
      }else{
        if(angle[i - 1] == 'a'){angle[i] = 'b';}
        if(angle[i - 1] == 'b'){angle[i] = 'a';}
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
    vector<string> v(n);
    bool finished[n];
    for(int i = 0; i < n; i++){
      finished[i] = false;
    }
    finished[0] = false;
    for(int d = 0; d < n; d++){
      int cntr = 0;
      for(int i = 1; i < n; i++){
        if(finished[i]){
          cntr++;
          continue;
        }
        if((i + d) % n == 0){
          finished[i] = true;
          continue;
        }
        v[i] += angle[(i + d) % n];
        v[i] += to_string(length(v2[(i + d + 1) % n]));
      }
      for(int i = 0; i < n; i++){
        if(finished[i]) continue;
        int c = 0;
        for(int j = 0; j < n; j++){
          if(i == j) continue;
          if(v[i] != v[j]){
            c++;
          }
        }
        if(c == n - 1){
          finished[i] = true;
        }
      }
    }
    int myMax = 0;
    for(int i = 0; i < n; i++){
      int x = len(v[i]);
      myMax = max(dist(v[i]) + minDist[(i + x) % n] - minDist[i],myMax);
    }
    out << myMax << endl;
  }
};
