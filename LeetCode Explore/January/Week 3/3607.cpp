class Solution {
public:
    int dp[60][60];
    int calc(int k, int n){
        if(n == 0){
            dp[k][n] = 1;
            return 1;
        }
        if(k == 0){
            dp[k][n] = 0;
            return 0;
        }
        if(dp[k][n] != -1){
            return dp[k][n];
        }
        dp[k][n] = calc(k - 1, n - 1) + calc(k - 1, n);
        return dp[k][n];
    }
    int countVowelStrings(int n) {
        for(int i = 0; i < 60; i++){
            for(int j = 0; j < 60; j++){
                dp[i][j] = -1;
            }
        }
        return calc(n + 4,4);
    }
};
