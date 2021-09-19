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

    static Boolean solve(String s1, String s2) {
        if(s1.equals(s2)) {
            return true;
        }
        if(s2.contains("0") && !s2.contains("1")){
            return false;
        }
        if(s2.contains("1") && !s2.contains("0")) {
            return false;
        }
        return true;
    }
    
	public static void main (String[] args) throws java.lang.Exception
	{
		OutputStream outputStream = System.out;
        PrintWriter out = new PrintWriter(outputStream);
        FastReader in = new FastReader();
        int t = in.nextInt();
        for(int tc = 0; tc < t; tc++) {
            int n = in.nextInt();
            String s1 = in.nextLine();
            String s2 = in.nextLine();
            //System.out.println(s1 + " " + s2);
            Boolean b = solve(s1, s2);
            if(b) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
	}
}
