class Solution {
public:
    vector<vector<int>> inv_adj;
    vector<int> dp;
    vector<int> cost;
    int memoize (int cur) {
        if (dp[cur] != -1) {
            return dp[cur];
        }
        int myMax = 0;
        for (int i: inv_adj[cur]) {
            myMax = max(memoize(i), myMax);
        }
        return (dp[cur] = myMax + cost[cur]);
    }
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        inv_adj.resize(n);
        dp.resize(n);
        cost = time;
        for (auto vec: relations) {
            inv_adj[vec[1] - 1].push_back(vec[0] - 1);
        }
        for (int i = 0; i < n; i++) {
            dp[i] = -1;
        }
        int myMax = 0;
        for (int i = 0; i < n; i++) {
            myMax = max(memoize(i), myMax);
        }
        return myMax;
    }
};
