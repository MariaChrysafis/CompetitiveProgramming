class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int myMax = 0;
        for(int i = 0; i < accounts.size(); i++){
            int ans = 0;
            for(int j: accounts[i]){
                ans += j;
            }
            myMax = max(myMax,ans);
        }
        return myMax;
    }
};
