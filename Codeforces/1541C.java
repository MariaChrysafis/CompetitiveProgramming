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
    static void sort(long[] a) {
        ArrayList<Long> l=new ArrayList<>();
        for (long i:a) l.add(i);
        Collections.sort(l);
        for (int i=0; i<a.length; i++) a[i]=l.get(i);
    }
    static void print(int[] arr){
        for(int i = 0; i < arr.length; i++){
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
    static void solve(){
        int n = sc.ni();
        long[] arr = new long[n];
        for(int i = 0; i < n; i++){
            arr[i] = sc.ni();
        }
        sort(arr);
        long pref[] = new long[n];
        pref[0] = arr[0];
        for(int i = 1; i < n; i++){
            pref[i] = pref[i - 1] + (arr[i] - arr[i - 1]);
        }
        long suf[] = new long[n];
        suf[n - 1] = pref[n - 1];
        for(int i = n - 2; i >= 0; i--){
            suf[i] = pref[i] + suf[i + 1];
        }
        long ans = 0;
        for(int i = 1; i < n - 1; i++){
            ans -= (n - i - 1) * pref[i - 1];
            ans += suf[i + 1];
        }
        System.out.println(-ans);
    }
    public static void main(String[] args) {
        int t = sc.ni();
        for(int i = 0; i < t; i++){
            solve();
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
