import java.lang.*;
import java.io.*;
import java.util.*;
 
public class Main {
    static FastScanner sc = new FastScanner();
    static long distance(Point c1, Point c2){
        return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
    }
    public static void main(String[] args) {
        int n = sc.ni();
        Point[] arr = new Point[n];
        for(int i = 0; i < n; i++){
            arr[i] = new Point(sc.ni(), sc.ni());
        }
        boolean[] hasVisited = new boolean[n];
        for(int i = 1; i < n; i++){
            hasVisited[i] = false;
        }
        hasVisited[0] = true;
        Point cur = arr[0];
        System.out.print("1 ");
        for(int dum = 0; dum < n - 1; dum++){
            long myMax = 0;
            int ans = 0;
            for(int i = 0; i < n; i++){
                if(!hasVisited[i]) {
                    long dist = distance(cur, arr[i]);
                    if (dist > myMax) {
                        myMax = dist;
                        ans = i;
                    }
                }
            }
            cur = arr[ans];
            hasVisited[ans] = true;
            System.out.print(ans + 1 + " ");
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
