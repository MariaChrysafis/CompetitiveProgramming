import java.lang.*;
import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;
import java.util.*;
 
import javafx.util.Pair;
 
import java.math.*;
import java.awt.Point;
 
public class Main {
    static FastScanner sc = new FastScanner();
 
    public static void main(String[] args) {
        int t = sc.ni();
        for (int i = 0; i < t; i++) {
            graph g = new graph();
            g.n = sc.ni();
            g.m = sc.ni();
            g.v1 = new int[g.n];
            g.v2 = new int[g.n];
            g.color = new int[g.n];
            g.adj = new ArrayList<>(g.n);
            for(int j = 0; j < g.n; j++){
                g.v1[j] = sc.ni();
                g.color[j] = -1;
                g.adj.add(new ArrayList<>());
                g.color[j] = -1;
                //System.out.println(g.v1[j] - g.v2[j]);
            }
            for(int j = 0; j < g.n; j++){
                g.v2[j] = sc.ni();
            }
            for(int j = 0; j < g.m; j++){
                int u = sc.ni();
                int v = sc.ni();
                g.adj.get(u - 1).add(v - 1);
                g.adj.get(v - 1).add(u - 1);
            }
            g.read();
        }
    }
}
class graph {
    public List<List<Integer>> adj = new ArrayList<List<Integer>>();
    public int color[];
    public int v1[];
    public int v2[];
    public int n;
    public int m;
 
    void dfs(int u, int cntr) {
        color[u] = cntr;
        for (int v : adj.get(u)) {
            if (color[v] == -1) {
                dfs(v, 1 - cntr);
            }
        }
    }
 
    void read() {
        int c1 = 0;
        int c2 = 0;
        for (int i = 0; i < n; i++) {
            c1 += Math.abs(v1[i]);
            c1 %= 2;
        }
        for (int i = 0; i < n; i++) {
            c2 += Math.abs(v2[i]);
            c2 %= 2;
        }
        if (c1 != c2) {
            System.out.println("NO");
            return;
        }
        dfs(0, 0);
        boolean bip = true;
        long cntr[] = new long[2];
        for (int i = 0; i < n; i++) {
            cntr[color[i]] = v2[i] - v1[i] + cntr[color[i]];
            //System.out.println(v1[i] - v2[i]);
            for (int j : adj.get(i)) {
                if (color[i] == color[j]) {
                    bip = false;
                }
            }
        }
        //System.out.println(cntr[0] + " " + cntr[1]);
        if (!bip || cntr[0] == cntr[1]) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }
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
