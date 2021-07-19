class Solution {
public:
    int addRungs(vector<int>& rungs, int dist) {
        vector<int> delta;
        delta.push_back(rungs[0]);
        for(int i = 0; i < rungs.size() - 1; i++){
            delta.push_back(rungs[i + 1] - rungs[i]);
        }
        int ans = 0;
        for(int x: delta){
            //cout << x << " ";
            ans += (x - 1)/dist;
        }
        //cout << endl;
        return ans;
    }
};
