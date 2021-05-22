#include <iostream>
using namespace std;
const int MOD = 1e9 + 7;
int main(){
    int n;
    cin >> n;
    long long dp[n + 1];
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        dp[i] = 0;
        for(int j = 1; j <= min(i, 6); j++){
            dp[i] += dp[i - j];
            if(dp[i] > MOD) dp[i] %= MOD;
        }
    }
    cout << dp[n] << endl;
}
