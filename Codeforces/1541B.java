//package com.MARIAAAA;
 
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
        Map<Long, Long> myMap = new HashMap<Long, Long>();
        long[] arr = new long[n];
        for(int i = 0; i < n; i++){
            arr[i] = sc.ni();
            myMap.put(arr[i], new Long(i + 1));
        }
        sort(arr);
        long[] inv = new long[n];
        for(int i = 0; i < n; i++){
            inv[i] = myMap.get(arr[i]);
        }
        long cntr = 0;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(arr[i] * arr[j] == inv[i] + inv[j]){
                    cntr++;
                }
                if(arr[i] * arr[j] > inv[i] + inv[j] + 2 * n){
                    break;
                }
            }
        }
        System.out.println(cntr);
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
