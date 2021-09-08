import java.lang.*;
import java.io.*;
import java.util.*;
 
public class Main {
    static class FS {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer("");
        String next() {
            while(!st.hasMoreElements()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch(Exception e) {}
            }
            return st.nextToken();
        }
        int nextInt() {
            return Integer.parseInt(next());
        }
        long nextLong() {
            return Long.parseLong(next());
        }
    }
 
    OutputStream outputStream = System.out;
    static final FS sc = new FS();
    static final PrintWriter pw = new PrintWriter(System.out);
    static long compute(long [][]arr, long startingPoint){
        if(arr[0][0] < startingPoint){
            return Long.MAX_VALUE;
        }
        long [][]dp = new long[arr.length][arr[0].length];
        for(int i = 0; i < arr.length; i++){
            for(int j = 0; j < arr[i].length; j++){
                dp[i][j] = Long.MAX_VALUE;
            }
        }
        dp[0][0] = (arr[0][0] - startingPoint);
        for(int i = 0; i < arr.length; i++){
            for(int j = 0; j < arr[i].length; j++){
                if(i == 0 && j == 0) {
                    //System.out.print(dp[0][0] + " ");
                    continue;
                }
                long curVal = i + j + startingPoint;
                long down = Long.MAX_VALUE;
                if(i != 0 && arr[i][j] >= curVal && dp[i - 1][j] != Long.MAX_VALUE){
                    down = dp[i - 1][j] + (arr[i][j] - curVal);
                }
                long up = Long.MAX_VALUE;
                if(j != 0 && arr[i][j] >= curVal && dp[i][j - 1] != Long.MAX_VALUE){
                    up = dp[i][j - 1] + (arr[i][j] - curVal);
                }
                dp[i][j] = Math.min(up, down);
                //System.out.print("(" + dp[i][j] + ", " + down + ", " + up + ") | ");
            }
            //System.out.println();
        }
        return dp[dp.length - 1][dp[0].length - 1];
    }
 
    static void solve(long [][]arr, ArrayList<Long> vec){
        long myMin = Long.MAX_VALUE;
        for(long x: vec){
            myMin = Math.min(myMin, compute(arr, x));
        }
        System.out.println(myMin);
    }
 
    public static void main(String[] args) {
        int t = sc.nextInt();
        for(int tc = 0; tc < t; tc++){
            int n = sc.nextInt();
            int m = sc.nextInt();
            long [][]arr = new long[n][m];
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    arr[i][j] = sc.nextLong();
                }
            }
            Set<Long> mySet = new HashSet<>();
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    mySet.add(arr[i][j] - i - j);
                }
            }
            ArrayList<Long> vec = new ArrayList<>();
            vec.addAll(mySet);
            solve(arr, vec);
        }
    }
}
