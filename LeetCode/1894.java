class Solution {
    long[] chalkCopy;
    public int chalkReplacer(int[] chalk, int k) {
        chalkCopy = new long[chalk.length];
        long kCopy = k;
        for(int i = 0; i < chalk.length; i++){
            chalkCopy[i] = chalk[i];
        }
        long sum = 0;
        for(int i = 0; i < chalk.length; i++){
            sum += chalk[i];
        }
        kCopy %= sum;
        for(int i = 0; i < chalk.length; i++){
            if(kCopy - chalk[i] >= 0){
                kCopy -= chalk[i];
            }else{
                return i;
            }
        }
        return 3;
    }
}
