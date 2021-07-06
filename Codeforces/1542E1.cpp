#include <iostream>
long long MAX = 1251 * 2;
using namespace std;
int main(){
    int n;
    cin >> n;
    long long MOD;
    cin >> MOD;
    long long dp[n + 1][MAX + 1][3];
    //0 -> p = q
    //1 -> p < q
    //2 -> p > q
    for(int i = 0; i < n + 1; i++){
        for(int j = 0; j < MAX; j++){
            dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = 0;
        }
    }
    //return 0;
    dp[0][MAX/2][0] = 1;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < MAX; j++){
            for(int p = 0; p <= i; p++){
                for(int q = 0; q <= i; q++){
                    if(p == q){
                        for(int k = 0; k < 3; k++){
                            dp[i + 1][j][k] += dp[i][j][k];
                            if(dp[i + 1][j][k] >= MOD) dp[i + 1][j][k] -= MOD;
                        }
                    }else if(p < q){
                        if(j + (p - q) < 0 || j + (p - q) >= MAX) continue;
                        dp[i + 1][j + (p - q)][1] += (dp[i][j][0] + dp[i][j][1] + dp[i][j][2]);
                        while(dp[i + 1][j + (p - q)][1] >= MOD) dp[i + 1][j + (p - q)][1] -= MOD;
                    }else{
                        if(j + (p - q) < 0 || j + (p - q) >= MAX) continue;
                        dp[i + 1][j + (p - q)][2] += (dp[i][j][0] + dp[i][j][1] + dp[i][j][2]);
                        while(dp[i + 1][j + (p - q)][2] >= MOD) dp[i + 1][j + (p - q)][2] -= MOD;
                    }
                }
            }
        }
    }
    long long ans = 0;
    for(int i = MAX/2 + 1; i < MAX; i++){
        ans += dp[n][i][1];
        if(ans >= MOD) ans -= MOD;
    }
    cout << ans << endl;
}
