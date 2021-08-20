import java.lang.*;
import java.io.*;
import java.util.*;
 
public class Main {
    static FastScanner sc = new FastScanner();
    static long distance(Point c1, Point c2){
        return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
    }
    public static int MOD = (int)1e9 + 7;
    public static void main(String[] args) {
        int n = sc.ni();
        int k = sc.ni();
        int q = sc.ni();
        long [][]dp = new long[k + 1][n];
        for(int i = 0; i <= k; i++){
            for(int j = 0; j < n; j++){
                dp[i][j] = 0;
                if(i == 0) {
                    dp[i][j] = 1;
                    continue;
                }
                if(j - 1 >= 0) dp[i][j] += dp[i - 1][j - 1];
                if(j + 1 < n) dp[i][j] += dp[i - 1][j + 1];
                while(dp[i][j] > MOD) dp[i][j] -= MOD;
            }
        }
        long []arr = new long[n];
        for(int i = 0; i < n; i++){
            arr[i] = sc.ni();
        }
        long []weight = new long[n];
        long ans = 0;
        for(int i = 0; i < n; i++){
            weight[i] = 0;
            for(int j = 0; j <= k; j++){
                weight[i] += (dp[j][i] * dp[k - j][i]) % MOD;
                if(weight[i] > MOD) weight[i]-= MOD;
            }
            ans += (weight[i] * arr[i]) % MOD;
            ans %= MOD;
        }
        for(int dum = 0; dum < q; dum++){
            int i = sc.ni() - 1;
            long x = sc.ni();
            x %= MOD;
            ans += ((x - arr[i] + MOD) % MOD * weight[i]) % MOD;
            if(ans > MOD) ans -= MOD;
            arr[i] = x;
            System.out.println(ans);
        }
    }
}
 
class Point{
    public long x;
    public long y;
    public Point(long a, long b) {
        this.x = a;
        this.y = b;
    }
}
 
 
class FastScanner {
    BufferedReader br;
    StringTokenizer st;
 
    public FastScanner() {
        br = new BufferedReader(new InputStreamReader(System.in), 32768);
        st = null;
    }
 
    String next() {
        while (st == null || !st.hasMoreElements()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return st.nextToken();
    }
 
    int ni() {
        return Integer.parseInt(next());
    }
 
    long nl() {
        return Long.parseLong(next());
    }
}
