#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int inversions(vector<int> v) {
  int pref[v.size() + 1];
  pref[0] = 0;
  for (int i = 1; i <= v.size(); i++) {
    pref[i] = pref[i - 1] + (v[i - 1] == 1);
  }
  int cntr = 0;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == 0) {
      cntr += pref[i];
    }
  }
  return cntr;
}
class Problem3BalancingInversions {
public:
  void solve(std::istream &in, std::ostream &out) {
    int n;
    in >> n;
    vector<int> v1(n);
    vector<int> v2(n);
    for (int i = 0; i < n; i++) {
      in >> v1[i];
    }
    for (int i = 0; i < n; i++) {
      in >> v2[i];
    }
    /*
    if(inversions(v1) < inversions(v2)){
      swap(v1, v2);
    }
     */
    long long myMin = 0;
    if (inversions(v1) > inversions(v2)) {
      vector<int> ones;
      vector<int> zeroes;
      for (int i = n - 1; i >= 0; i--) {
        if (v1[i] == 1) {
          ones.push_back(i);
        }
      }
      for (int i = 0; i < n; i++) {
        if (v2[i] == 0) {
          zeroes.push_back(i);
        }
      }
      long long moves = 0;
      long long dif = inversions(v1) - inversions(v2);
      myMin = dif;
      for (int t = 0; t < min(zeroes.size(), ones.size()); t++) {
        int dist1 = n - 1 - ones[t];
        int dist2 = zeroes[t];
        moves += dist1 + dist2 + 1;
        dif += ones.size() - dist1 - zeroes.size() + dist2;
        myMin = min(abs(dif) + moves, myMin);
      }
    } else {
      long long moves = 0;
      long long dif = inversions(v2) - inversions(v1);
      vector<int> ones;
      vector<int> zeroes;
      myMin = dif;
      for (int i = n - 1; i >= 0; i--) {
        if (v1[i] == 0) {
          zeroes.push_back(i);
        }
      }
      for (int i = 0; i < n; i++) {
        if (v2[i] == 1) {
          ones.push_back(i);
        }
      }
      for (int t = 0; t < min(zeroes.size(), ones.size()); t++) {
        int dist1 = ones[t];
        int dist2 = n - 1 - zeroes[t];
        moves += dist1 + dist2 + 1;
        dif += ones.size() - dist2 - zeroes.size() + dist1;
        myMin = min(abs(dif) + moves, myMin);
      }
    }
    out << myMin << endl;
  }
};
