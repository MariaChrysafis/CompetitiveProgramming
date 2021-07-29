#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
#include <iomanip>
 
#define ll long long
#define endl '\n'
 
using namespace std;
const int mod = 1e9 + 7;
void solve(){
    string str = "chokudai";
    string s;
    cin >> s;
    int n = s.length();
    vector<vector<ll>> dp(n);
    for(int i = 0; i < n; i++){
        dp[i].resize(str.length());
        for(int j = 0; j < str.length(); j++){
            dp[i][j] = 0;
        }
    }
    dp[0][0] = (s[0] == str[0]);
    for(int i = 1; i < n; i++){
        dp[i][0] = dp[i - 1][0] + (s[i] == str[0]);
    }
    for(int i = 1; i < n; i++){
        for(int j = 1; j < str.length(); j++){
            dp[i][j] = dp[i - 1][j - 1] * (str[j] == s[i]) + dp[i - 1][j];
            dp[i][j] %= mod;
        }
    }
    cout << dp[n - 1][str.length() - 1];
 
}
 
int main() {
    solve();
}
