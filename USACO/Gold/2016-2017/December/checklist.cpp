#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
using namespace std;
class Problem2CowChecklist {
public:
  int H,G;
  struct coord{
    long long x;
    long long y;
  };
  long long distance(coord a, coord b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  }
  vector<coord> v[2];
  long long dp[2][1002][1002];
  long long INF = 1000000000;
  long long fill(int i, int h, int g){
    /*
     * H H H H H H
     * G G G
     * H --> 0
     * G --> 1
     */
    if(h == v[0].size() - 1 && g == v[1].size() - 1){
      return 0;
    }
    if(h == v[0].size() - 1){
      return INF;
    }
    if(g == v[1].size() - 1){
      if(i == 0) {
        dp[i][h + 1][g + 1] = fill(0,h + 1,g) + distance(v[0][h],v[0][h + 1]);
      }else{
        dp[i][h + 1][g + 1] = fill(0,h + 1, g) + distance(v[1][g], v[0][h + 1]);
      }
      return dp[i][h + 1][g + 1];
    }
    if(dp[i][h + 1][g + 1] != -1){
      return dp[i][h + 1][g + 1];
    }
    if(i == 0){
      //the last one we took is v[0][h]
      int pos1 = fill(1, h,g + 1) + distance(v[1][g + 1],v[0][h]);
      int pos2 = fill(0,h + 1, g) + distance(v[0][h],v[0][h + 1]);
      dp[i][h + 1][g + 1] = min(pos1,pos2);
      return dp[i][h + 1][g + 1];
    }else{
      //the last one we took is v[1][g]
      int pos1 = fill(1,h,g + 1) + distance(v[1][g],v[1][g + 1]);
      int pos2 = fill(0,h + 1, g) + distance(v[1][g],v[0][h + 1]);
      dp[i][h + 1][g + 1] = min(pos1,pos2);
      return dp[i][h + 1][g + 1];
    }
  }
  void solve(std::istream& in, std::ostream& out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    in >> H >> G;
    while(H--){
      int x,y;
      in >> x >> y;
      v[0].push_back({x,y});

    }
    while(G--){
      int x,y;
      in >> x >> y;
      v[1].push_back({x,y});
    }
    for(int i = 0; i < 2; i++){
      for(int j = 0; j < 1001; j++){
        for(int k = 0; k < 1001; k++){
          dp[i][j][k] = -1;
        }
      }
    }
    int x = fill(0,0,-1);
    out << x << endl;
  }
};
int main(){
   Problem2CowChecklist solver;
   ifstream in("checklist.in");
   ofstream out("checklist.out");
   solver.solve(in,out);
}
