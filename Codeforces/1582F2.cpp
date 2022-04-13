#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int arr[N];
    vector<int> v[8192];
    for (int i = 0; i < N; i++) {
        cin >> arr[i]; v[arr[i]].push_back(i);
    }
    int dp[8192]; for (int i = 0; i < 8192; i++) dp[i] = INT_MAX;
    dp[0] = -1;
    for (int i = 0; i < 8192; i++) {
        if (v[i].empty()) continue;
        for (int k = 0; k < 8192; k++) {
            int l = 0, r = (int)v[i].size() - 1;
            while (l != r) {
                int m = (l + r)/2;
                if (v[i][m] > dp[k]) r = m;
                else l = m + 1;
            }
            if (dp[k] < v[i][l]) dp[k ^ i] = min(v[i][l], dp[k ^ i]);
        }
    }
    vector<int> vec = {0};
    for (int i = 1; i < 8192; i++) if (dp[i] != INT_MAX) vec.push_back(i);
    cout << vec.size() << '\n';
    for (int i: vec) cout << i << ' ';
    cout << '\n';
}
