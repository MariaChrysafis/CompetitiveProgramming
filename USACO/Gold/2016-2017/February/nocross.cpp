/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

#include <iostream>
#include <fstream>

#include <iostream>
#include <vector>
using namespace std;
class Problem2WhyDidTheCowCrossTheRoadII {
public:
  int N;
  vector<int> arr1;
  vector<int> arr2;
  vector<vector<int>> DP;
  int memoize(int x, int y){
    if(DP[x][y] != -1){
      return DP[x][y];
    }
    if(x == 0 && y == 0){
      DP[0][0] = (abs(arr1[x] - arr2[y]) <= 4);
      return DP[0][0];
    }
    if(x == 0){
      bool val = false;
      for(int j = 0; j <= y; j++){
        if(abs(arr1[x] - arr2[j]) <= 4){
          val = true;
          break;
        }
      }
      DP[x][y] = val;
      return DP[x][y];
    }
    if(y == 0){
      bool val = false;
      for(int j = 0; j <= x; j++){
        if(abs(arr1[j] - arr2[y]) <= 4){
          val = true;
        }
      }
      DP[x][y] = val;
      return DP[x][y];
    }
    int pos1 = memoize(x - 1, y - 1) + (abs(arr1[x] - arr2[y]) <= 4);
    int pos2 = max(memoize(x - 1,y),memoize(x,y - 1));
    DP[x][y] = max(pos1,pos2);
    return DP[x][y];
  }
  void solve(std::istream &in, std::ostream &out) {
    in >> N;
    arr1.resize(N);
    arr2.resize(N);
    for(int i = 0; i < N; i++){
      in >> arr1[i];
    }
    for(int i = 0; i < N; i++){
      in >> arr2[i];
    }
    DP.resize(N);
    for(int i = 0; i < N; i++){
      DP[i].resize(N);
      for(int j = 0; j < N; j++){
        DP[i][j] = -1;
      }
    }
    int a = memoize(N - 1, N - 1);
    out << a << endl;
  }
};


int main() {
	Problem2WhyDidTheCowCrossTheRoadII solver;
	std::ifstream in("nocross.in");
	std::ofstream out("nocross.out");
	solver.solve(in, out);
	return 0;
}
