import java.lang.*;
import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;
import java.util.*;
import java.math.*;
import java.awt.Point;
public class Main {
    static int MAX = 5;
    public static Long zero = new Long(0);
    static FastScanner sc = new FastScanner();
    static String convert(Boolean b){
        if(b){
            return "YES";
        }
        return "NO";
    }
    static long solve(long n1, long n2){
        long x = (n1 ^ n2);
        boolean b = ((x | n1) == (x ^ n2));
        if(b){
            return x;
        }else{
            return -1;
        }
        //return 1;
    }
    public static void main(String[] args){
        int t = sc.ni();
        for(int i = 0; i < t; i++){
            long n1 = sc.nl();
            long n2 = sc.nl();
            long x = solve(n1, n2);
            System.out.println(x);
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
    
