class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        vector<int> cur;
        for(int i = 0; i < dist.size(); i++){
            cur.push_back(dist[i]/speed[i] + (dist[i] % speed[i] != 0));
        }
        sort(cur.begin(), cur.end());
        int time = 1;
        for(int i = 0; i < cur.size(); i++){
            if(time > cur[i]){
                return i;
            }
            time++;
        }
        return dist.size();
    }
};
