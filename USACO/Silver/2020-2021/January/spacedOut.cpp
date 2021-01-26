/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author
 */

//Created by Maria Chrysafis
#include <iostream>
#include <fstream>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Problem3SpacedOut {
public:
  vector<vector<int>> mat;
  int N;
  int MAX(){
    int counter = 0;
    for(int i = 0; i < N; i++){
      int cur = 0;
      int pos = 0;
      for(int j = 0; j < N; j++){
        if((abs(i - j)) % 2 == 0){
          cur += mat[i][j];
        }
        pos += mat[i][j];
      }
      cur = max(cur, pos - cur);
      counter += cur;
    }
    return counter;
  }
  int MAX1(){
    int counter = 0;
    for(int i = 0; i < N; i++){
      int cur = 0;
      int pos = 0;
      for(int j = 0; j < N; j++){
        if((i + j) % 2 == 0){
          cur += mat[i][j];
        }
        pos += mat[i][j];
      }
      cur = max(cur, pos - cur);
      counter += cur;
    }
    return counter;
  }
  void solve(std::istream& in, std::ostream& out) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    in >> N;
    mat.resize(N);
    for(int i = 0; i < N; i++){
      mat[i].resize(N);
      for(int j = 0; j < N; j++){
        in >> mat[i][j];
      }
    }
    int ANS = max(MAX(),MAX1());
    vector<vector<int>> new_mat = mat;
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        new_mat[j][i] = mat[i][j];
      }
    }
    mat = new_mat;
    ANS = max(MAX(),max(ANS,MAX1()));
    out << ANS << endl;
  }
};


int main() {
	Problem3SpacedOut solver;
	std::istream& in(std::cin);
	std::ostream& out(std::cout);
	solver.solve(in, out);
	return 0;
}
