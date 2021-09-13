#include <iostream>
#include <vector>
#include <fstream>

#include <map>
#include <set>
#include <algorithm>

using namespace std;
vector<int> read(int n){
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}
void solve() {
    int n;
    cin >> n;
    vector<int> v = read(n);
    int dp[n][60];
    int myMax = 0;
    for(int i = n - 1; i >= 0; i--){
        for(int j = 0; j < 60; j++){
            dp[i][j] = -1;
        }
        dp[i][v[i]] = i;
        if(i == n - 1) continue;
        for(int j = v[i] + 1; j < 60; j++){
            if(dp[i][j - 1] == -1 || dp[i][j - 1] == n - 1) continue;
            dp[i][j] = dp[dp[i][j - 1] + 1][j - 1];
            if(dp[i][j] != -1){
                myMax = max(myMax, j);
            }
        }
    }
    cout << myMax <<endl;
}

int main() {
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
