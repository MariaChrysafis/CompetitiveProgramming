#include <iostream>
#include <map>
#include <vector>
using namespace std;
class Problem2RectangularPasture {
public:
    long long dp[2501][2501];
    long long strip(int x, int y1, int y2){
      if(y1 == 0){
        return dp[x][y2];
      }
      if(x == -1){
        return 0;
      }
      return dp[x][y2] - dp[x][y1 - 1];
    }
    long long rect(int x1, int x2, int y1, int y2){
      return strip(x2, y1, y2) - strip(x1 - 1, y1, y2);
    }
	void solve(std::istream& in, std::ostream& out) {
	  // coordinate compression
	  int n;
	  in >> n;
      vector<pair<int,int>> inp;
      vector<pair<int,int>> v;
      map<pair<int,int>,bool> coord;
      inp.resize(n);
      map<int,int> ox;
      map<int,int> oy;
      for(int i = 0; i < n; i++){
        in >> inp[i].first >> inp[i].second;
        ox[inp[i].first]++;
        oy[inp[i].second]++;
      }
      map<int,int> ix;
      map<int,int> iy;
      int indx = 0;
      for(pair<int,int> p: ox){
        ix[p.first] = indx;
        indx++;
      }
      int indy = 0;
      for(pair<int,int> p: oy){
        iy[p.first] = indy;
        indy++;
      }
      for(pair<int,int> p: inp){
        v.push_back({ix[p.first],iy[p.second]});
        coord[{ix[p.first],iy[p.second]}] = true;
      }
      //v stores our new coordinates
      dp[0][0] = coord[{0,0}];
      for(int i = 0; i < indx; i++){
        for(int j = 0; j < indy; j++){
          if(i == 0 && j == 0){
            continue;
          }
          if(i == 0){
            dp[i][j] = dp[i][j - 1] + coord[{i,j}];
            continue;
          }
          if(j == 0){
            dp[i][j] = dp[i - 1][j] + coord[{i,j}];
            continue;
          }
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + coord[{i,j}];
        }
      }
      long long sum = n + 1;
      for(int i = 0; i < indx; i++){
        for(int j = i + 1; j < indy; j++){
          int x1 = v[i].first;
          int x2 = v[j].first;
          int y1 = v[i].second;
          int y2 = v[j].second;
          if(x1 > x2){
            swap(x1,x2);
          }
          if(y1 > y2){
            swap(y1, y2);
          }
          sum += strip(x1,y1,y2) *  rect(x2, n - 1, y1, y2);
        }
      }
      out << sum << endl;
	}

};
