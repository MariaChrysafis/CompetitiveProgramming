class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        pair<int,int> start = {startPos[0], startPos[1]};
        pair<int,int> home = {homePos[0], homePos[1]};
        int ans = 0;
        for (int i = min(start.first, home.first); i <= max(start.first,home.first); i++) {
            ans += rowCosts[i];
        }
        for (int i = min(start.second, home.second); i <= max(home.second,start.second); i++) {
            ans += colCosts[i];
        }
        ans -= rowCosts[start.first];
        ans -= colCosts[start.second];
        return ans;
    }
};
