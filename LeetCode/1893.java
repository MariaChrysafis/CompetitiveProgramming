class Solution {
    public boolean isCovered(int[][] ranges, int left, int right) {
        for(int i = left; i <= right; i++){
            boolean fine = false;
            for(int j = 0; j < ranges.length; j++){
                if(i >= ranges[j][0] && i <= ranges[j][1]){
                    fine = true;
                }
            }
            if(!fine) return false;
        }
        return true;
    }
}
