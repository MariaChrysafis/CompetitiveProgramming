import java.lang.*;
import java.io.*;
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
 
    public static int[] sort(int[] array){
        ArrayList<Integer> copy = new ArrayList<>();
        for (int i : array)
            copy.add(i);
        Collections.sort(copy);
        for(int i = 0;i<array.length;i++)
            array[i] = copy.get(i);
        return array;
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
    static ArrayList<ArrayList<Long>> dp;
    static ArrayList<Long> arr = new ArrayList<Long>();
    public static int MOD = 998244353;
    public static long mult(long a, long b){
        return (a * b) % MOD;
    }
    public static long memoize(int l, int r){
        if(l >= r){
            return 1;
        }
        if(dp.get(l).get(r) != -1){
            return dp.get(l).get(r);
        }
        int ind = l;
        for(int i = l; i <= r; i++){
            if(arr.get(i).compareTo(arr.get(ind)) < 0){
                ind = i;
            }
        }
        int left = 0;
        for(int i = l; i <= ind; i++){
            left += mult(memoize(l, i - 1), memoize(i, ind - 1));
            left %= MOD;
        }
        int right = 0;
        for(int i = ind; i <= r; i++){
            right += mult(memoize(ind + 1, i), memoize(i + 1, r));
            right %= MOD;
        }
        dp.get(l).set(r, mult(left, right));
        return mult(left, right);
    }
    public static void main(String[] args) {
        OutputStream outputStream = System.out;
        PrintWriter out = new PrintWriter(outputStream);
        FastReader in = new FastReader();
        int n = in.nextInt();
        n = in.nextInt();
        dp = new ArrayList<>(n);
        for(int i = 0; i < n; i++){
            dp.add(new ArrayList());
            for(int j = 0; j < n; j++){
                dp.get(i).add(-1L);
            }
        }
        for(int i = 0; i < n; i++){
            arr.add(in.nextLong());
        }
        System.out.print(memoize(0, n - 1) + " ");
    }
}
