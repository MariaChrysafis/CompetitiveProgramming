class Solution {
public:
    vector<int> canSeePersonsCount(vector<int> &heights) {
        reverse(heights.begin(), heights.end());
        stack<int> v;
        v.push(heights[0]);
        vector<int> ans = {0};
        for(int i = 1; i < heights.size(); i++){
            int cntr = 0;
            while(!v.empty() && v.top() < heights[i]) {
                v.pop();
                cntr++;
            }
            ans.push_back(cntr + !v.empty());
            v.push(heights[i]);
        }
        reverse(ans.begin(), ans.end());
        return ans;

    }
};
