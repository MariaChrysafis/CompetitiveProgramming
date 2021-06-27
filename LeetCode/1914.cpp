class Solution {
public:
    int n, m;
    vector<int> shift(vector<int> v){
        vector<int> vec;
        for(int i = 1; i < v.size(); i++){
            vec.push_back(v[i]);
        }
        vec.push_back(v[0]);
        return vec;
    }
    vector<pair<int,int>> multishift(vector<pair<int,int>> v, int k){
        k %= v.size();
        vector<pair<int,int>> vec;
        for(int i = k; i < v.size(); i++){
            vec.push_back(v[i]);
        }
        for(int i = 0; i < k; i++){
            vec.push_back(v[i]);
        }
        return vec;
    }
    pair<int,int> plus(pair<int,int> p1, pair<int,int> p2){
        return {p1.first + p2.first, p1.second + p2.second};
    }
    bool inBounds(pair<int,int> p){
        return (p.first >= 0 && p.second >= 0 && p.first < n && p.second < m);
    }
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        vector<vector<int>> ans = grid;
        n = grid.size();
        m = grid[0].size();
        int ind = 0;
        vector<pair<int,int>> dir;
        dir.push_back(make_pair(1, 0));
        dir.push_back(make_pair(0, 1));
        dir.push_back(make_pair(-1, 0));
        dir.push_back(make_pair(0, -1));
        bool hasVisited[n][m];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                hasVisited[i][j] = false;
            }
        }
        for(int i = 0; i < min(n, m)/2; i++){
            vector<pair<int,int>> vec;
            pair<int,int> cur = make_pair(i, i);
            vec.push_back(cur);
            int ind = 0;
            while(ind < dir.size()){
                hasVisited[cur.first][cur.second] = true;
                pair<int,int> p = plus(cur, dir[ind]);
                if(!inBounds(p) || hasVisited[p.first][p.second]){
                    ind++;
                }else{
                    cur = p;
                    vec.push_back(cur);
                }
            }
            vector<pair<int,int>> upd = multishift(vec, k);
            for(int i = 0; i < upd.size(); i++){
                ans[upd[i].first][upd[i].second] = grid[vec[i].first][vec[i].second];
            }
        }
        return ans;
    }
};
