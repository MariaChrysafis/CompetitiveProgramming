class Solution {
public:
    const int INF = 1000000;
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int pref[101][nums.size() + 1];
        int cnt[101];
        for(int i = 0; i < 101; i++){
            cnt[i] = 0;
            for(int j = 0; j <= nums.size(); j++){
                pref[i][j] = 0;
            }
        }
        for(int i = 0; i < nums.size(); i++){
            cnt[nums[i]]++;
            for(int j = 0; j <= 100; j++){
                pref[j][i + 1] = cnt[j];
            }
        }
        vector<int> ans;
        for(int i = 0; i < queries.size(); i++){
            int l = queries[i][0];
            int r = queries[i][1];
            for(int j = 0; j < 101; j++){
                cnt[j] = pref[j][r + 1] - pref[j][l];
            }
            int prev = -INF;
            int myMin = INF;
            for(int j = 0; j < 101; j++){
                if(cnt[j] != 0){
                    if(prev != -INF) myMin = min(myMin, abs(j - prev));
                    prev = j;
                }
            }
            if(myMin == INF) myMin = -1;
            ans.push_back(myMin);
        }
        return ans;
    }
};
