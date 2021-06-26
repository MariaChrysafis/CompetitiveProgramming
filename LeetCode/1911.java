class Solution {
    public long LIS(int[] arr){
        long dp[][] = new long[2][arr.length];
        //int dp[1][arr.length];
        for(int i = 0; i < arr.length; i++){
            dp[1][i] = Math.max(0, arr[0]);
            dp[0][i] = 0;
        }
        long myMax = 0;
        for(int i = 1; i < arr.length; i++){
            dp[0][i] = Math.max(dp[0][i - 1], -arr[i] + dp[1][i - 1]);
            dp[1][i] = Math.max(dp[1][i - 1], arr[i] + dp[0][i - 1]);
            myMax = Math.max(dp[0][i], myMax);
            myMax = Math.max(dp[1][i], myMax);
        }
        return myMax;
    }
    public long maxAlternatingSum(int[] nums) {
        return LIS(nums);
    }
}
