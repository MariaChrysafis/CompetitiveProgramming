class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        vector<int> ans;
        int n = nums.size();
        for(int i = 0; i < nums.size(); i++){
            while(!ans.empty() && nums[i] < ans[ans.size() - 1] && ans.size() + n - i - 1 >= k){
                ans.pop_back();
            }
            ans.push_back(nums[i]);
        }
        while(ans.size() > k){ans.pop_back();}
        return ans;
        
    }
};
