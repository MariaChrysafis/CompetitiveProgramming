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
class DWalkOnMatrix {
public:
    const int INF = 262143;
    int solve(vector<vector<int>> v){
      vector<vector<int>> dp = v;
      for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
          dp[i][j] = 0;
        }
      }
      dp[0][0] = v[0][0];
      for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v[0].size(); j++){
          if(i == 0 && j == 0){
            continue;
          }
          if(i == 0){
            dp[i][j] = dp[i][j - 1] & v[i][j];
            continue;
          }
          if(j == 0){
            dp[i][j] = dp[i - 1][j] & v[i][j];
            continue;
          }
          dp[i][j] = max(dp[i - 1][j] & v[i][j], dp[i][j - 1] & v[i][j]);
        }
      }
      /*
      for(int i = 0; i < dp.size(); i++){
        for(int j: dp[i]){
          cout << j << " ";
        }
        cout << endl;
      }
       */
      return dp[v.size() - 1][v[0].size() - 1];
    }
	void solve(std::istream& in, std::ostream& out) {
	  int k;
	  in >> k;
	  vector<vector<int>> mat;
	  mat.resize(3);
	  for(int i = 0; i < 3; i++){
        mat[i].resize(4);
	  }
	  out << 3 << " " << 4 << endl;
	  mat[0] = {INF,k,k,0};
	  mat[1] = {(INF + 1)/2,0,k,0};
	  mat[2] = {INF,INF,INF,k};
      for(int i = 0; i < mat.size(); i++){
        for(int j: mat[i]){
          out << j << " ";
        }
        out << endl;
      }
	}
};


int main() {
	DWalkOnMatrix solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
