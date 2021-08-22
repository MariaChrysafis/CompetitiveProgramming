class Solution {
public:
    vector<int> inp;
    void print(vector<int> v){
        for(int i: v) cout << i << " ";
        cout << endl;
    }
    bool contains(int x, vector<int> v){
        for(int i: v) if (i == x) return true;
        return false;
    }
    vector<int> rec(vector<int> sums){
        //print(sums);
        if(sums.size() == 2){
            if(sums[0] != 0) return {sums[0]};
            if(sums[1] != 0) return {sums[1]};
            return {0};
        }
        vector<int> pos;
        pos.push_back(sums[0] - sums[1]); //either we have a positive
        pos.push_back(sums[1] - sums[0]);  //or we have a negative
        if(sums[0] == sums[1]){
            vector<int> v = {};
            for(int i = 0; i < sums.size(); i += 2){
                v.push_back(sums[i]);
            }
            vector<int> vec = rec(v);
            vec.push_back(0);
            return vec;
        }
        for(int x: pos){
            bool valid = true;
            int color[sums.size()];
            map<int,vector<int>> myMap;
            for(int i = sums.size() - 1; i >= 0; i--) myMap[sums[i]].push_back(i);
            for(int i = 0; i < sums.size(); i++) color[i] = -1;
            for(int i = 0; i < sums.size(); i++) {
                if(color[i] != -1) continue;
                int nxt = sums[i] + x;
                if(x > 0) nxt = sums[i] - x;
                if(myMap[nxt].size() == 0) { 
                    valid = false; 
                    break; 
                }
                color[i] = 0;
                color[myMap[nxt].back()] = 1;
                myMap[sums[i]].pop_back();
                myMap[nxt].pop_back();
            }
            if(!valid) continue;
            vector<int> v;
            for(int i = 0; i < sums.size(); i++){
                if(color[i] == 0 && x < 0) v.push_back(sums[i]);
                else if(color[i] == 1 && x > 0) v.push_back(sums[i]);
            }
            if(!contains(0, v)) continue;
            vector<int> vec = rec(v);
            vec.push_back(x);
            return vec;
        }
        return {};
    }
    vector<int> recoverArray(int n, vector<int>& sums) {
        sort(sums.begin(), sums.end());
        reverse(sums.begin(), sums.end()); //decreasing
        inp = sums;
        return rec(sums);
    }
};
