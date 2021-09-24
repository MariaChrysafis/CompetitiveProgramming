class Solution {
    public static int[][] water;
    public static Boolean[][] hasVisited;
    public static Boolean[][] myGrid;
    public static int n, m;
    public static void dfs(int x, int y) {
        //System.out.println(x + " " + y);
        if(x >= n || y >= m || x < 0 || y < 0 || myGrid[x][y] == true || hasVisited[x][y] == true) {
            return;
        }
        hasVisited[x][y] = true;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if(Math.abs(i) != Math.abs(j)) {
                    dfs(x + i, y + j);
                }
            }
        }
    }
    public static Boolean isConnected(int x) {
        hasVisited = new Boolean[n][m];
        myGrid = new Boolean[n][m];
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                myGrid[i][j] = false;
                hasVisited[i][j] = false;
            }
        }
        for (int i = 0; i < x; i++) {
            myGrid[water[i][0] - 1][water[i][1] - 1] = true;
        }
        for(int i = 0; i < m; i++) {
            dfs(0, i);
        }
        Boolean valid = false;
        for(int i = 0; i < m; i++) {
            if(hasVisited[n - 1][i]) {
                valid = true;
            }
        }
        return valid;
    }
    
    public static int binSearch(int l, int r) {
        int m = (l + r)/2;
        if(l == r) {
            return l;
        }
        if(isConnected(m)) {
            return binSearch(m + 1, r);
        } else {
            return binSearch(l, m);
        }
    }
    
    public int latestDayToCross(int row, int col, int[][] cells) {
        water = new int[cells.length][2];
        water = cells;
        n = row;
        m = col;
        return binSearch(0, cells.length) - 1;
    }
}
