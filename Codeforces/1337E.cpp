#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
 
#define ll long long
using namespace std;
vector<vector<int>> dp;
string s, t;
const int MOD = 998244353;
vector<int> powr;
int memoize(int i, int j){
    //(j, ... , j + i)
    if(i == 0){
        return (t[j] == s[i]) * 2;
    }
    if(dp[i][j] != -1){
        return dp[i][j];
    }
    dp[i][j] = 0;
    if(s[i] == t[j]){
        if(j == t.length() - 1){
            dp[i][j] += powr[i];
        }else {
            dp[i][j] += memoize(i - 1, j + 1);
        }
    }
    if(j + i >= t.length() || t[j + i] == s[i]){
        dp[i][j] += memoize(i - 1, j);
    }
    return (dp[i][j] = dp[i][j] % MOD);
}
void solve(){
    cin >> s >> t;
    dp.resize(s.length());
    for(int i = 0; i < dp.size(); i++){
        dp[i].resize(t.length());
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = -1;
        }
    }
    powr.resize(3001);
    powr[0] = 1;
    for(int i = 1; i < powr.size(); i++){
        powr[i] = (2 * powr[i - 1]) % MOD;
    }
    int ans = 0;
    for(int i = t.length() - 1; i < s.length(); i++){
        ans += memoize(i, 0);
        if(ans > MOD) ans -= MOD;
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
 
}
