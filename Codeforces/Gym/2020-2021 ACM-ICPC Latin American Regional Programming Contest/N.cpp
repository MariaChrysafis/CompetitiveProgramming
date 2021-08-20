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
 
    public static void main(String[] args) {
        OutputStream outputStream = System.out;
        PrintWriter out = new PrintWriter(outputStream);
        FastReader in = new FastReader();
        int n = in.nextInt();
        String arr[] = new String[n + 1];
        int a[] = new int[n + 1];
        for(int i = 0; i < arr.length; i++){
            arr[i] = in.nextLine();
            arr[i] = arr[i].substring(1);
            int dot = 0;
            for(int j = 0; j < arr[i].length(); j++){
                if(arr[i].charAt(j) == '.'){
                    dot = j;
                }
            }
            String s1 = arr[i].substring(0, dot);
            String s2 = "";
            s2 += arr[i].charAt(arr[i].length() - 2);
            s2 += arr[i].charAt(arr[i].length() - 1);
            arr[i] = s1 + s2;
            a[i] = Integer.parseInt(arr[i]);
            //System.out.println(arr[i]);
        }
        int cur = a[0];
        int ans = 0;
        for(int i = 1; i < arr.length; i++){
            cur += a[i];
            if(cur % 100 != 0){
                ans++;
            }
            cur %= 100;
        }
        System.out.print(ans);
    }
}
