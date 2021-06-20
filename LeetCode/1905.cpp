#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
class Solution {
public:
    vector<vector<int>> g1, g2;
    void dfs(int i, int j){
        if(i < 0 || i >= g1.size() || j < 0 || j >= g1[0].size() || g2[i][j] == 0){
            return;
        }
        g2[i][j] = 0;
        dfs(i + 1, j);
        dfs(i - 1, j);
        dfs(i, j + 1);
        dfs(i, j - 1);
    }
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        g1 = grid1, g2 = grid2;
        for(int i = 0; i < g1.size(); i++){
            for(int j = 0; j < g1[0].size(); j++){
                if(grid2[i][j] == 1 && grid1[i][j] == 0){
                    dfs(i, j);
                }
            }
        }
        int c = 0;
        for(int i = 0; i < g1.size(); i++){
            for(int j = 0; j < g1[0].size(); j++){
                if(g2[i][j] == 1){
                    dfs(i, j);
                    c++;
                }
            }
        }
        return c;
    }
};
