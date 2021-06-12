class Solution {
    int[][] row_sum, col_sum;
    int row_pref(int l, int r, int x){
        if(l == 0) return row_sum[x][r];
        return row_sum[x][r] - row_sum[x][l - 1];
    }
    int col_pref(int l, int r, int x){
        if(l == 0) return col_sum[x][r];
        return col_sum[x][r] - col_sum[x][l - 1];
    }
    public int largestMagicSquare(int[][] grid) {
        row_sum = new int[grid.length][grid[0].length];
        for(int i = 0; i < grid.length; i++){
            for(int j = 0; j < grid[0].length; j++){
                if(j != 0) row_sum[i][j] = row_sum[i][j - 1] + grid[i][j];
                else row_sum[i][j] = grid[i][j];
            }
        }
        col_sum = new int[grid[0].length][grid.length];
        for(int i = 0; i < grid[0].length; i++){
            for(int j = 0; j < grid.length; j++){
                if(j != 0) col_sum[i][j] = col_sum[i][j - 1] + grid[j][i];
                else col_sum[i][j] = grid[j][i];
            }
        }
        int myMax = 1;
        for(int rowL = 0; rowL < grid.length; rowL++){
            for(int rowR = rowL + 1; rowR < grid.length; rowR++){
                for(int colL = 0; colL < grid[0].length; colL++){
                    int colR = rowR - rowL + colL;
                    if(colR >= grid[0].length) break;
                    int des = col_pref(rowL, rowR, colL);
                    boolean fine = true;
                    for(int i = colL; i <= colR; i++){
                        if(col_pref(rowL, rowR, i) != des) fine = false;
                    }
                    if(!fine) continue;
                    for(int i = rowL; i <= rowR; i++){
                        if(row_pref(colL, colR, i) != des) fine = false;
                    }
                    if(!fine) continue;
                    //continue;
                    
                    int sum1 = 0;
                    for(int i = 0; i <= rowR - rowL; i++){
                        sum1 += grid[rowL + i][colL + i];
                    }
                    int sum2 = 0;
                    for(int i = 0; i <= rowR - rowL; i++){
                        sum2 += grid[rowR - i][colL + i];
                    }
                    if(sum1 == des && sum2 == sum1) myMax = Math.max(myMax, colR - colL + 1);
                    
                }
            }
        }
        return myMax;
    }
}
