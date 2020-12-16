class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        set<int> prev;
        for(int i = 0; i < nums.size(); i++){
            if(prev.count(target - nums[i])){
                for(int j = 0; j < nums.size(); j++){
                    if(nums[j] == target - nums[i]){
                        return {i,j};
                    }
                }
            }
            prev.insert(nums[i]);
        }
        return {0,0};
    }
};
