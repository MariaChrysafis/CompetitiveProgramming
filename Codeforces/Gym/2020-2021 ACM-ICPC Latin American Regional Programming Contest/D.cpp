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
        int arr[] = new int[n];
        int d[] = new int[200001];
        for(int i = 0; i < d.length; i++){
            d[i] = 0;
        }
        for(int i = 0; i < n; i++){
            arr[i] = in.nextInt();
            int cur = arr[i];
            while(d[cur] == 1){
                d[cur] = 0;
                cur++;
            }
            d[cur] = 1;
        }
        int cntr = 0;
        for(int i = 0; i < d.length; i++){
            if(d[i] == 1){
                cntr++;
            }
        }
        if(cntr <= 2 && n != 1){
            System.out.print('Y');
        }else{
            System.out.print('N');
        }
 
    }
}
