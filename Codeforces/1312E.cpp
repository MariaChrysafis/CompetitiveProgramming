#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
vector<vector<int>> dp;
void solve() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
            if (i == j) {
                dp[i][j] = arr[i];
            }
        }
    }
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i < n; i++) {
            int j = i + len;
            if (j >= n) continue;
            for (int k = i; k < j; k++) {
                if (dp[i][k] != -1 && dp[k + 1][j] != -1) {
                    if (dp[i][k] == dp[k + 1][j]) {
                        dp[i][j] = dp[k + 1][j] + 1;
                    }
                }
            }
        }
    }
    int pref[n];
    for(int i = 0; i < n; i++){
        if(dp[0][i] != -1){
            pref[i] = 1;
            continue;
        }
        pref[i] = pref[i - 1] + 1;
        for(int j = 0; j < i; j++){
            if(dp[j + 1][i] == -1){
                continue;
            }
            pref[i] = min(pref[j] + 1, pref[i]);
        }
    }
    cout << pref[n - 1] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
