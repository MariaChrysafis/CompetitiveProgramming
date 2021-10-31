class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        vector<long long> dp(1001);
        for (int i = 0; i < dp.size(); i++) {
            dp[i] = (int)1e9;
        }
        set<long long> s;
        for (long long j: nums) {
            s.insert(j);
        }
        nums.clear();
        for (long long j: s) {
            nums.push_back(j);
        }
        dp[start] = 0;
        for (int i = 0; i < dp.size(); i++) {
            for (long long j: nums) {
                if (j < -1000 || j > 1000) {
                    continue;
                }
                for (long long k = 1; k < 1000; k++) {
                    if (i + j * k < dp.size() && i + j * k >= 0) dp[i + j * k] = min(dp[i] + k, dp[i + j * k]);
                    if (i + j * k >= dp.size() || i + j * k < 0) break;
                }
                for (int k = 1; k <= 1000; k++) {
                    if (i - j * k >= 0 && i - j * k <= 1000) dp[i - j * k] = min(dp[i] + k, dp[i - j * k]);
                    if (i - j * k < 0 || i - j * k > 1000) break;
                }
            }
        }
        for (int i = 0; i < dp.size(); i++) {
            for (long long j: nums) {
                if ((i ^ j) <= 1000 && (i ^ j) >= 0) dp[i ^ j] = min(dp[i] + 1, dp[i ^ j]);
            }
        }
        if (goal >= 0 && goal < dp.size()) {
            if (dp[goal] == (int)1e9) {
                return -1;
            }
            return dp[goal];
        }
        long long myMin = (int)1e9;
        for (int i = 0; i < dp.size(); i++) {
            for (int j: nums) {
                if (i + j == goal) {
                    myMin = min(myMin, dp[i] + 1);
                }
                if (i - j == goal) {
                    myMin = min(myMin, dp[i] + 1);
                }
                if ((i ^ j) == goal) {
                    myMin = min(myMin, dp[i] + 1);
                }
            }
        }
        if (myMin == (int)1e9) {
            return -1;
        }
        return myMin;
    }
};
