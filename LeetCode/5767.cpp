class Solution {
public:
    bool isCovered(vector<vector<int>>& ranges, int left, int right) {
        for(int i = left; i <= right; i++){
            bool fine = false;
            for(int j = 0; j < ranges.size(); j++){
                int x = ranges[j][0];
                int y = ranges[j][1];
                if(i >= x && i <= y){
                    fine = true;
                }
            }
            if(!fine){
                //cout << i << endl;
                return false;
            }
        }
        return true;
    }
};
