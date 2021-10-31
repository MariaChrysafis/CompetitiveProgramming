#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll signed long long int
#pragma GCC optimize("Ofast")
using namespace std;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n);
    vector<pair<vector<int>,int>> vec(n);
    for (int i = 0; i < n; i++) {
        arr[i].resize(m);
        vec[i].first.resize(m);
        vec[i].second = i;
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            //cin >> vec[i].first[j];
            vec[i].first[j] = arr[i][j];
        }
    }
    sort(arr.begin(), arr.end());
    reverse(arr.begin(), arr.end());
    sort(vec.begin(), vec.end());
    reverse(vec.begin(), vec.end());
    vector<vector<int>> top_left(n);
    for (int i = 0; i < n; i++) {
        top_left[i].resize(m);
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                top_left[i][j] = arr[i][j];
            } else if (i == 0) {
                top_left[i][j] = min(top_left[i][j - 1], arr[i][j]);
            } else if (j == 0) {
                top_left[i][j] = min(top_left[i - 1][j], arr[i][j]);
            } else {
                top_left[i][j] = min(min(top_left[i - 1][j], top_left[i][j - 1]), arr[i][j]);
            }
        }
    }
    vector<vector<int>> bottom_right(n);
    for (int i = n - 1; i >= 0; i--) {
        bottom_right[i].resize(m);
        for (int j = m - 1; j >= 0; j--) {
            if (i == n - 1 && j == m - 1) {
                bottom_right[i][j] = arr[i][j];
            } else if (i == n - 1) {
                bottom_right[i][j] = min(bottom_right[i][j + 1], arr[i][j]);
            } else if (j == m - 1) {
                bottom_right[i][j] = min(bottom_right[i + 1][j], arr[i][j]);
            } else {
                bottom_right[i][j] = min(min(bottom_right[i + 1][j], bottom_right[i][j + 1]), arr[i][j]);
            }
        }
    }
    vector<vector<int>> top_right(n);
    for (int i = 0; i < n; i++) {
        top_right[i].resize(m);
        for (int j = m - 1; j >= 0; j--) {
            if (i == 0 && j == m - 1) {
                top_right[i][j] = arr[i][j];
            } else if (i == 0) {
                top_right[i][j] = max(top_right[i][j + 1], arr[i][j]);
            } else if (j == m - 1) {
                top_right[i][j] = max(top_right[i - 1][j], arr[i][j]);
            } else {
                top_right[i][j] = max(max(top_right[i - 1][j], top_right[i][j + 1]), arr[i][j]);
            }
        }
    }
    vector<vector<int>> bottom_left(n);
    for (int i = n - 1; i >= 0; i--) {
        bottom_left[i].resize(m);
        for (int j = 0; j < m; j++) {
            if (i == n - 1 && j == 0) {
                bottom_left[i][j] = arr[i][j];
            } else if (i == n - 1) {
                bottom_left[i][j] = max(bottom_left[i][j - 1], arr[i][j]);
            } else if (j == 0) {
                bottom_left[i][j] = max(bottom_left[i + 1][j], arr[i][j]);
            } else {
                bottom_left[i][j] = max(max(bottom_left[i + 1][j], bottom_left[i][j - 1]), arr[i][j]);
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            int tl = top_left[i][j];
            int tr = top_right[i][j + 1];
            int bl = bottom_left[i + 1][j];
            int br = bottom_right[i + 1][j + 1];
            if (tl > bl && br > tr) {
                cout << "YES\n";
                string ans;
                for (int a = 0; a < n; a++) {
                    ans += 'B';
                }
                for (int a = 0; a <= i; a++) {
                    ans[vec[a].second] = 'R';
                }
                cout << ans << " " << j + 1 << '\n';
                return;
            }
        }
    }
    cout << "NO\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
