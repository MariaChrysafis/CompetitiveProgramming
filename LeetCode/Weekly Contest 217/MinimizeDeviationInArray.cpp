class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        set <int> s;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] % 2 == 1){
                nums[i] *= 2;
            }
            s.insert(nums[i]);
        }
        int dif = *s.rbegin() - *s.begin();
        while(*s.rbegin() % 2 == 0){
            int x = *s.rbegin();
            s.erase(*s.rbegin());
            s.insert(x/2);
            dif = min(*s.rbegin() - *s.begin(),dif);
        }
        return dif;
    }
};
