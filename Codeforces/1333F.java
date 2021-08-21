import java.lang.*;
import java.io.*;
import java.lang.reflect.Array;

import java.util.concurrent.ThreadLocalRandom;
import java.util.*;

public class Main {
    static class FastReader {
        BufferedReader br;
        StringTokenizer st;

        public FastReader() {
            br = new BufferedReader(new
                    InputStreamReader(System.in));
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

        int nextInt() {
            return Integer.parseInt(next());
        }

        long nextLong() {
            return Long.parseLong(next());
        }

        double nextDouble() {
            return Double.parseDouble(next());
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

    static final Random random=new Random();

    static void ruffleSort(int[] a) {
        int n=a.length;//shuffle, then sort
        for (int i=0; i<n; i++) {
            int oi=random.nextInt(n), temp=a[oi];
            a[oi]=a[i]; a[i]=temp;
        }
        Arrays.sort(a);
    }

    public static void print(int[] arr){
        for(int i = 0; i < arr.length; i++){
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }
    static ArrayList<Integer> identity(int n){
        ArrayList<Integer> arr = new ArrayList<>(n);
        return arr;
    }
    public static void main(String[] args) {
        OutputStream outputStream = System.out;
        PrintWriter out = new PrintWriter(outputStream);
        FastReader in = new FastReader();
        int n = in.nextInt();
        int max_div[] = new int[n + 1];
        for(int i = 0; i < n; i++){
            max_div[i] = 1;
        }
        max_div[1] = 1;
        for(int i = 2; i <= n; i++){
            if(max_div[i] == 1) {
                for (int j = 2 * i; j <= n; j += i) {
                    max_div[j] = Math.max(j/i, max_div[j]);
                }
            }
        }
        
        ruffleSort(max_div);
        for(int i = 2; i <= n; i++){
            out.print(max_div[i] + " ");
        }
        out.close();
    }
}
