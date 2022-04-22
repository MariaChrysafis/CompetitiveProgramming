#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <map>
#include <complex>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
using namespace std;
void print (vector<string> vec) {
    for (auto& s: vec) {
        cout << s << '\n';
    }
}
void stimulate (vector<string>& grid) {
    for (int i = grid.size() - 2; i >= 0; i--) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '*') {
                if (grid[i + 1][j] == '*' || grid[i + 1][j] == 'o') continue;
                swap(grid[i][j], grid[i + 1][j]);
            }
        }
    }
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<string> grid(n);
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        int tc = 50;
        while (tc--) {
            stimulate(grid);
        }
        print(grid);
    }
}
