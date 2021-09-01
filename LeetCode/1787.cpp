class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int oc[k][1024];
        for(int i = 0; i < k; i++){
            for(int j = 0; j < 1024; j++){
                oc[i][j] = 0;
            }
        }
        for(int i = 0; i < nums.size(); i++){
            oc[i % k][nums[i]]++;
        }
        int dp[k][1024];
        for(int i = 0; i < k; i++){
            for(int j = 0; j < 1024; j++){
                dp[i][j] = 0;
            }
        }
        int bestAnswer[k];
        for(int i = 0; i < k; i++){
            bestAnswer[i] = 0;
        }
        for(int i = 0; i < 1024; i++){
            dp[0][i] = oc[0][i];
            bestAnswer[0] = max(bestAnswer[0], dp[0][i]);
        }
        //cout << dp[0][1] << endl;
    
        for(int i = 1; i < k; i++){
            for(int j = 0; j < 1024; j++){
                dp[i][j] = bestAnswer[i - 1];
            }
            for(int j = 0; j < 1024; j++){
                if(oc[i][j] == 0) continue;
                for(int l = 0; l < 1024; l++){
                    dp[i][j ^ l] = max(dp[i][j ^ l], dp[i - 1][l] + oc[i][j]);
                    bestAnswer[i] = max(bestAnswer[i], dp[i][j ^ l]);
                }
            }
        }
        //cout << dp[1][3] << endl;
        return nums.size() - dp[k - 1][0];
    }
};
