class Solution {
public:
    vector<vector<int>> row_sum;
    vector<vector<int>> col_sum;
    int col_pref(int l, int r, int x){
        if(l == 0) return col_sum[x][r];
        return col_sum[x][r] - col_sum[x][l - 1];
    }
    int row_pref(int l, int r, int x){
        if(l == 0) return row_sum[x][r];
        return row_sum[x][r] - row_sum[x][l - 1];        
    }
    int largestMagicSquare(vector<vector<int>>& grid) {
        row_sum.resize(grid.size());
        for(int i = 0; i < row_sum.size(); i++){
            row_sum[i].resize(grid[0].size());
            for(int j = 0; j < row_sum[0].size(); j++){
                if(j != 0) row_sum[i][j] = row_sum[i][j - 1] + grid[i][j];
                else row_sum[i][j] = grid[i][j];
            }
        }
        //return 3;
        col_sum.resize(grid[0].size());
        for(int i = 0; i < grid[0].size(); i++){
            col_sum[i].resize(grid.size());
            for(int j = 0; j < grid.size(); j++){
                if(j != 0) col_sum[i][j] = col_sum[i][j - 1] + grid[j][i];
                else col_sum[i][j] = grid[j][i];
            }
        }
        //cout << grid[0].size() << endl;
        // return 3;
        int myMax = 1;
        for(int rowL = 0; rowL < grid.size(); rowL++){
            for(int rowR = rowL + 1; rowR < grid.size(); rowR++){
                for(int colL = 0; colL < grid[0].size(); colL++){
                    int colR = (rowR - rowL) + colL;
                    if(colR >= grid[0].size()) continue;
                    //(rowL, rowR) -> (colL, colR)
                    bool fine = true;
                    int set = col_pref(rowL, rowR, colL);
                    for(int i = colL; i <= colR; i++){
                        if(col_pref(rowL, rowR, i) != set || !fine){
                            fine = false;
                            break;
                        }
                    }
                    if(!fine) continue;
                    for(int i = rowL; i <= rowR; i++){
                        if(row_pref(colL, colR, i) != set || !fine){
                            fine = false;
                            break;
                        }
                    }
                    if(!fine) continue;
                    int x = 0;
                    for(int i = 0; i <= rowR - rowL; i++) x += grid[rowL + i][colL + i];
                    if(x != set) continue;
                    int y = 0;
                    for(int i = 0; i <= rowR - rowL; i++) y += grid[rowR - i][colL + i];
                    if(y != set) continue;
                    if(fine){
                        myMax = max(colR - colL + 1, myMax);
                    }
                }
            }
        }
        return myMax;
    }
};
