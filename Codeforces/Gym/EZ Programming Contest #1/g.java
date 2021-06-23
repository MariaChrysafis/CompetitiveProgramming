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
    //public static int best[] = new int[8];
    //public static int worst[] = new int[8];
    public static int[] worst = {-1, -1, 1, 7, 4, 2, 6, 8, 10, 18, 22, 20, 28, 68, 88};
    public static int[] worstBegin = {888, 108, 188, 200, 208, 288, 688};
    static FastScanner sc = new FastScanner();
    static void solve(int x){
        if(x < worst.length){
            System.out.print(worst[x]);
        }else{
            System.out.print(worstBegin[x % 7]);
            for(int i = 0; i < (x - 1)/7 - 2; i++){
                System.out.print(8);
            }
        }
        System.out.print(" ");
        if(x % 2 == 0){
            System.out.print(1);
        }else{
            System.out.print(7);
        }
        for(int i = 0; i < x/2 - 1; i++){
            System.out.print(1);
        }
        System.out.println();
    }
    public static void main(String[] args){
        int t = sc.ni();
        for(int i = 0; i < t; i++){
            int x = sc.ni();
            solve(x);
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
      
