/* package codechef; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class Codechef
{
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
    
	public static void main(String[] args) {
        OutputStream outputStream = System.out;
        PrintWriter out = new PrintWriter(outputStream);
        FastReader in = new FastReader();
        int t = in.nextInt();
        for(int tc = 0; tc < t; tc++) {
            int n = in.nextInt();
            int arr[] = new int[n];
            for(int i = 0; i < n; i++) {
                arr[i] = in.nextInt();
            }
            if(n > 4) {
                System.out.println("NO");
                continue;
            }
            System.out.println("YES");
            if(n >= 1) System.out.println(arr[0] + " " + 0);
            if(n >= 2) System.out.println(-arr[1] + " " + 0);
            if(n >= 3) System.out.println(0 + " " + arr[2]);
            if(n >= 4) System.out.println(0 + " " + -arr[3]);
            System.out.println();
        }
    }
}
