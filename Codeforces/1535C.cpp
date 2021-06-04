#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <map>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;
void solve(){
    string s;
    cin >> s;
    int n = (int)s.length();
    long long dp[2][n];
    dp[0][0] = (s[0] != '1');
    dp[1][0] = (s[0] != '0');
    //cout << dp[0][0] << " " << dp[1][0] << endl;
    long long sum = dp[0][0] + dp[1][0];
    for(int i = 1; i < n; i++){
        dp[0][i] = (dp[1][i - 1] + 1) * (s[i] != '1');
        dp[1][i] = (dp[0][i - 1] + 1) * (s[i] != '0');
        //cout << dp[0][i] << " " << dp[1][i] << endl;
        sum += dp[0][i] + dp[1][i];
    }
    long long cntr = 0;
    long long over = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '?') cntr++;
        else{
            over += cntr * (cntr + 1)/2;
            cntr = 0;
        }
    }
    over += cntr * (cntr + 1)/2;
    cout << sum - over << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
