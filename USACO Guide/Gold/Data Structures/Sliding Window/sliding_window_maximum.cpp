#pragma GCC optimize("O2")

class Solution {
public:
    vector<int> v;
     vector<vector<int>> sparseTable;
    int query (int l, int r) {
        //cout << l << " " << r << endl;
        if(l > r) {
            return -1e6;
        }
        if(pow(2, (int)log2(r - l + 1)) == r - l + 1) {
            return sparseTable[l][(int)log2(r - l + 1)];
        }
        int x = floor(log2(r - l));
        //cout << x << endl;
        //cout << l + (1 << x) + 1 << endl;
        return max(sparseTable[l][x], query(l + (1 << x), r)); 
    }
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        v = nums;
        sparseTable.resize(nums.size());
        vector<int> sufMax(nums.size());
        for(int i = 0; i < sparseTable.size(); i++) {
            sparseTable[i].resize(25);
        }
        sufMax[nums.size() - 1] = nums[nums.size() - 1];
        for(int i = nums.size() - 2; i >= 0; i--) {
            sufMax[i] = max(sufMax[i + 1], nums[i]);
        }
        for (int i = nums.size() - 1; i >= 0; i--) {
            for (int j = 0; j < 25; j++) {
                if(i + (1 << j) - 1 >= nums.size()) {
                    sparseTable[i][j] = sufMax[i];
                } else {
                    if (j == 0) sparseTable[i][j] = nums[i];
                    else sparseTable[i][j] = max(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
        // cout << query(0, 1) << endl;
        //cout << query(2, 4) << endl;
        //return {};
        vector<int> ans;
        for(int i = 0; i <= v.size() - k; i++ ) {
            ans.push_back(query(i, i + k - 1));
        }
        return ans;
        //return {query(1, 4)};
        return {};
    }
};
