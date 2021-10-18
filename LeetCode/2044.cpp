class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int myMax = 0;
        int oc = 0;
        for (int i = 0; i < (1 << nums.size()); i++) {
            int bitwiseOr = 0;
            for (int j = 0; j < nums.size(); j++) {
                if ((1 << j) & i) {
                    bitwiseOr = bitwiseOr | nums[j];
                }
            }
            //cout << bitwiseOr << endl;
            if (bitwiseOr == myMax) {
                 oc++;
            } else if (bitwiseOr > myMax) {
                oc = 1;
                myMax = bitwiseOr;
            }
        }
        return oc;
    }
};
