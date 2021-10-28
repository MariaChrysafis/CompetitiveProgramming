class Solution {
public:
    string s;
    string t;
    vector<vector<int>> dp;
    int memoize (int i, int j) {
        if (dp[i][j] != -1) {
            return dp[i][j];
        }
        if (i == 0 || j == 0) {
            return 0;
        }
        if (s[i - 1] == t[j - 1]) {
            return (dp[i][j] = memoize(i - 1, j - 1) + 1);  
        }
        return (dp[i][j] = max(memoize(i - 1, j), memoize(i, j - 1)));
    }
    int longestCommonSubsequence(string text1, string text2) {
        s = text1;
        t = text2;
        dp.resize(s.length() + 1);
        for (int i = 0; i < dp.size(); i++) {
            dp[i].resize(t.length() + 1);
            for (int j = 0; j < dp[i].size(); j++) {
                dp[i][j] = -1;
            }
        }
        return memoize(text1.length(), text2.length());
    }
};
