class Solution {
    void print(int[][] arr){
        for(int i = 0; i < arr.length; i++){
            for(int j = 0; j < arr.length; j++){
                System.out.print(arr[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println();
    }
    int[][] transpose(int[][] arr, int x){
        if(x == 0){
            return arr;
        }
        int[][] new_arr = new int[arr.length][arr.length];
        for(int i = 0; i < arr.length; i++){
            for(int j = 0; j < arr.length; j++){
                new_arr[i][j] = arr[j][i];
            }
        }
        return transpose(new_arr, x - 1);
    }
    int[][] construct_left(int[][] arr){
        int[][] left = new int[arr.length][arr.length];
        for(int i = 0; i < arr.length; i++){
            for(int j = 0; j < arr.length; j++){
                if(arr[i][j] == 0){
                    left[i][j] = 0;
                    continue;
                }
                if(j == 0){
                    left[i][j] = 1;
                    continue;
                }
                left[i][j] = left[i][j - 1] + 1;
            }
        }
        return left;
    }
    int[][] construct_right(int[][] arr){
        int[][] right = new int[arr.length][arr.length];
        for(int i = 0; i < arr.length; i++){
            for(int j = arr.length - 1; j >= 0; j--){
                if(arr[i][j] == 0){
                    right[i][j] = 0;
                    continue;
                }
                if(j == arr.length - 1){
                    right[i][j] = 1;
                    continue;
                }
                right[i][j] = right[i][j + 1] + 1;
            }
        }
        return right;
    }
    int min4(int x, int y, int z, int w){
        return Math.min(Math.min(x, y), Math.min(z, w));
    }
    public int orderOfLargestPlusSign(int n, int[][] mines) {
        int [][]arr = new int[n][n];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                arr[i][j] = 1;
            }
        }
        for(int i = 0; i < mines.length; i++){
            arr[mines[i][0]][mines[i][1]] = 0;
        }
        int[][] left = construct_left(arr);
        int[][] right = construct_right(arr);
        int[][] down = transpose(construct_right(transpose(arr, 1)), 3);
        int[][] up = transpose(construct_left(transpose(arr, 3)), 1);
        //print(down);
        //print(up);
        int myMax = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                myMax = Math.max(myMax, min4(up[i][j], down[i][j], left[i][j], right[i][j]));
            }
        }
        return myMax;
    }
}
