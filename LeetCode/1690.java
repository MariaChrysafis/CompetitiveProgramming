class Solution {
    int INF = 1000000000;
    int[] vec;
    int[] pref;
    int[][]dp;
    int Pref(int x){
        if(x == -1) return 0;
        return pref[x];
    }
    int sum(int l, int r){
        return Pref(r) - Pref(l - 1);
    }
    int ans(int l, int r){
        if(l == r) return 0;
        if(dp[l][r] != INF) return dp[l][r];
        int sl = sum(l + 1, r);
        int sr = sum(l, r - 1);
        int x = Math.max(sl - ans(l + 1, r), sr - ans(l, r - 1));
        dp[l][r] = x;
        return dp[l][r];
    }
    public int stoneGameVII(int[] stones) {
        pref = new int[stones.length]; 
        vec = new int[stones.length]; 
        dp = new int[stones.length][stones.length];
        for(int i = 0; i < stones.length; i++){
            vec[i] = stones[i];
            for(int j = 0; j < stones.length; j++){
                dp[i][j] = INF;
            }
        }
        pref[0] = vec[0];
        for(int i = 1; i < pref.length; i++){
            pref[i] = pref[i - 1] + vec[i];
        }
        return ans(0, stones.length - 1);
    }
}
