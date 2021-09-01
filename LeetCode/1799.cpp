class Solution {
public:
    int gcd(int a, int b){
        if(min(a,b) == 0) return max(a,b);
        return gcd(max(a,b) % min(a,b), min(a,b));
    }
    int maxScore(vector<int>& nums) {
        vector<int> dp((1 << nums.size()));
        dp[0] = 0;
        for(int i = 2; i < (1 << nums.size()); i++){
            vector<int> pos;
            for(int j = 0; j < nums.size(); j++){
                if(i & (1 << j)){
                    pos.push_back(j);
                }
            }
            if(pos.size() % 2 == 1) continue;
            int cost = 0;
            for(int j = 0; j < pos.size(); j++){
                for(int k = 0; k < pos.size(); k++){
                    if(j == k) continue;
                    int x = dp[i - (1 << pos[j]) - (1 << pos[k])] + gcd(nums[pos[j]], nums[pos[k]]) * pos.size()/2;
                    dp[i] = max(dp[i], x);
                }
            }
        }
        return dp[(1 << nums.size()) - 1];
    }
};
