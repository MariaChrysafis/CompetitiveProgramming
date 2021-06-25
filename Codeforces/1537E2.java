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
        int n = sc.ni();
        int k = sc.ni();
        String s = sc.next();
        int j = 0;
        int len = 1;
        for(int i = 1; i < n; i++){
            if(s.charAt(j) < s.charAt(i)){
                break;
            }
            if(s.charAt(j) > s.charAt(i)){
                len = i + 1;
                j = 0;
                continue;
            }
            j++;
            j %= len;
        }
        for(int i = 0; i < k; i++){
            System.out.print(s.charAt(i % len));
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
