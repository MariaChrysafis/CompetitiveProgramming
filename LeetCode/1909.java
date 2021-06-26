class Solution {
    public int LIS(int[] arr){
        int lis[] = new int[arr.length];
        lis[0] = 1;
        for(int i = 1; i < arr.length; i++){
            lis[i] = 1;
            for(int j = 0; j < i; j++){
                if(arr[j] < arr[i]){
                    lis[i] = Math.max(lis[j] + 1, lis[i]);
                }
            }
        }
        int myMax = 1;
        for(int i = 0; i < arr.length; i++){
            myMax = Math.max(myMax, lis[i]);
        }
        return myMax;
    }
    public boolean canBeIncreasing(int[] nums) {
        System.out.print(LIS(nums));
        return (LIS(nums) >= nums.length -1);
    }
}
