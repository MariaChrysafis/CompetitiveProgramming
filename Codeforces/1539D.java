import java.lang.*;
import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;
import java.util.*;
 
import javafx.util.Pair;
 
import java.math.*;
import java.awt.Point;
 
public class Main {
    static int MAX = 5;
    static FastScanner sc = new FastScanner();
 
    static class pair implements Comparable<pair> {
        long first;
        long second;
 
        public pair(long a, long b) {
            this.first = a;
            this.second = b;
        }
 
        public int compareTo(pair o) {
            return Long.compare(this.second, o.second);
        }
    }
 
    public static void main(String[] args) {
        int n;
        n = sc.ni();
        ArrayList<pair> arr = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            long x = sc.nl();
            long y = sc.nl();
            arr.add(new pair(x, y));
        }
        Collections.sort(arr);
        int pntr1 = 0;
        int pntr2 = arr.size() - 1;
        long cur = 0;
        long ans = 0;
        while (pntr1 < pntr2) {
            if (arr.get(pntr1).second <= cur && pntr1 < arr.size()) {
                cur += arr.get(pntr1).first;
                ans += arr.get(pntr1).first;
                arr.get(pntr1).first = 0;
                pntr1++;
                continue;
            }
            long delta = Math.min(arr.get(pntr1).second - cur, arr.get(pntr2).first);
            cur += delta;
            arr.get(pntr2).first -= delta;
            ans += 2 * delta;
            if (arr.get(pntr2).first == 0) {
                pntr2--;
            }
        }
        if (pntr1 == pntr2) {
            if (cur + arr.get(pntr1).first < arr.get(pntr1).second) {
                ans += 2 * arr.get(pntr1).first;
            } else {
                long moves = Math.max(arr.get(pntr1).second - cur, 0);
                ans += 2 * arr.get(pntr1).first - (arr.get(pntr1).first) + moves;
            }
        }
        System.out.println(ans);
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
