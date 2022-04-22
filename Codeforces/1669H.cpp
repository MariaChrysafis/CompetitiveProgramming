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
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        vector<int> cnt(31);
        cnt.assign(31, 0);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            for (int j = 0; j <= 30; j++) {
                if (!(arr[i] & (1 << j))) {
                    cnt[j]++;
                }
            }
        }
        int ans = 0;
        for (int i = cnt.size() -1 ; i >= 0; i--) {
            if (cnt[i] <= k) {
                k -= cnt[i];
                ans += (1 << i);
            }
        }
        cout << ans << '\n';
    }
}
