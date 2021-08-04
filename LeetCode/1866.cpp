#define ll long long
class Solution {
public:
    const int MOD = 1e9 + 7;
    int rearrangeSticks(int n, int k) {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        long long dp[n][k + 1];
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= k; j++){
                if(i + 1 == j) {
                    dp[i][j] = 1;
                }
                else if(j == 0 || i == 0){
                    dp[i][j] = 0;    
                }
                else {
                    dp[i][j] = (dp[i - 1][j] * i + dp[i - 1][j - 1]) % MOD;
                }
            }
        }
        return dp[n - 1][k];
    }
};
