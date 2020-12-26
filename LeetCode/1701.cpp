class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        vector<pair<double,double>> v;
        for(int i = 0; i < customers.size(); i++){
            int a = customers[i][0];
            int b = customers[i][1];
            v.push_back({a,b});
        }
        double curTime = v[0].first;
        double waitTime = 0;
        for(int i = 0; i < customers.size(); i++){
            if(curTime < v[i].first){
                curTime = v[i].first;
            }
            curTime += v[i].second;
            waitTime += curTime - v[i].first;
            //cout << curTime - v[i].first << endl;
        }
        double d = v.size();
        return waitTime/d;
    }
};
