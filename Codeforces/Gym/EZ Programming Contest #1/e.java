import java.lang.*;
import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;
import java.util.*;
 
import java.math.*;
import java.awt.Point;
public class Main {
    static FastScanner sc = new FastScanner();
    static String convert(Boolean b){
        if(b){
            return "YES";
        }
        return "NO";
    }
    static Boolean solve(int n, String s1, String s2){
        return (s2.contains("o"));
    }
    public static void main(String[] args){
        int t = sc.ni();
        for(int i = 0; i < t; i++){
            int n = sc.ni();
            String s1 = sc.next();
            String s2 = sc.next();
            boolean b = solve(n, s1, s2);
            System.out.println(convert(b));
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
 
    String nextLine() {
        String str = "";
        try {
            str = br.readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return str;
    }
}
