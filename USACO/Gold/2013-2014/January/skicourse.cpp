#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
void convert (vector<string>& arr, char a, char b) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            if (arr[i][j] == a) {
                arr[i][j] = b;
            }
        }
    }
}

struct Grid {
    vector<vector<int>> grid;
    vector<vector<int>> sums;
    int find_sum (int l1, int r1, int l2, int r2) {
        return sums[l2 + 1][r2 + 1] - sums[l2 + 1][r1] - sums[l1][r2 + 1] + sums[l1][r1];
    }
    void fill () {
        sums.resize(grid.size() + 1);
        for (int i = 0; i < sums.size(); i++) {
            sums[i].resize(grid[0].size() + 1);
        }
        sums[0][0] = 0;
        for (int i = 1; i < sums.size(); i++) {
            sums[i][0] = 0;
        }
        for (int i = 1; i < sums[0].size(); i++) {
            sums[0][i] = 0;
        }
        for (int i = 1; i < sums.size(); i++) {
            for (int j = 1; j < sums[0].size(); j++) {
                sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
    }
    void resz (int n, int m) {
        grid.resize(n);
        for (int i = 0; i < n; i++) {
            grid[i].resize(m);
        }
    }
};

vector<pair<int,int>> pos (vector<string> arr, char c, int sz) {
    vector<vector<int>> grid(arr.size());
    for (int i = 0; i < grid.size(); i++) {
        grid[i].assign(arr[0].size(), false);
    }
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) {
            grid[i][j] = (arr[i][j] == c || arr[i][j] == 'X');
        }
    }
    Grid myGrid;
    myGrid.grid = grid;
    myGrid.fill();
    vector<pair<int,int>> updates;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) {
            if (i + sz - 1 >= arr.size() || j + sz - 1 >= arr[0].size()) {
                continue;
            }
            if (myGrid.find_sum(i, j, i + sz - 1, j + sz - 1) == sz * sz) {
                updates.emplace_back(i, j);
            }
        }
    }
    return updates;
}
bool update (vector<pair<int,int>> pos, vector<string> &arr, int sz) {
    for (auto& p: pos) {
        for (int i = p.first; i <= p.first + sz - 1; i++) {
            for (int j = p.second; j <= p.second + sz - 1; j++) {
                arr[i][j] = 'X';
            }
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[0].size(); j++) {
            if (arr[i][j] != 'X') {
                return false;
            }
        }
    }
    return true;
}
bool isValid (int sz, vector<string> arr) {
    int N = arr.size(); int M = arr[0].size();
    int mx = max(N, M);
    while (mx--) {
        if (update(pos(arr, 'R', sz), arr, sz)) return true;
        if (update(pos(arr, 'S', sz), arr, sz)) return true;
    }
    return false;
}
int main() {
    freopen("skicourse.in", "r", stdin);
    freopen("skicourse.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<string> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    int l = 0;
    int r = max(N, M);
    while (l != r) {
        int m = (l + r + 1)/2;
        if (isValid(m, arr)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    cout << l << '\n';
}
