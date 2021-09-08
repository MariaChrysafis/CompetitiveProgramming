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
    public static void solve(long n, long m, long a, long b){
        if(n * a != m * b){
            pw.println("NO");
            return;
        }
        pw.println("YES");
        int [][]arr = new int[(int)n][(int)m];
        int start = 0;
        for(int i = 0; i < n; i++){
            int cntr = 0;
            while(cntr < a){
                arr[i][start] = 1;
                cntr++;
                start++;
                start %= m;
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                pw.print(arr[i][j]);
            }
            pw.println();
        }
    }
    public static void main(String[] args) {
        int t = sc.nextInt();
        for(int tc = 0; tc < t; tc++){
            long n, m, a, b;
            n = sc.nextInt();
            m = sc.nextInt();
            a = sc.nextInt();
            b = sc.nextInt();
            solve(n, m, a, b);
        }
        pw.close();
    }
}
