class Solution {
    public int minTotalDistance(int[][] grid) {
        ArrayList<Integer> x = new ArrayList<Integer>();
        ArrayList<Integer> y = new ArrayList<Integer>();
        int cntr = 0;
        for(int i = 0; i < grid.length; i++){
            for(int j = 0; j < grid[i].length; j++){
                if(grid[i][j] == 1){
                    x.add(i);
                    y.add(j);
                    cntr++;
                }
            }
        }
        Collections.sort(x);
        Collections.sort(y);
        int desX = x.get(cntr/2);
        int desY = y.get(cntr/2);
        int ans = 0;
        for(int i = 0; i < grid.length; i++){
            for(int j = 0; j < grid[i].length; j++){
                if(grid[i][j] == 0) continue;
                ans += Math.abs(i - desX) + Math.abs(j - desY);
            }
        }
        return ans;
    }
}
