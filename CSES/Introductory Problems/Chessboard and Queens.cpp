#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
 
using namespace std;
const int MOD = 1e9 + 7;
 
int cntr = 0;
 
void rec(vector<vector<char>> &vec, vector<pair<int,int>> queens) {
    cntr += (queens.size() == 8);
    if (vec.empty()) return;
    int prev;
    if (queens.empty()) prev = -1;
    else prev = queens.back().first;
    for (int i = prev + 1; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (vec[i][j] == '*') continue;
            bool fine = true;
            for (auto& q: queens) {
                if (make_pair(i, j) == q) {
                    fine = false;
                    break;
                }
                if (i == q.first || j == q.second) {
                    fine = false;
                    break;
                }
                if (abs(i - q.first) == abs(q.second - j)) {
                    fine = false;
                    break;
                }
            }
            if (fine) {
                queens.emplace_back(i, j);
                rec(vec, queens);
                queens.pop_back();
            }
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<char>> vec(8);
    for (int i = 0; i < 8; i++) {
        string s; cin >> s;
        vec[i].resize(8);
        for (int j = 0; j < 8; j++) {
            vec[i][j] = s[j];
        }
    }
    rec(vec, {});
    cout << cntr;
}
