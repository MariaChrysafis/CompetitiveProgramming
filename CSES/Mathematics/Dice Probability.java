//package com.company;
 
 
import java.math.BigDecimal;
import java.util.*;
import java.io.*;
import java.io.*;
import java.math.BigDecimal;
import java.math.RoundingMode;
 
 
 
public class Main {
    public static BigDecimal power (int n, int k) {
        BigDecimal bd = new BigDecimal(n);
        return bd.pow(k);
    }
    public static BigDecimal minus (BigDecimal a, BigDecimal b) {
        a = a.subtract(b);
        return a;
    }
    public static BigDecimal f (int n, int k) {
        BigDecimal bd = new BigDecimal(0);
        for (int i = 1; i <= k; i++) {
            BigDecimal dum = minus(power(i, n), power(i - 1, n));
            dum = dum.multiply(new BigDecimal(i));
            bd = bd.add(dum);
        }
        bd = bd.multiply(new BigDecimal(1000000));
        bd = bd.divide(power(k, n), RoundingMode.HALF_UP);
        return bd;
    }
    public static void main(String[] args) throws Exception {
        Reader br = new Reader();
        int n, a, b;
        n = br.nextInt();
        a = br.nextInt();
        b = br.nextInt();
        BigDecimal dp[][] = new BigDecimal[n + 1][b + 1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= b; j++) {
                dp[i][j] = new BigDecimal(0);
            }
        }
        dp[0][0] = new BigDecimal(1);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= b; j++) {
                dp[i][j] = new BigDecimal(0);
                for (int k = 1; k <= 6; k++) {
                    if (j - k >= 0) {
                        dp[i][j] = dp[i][j].add(dp[i - 1][j - k]);
                    }
                }
            }
        }
        BigDecimal ans = new BigDecimal(0);
        for (int i = a; i <= b; i++) {
            ans = ans.add(dp[n][i]);
        }
        ans = ans.multiply(new BigDecimal("1000000000000"));
        ans = ans.divide(power(6, n), RoundingMode.HALF_DOWN);
        StringBuilder s = new StringBuilder(ans.toString());
        while (s.length() != 12) {
            StringBuilder zero = new StringBuilder("0");
            zero.append(s);
            s  =zero;
        }
        BigDecimal dummy = new BigDecimal(s.toString());
        if (s.charAt(6) >= '5') {
            dummy = dummy.add(new BigDecimal(1000000));
        }
        s = new StringBuilder(dummy.toString());
        while (s.length() != 12) {
            StringBuilder zero = new StringBuilder("0");
            zero.append(s);
            s  =zero;
        }
        System.out.print("0.");
        for (int i = 0; i < 6; i++) {
            System.out.print(s.charAt(i));
        }
 
    }
    static class Reader
    {
        final private int BUFFER_SIZE = 1 << 16;
        private DataInputStream din;
        private byte[] buffer;
        private int bufferPointer, bytesRead;
 
        public Reader()
        {
            din = new DataInputStream(System.in);
            buffer = new byte[BUFFER_SIZE];
            bufferPointer = bytesRead = 0;
        }
        private void fillBuffer() throws IOException
        {
            bytesRead = din.read(buffer, bufferPointer = 0, BUFFER_SIZE);
            if (bytesRead == -1)
                buffer[0] = -1;
        }
 
        private byte read() throws IOException
        {
            if (bufferPointer == bytesRead)
                fillBuffer();
            return buffer[bufferPointer++];
        }
 
        public void close() throws IOException
        {
            if (din == null)
                return;
            din.close();
        }
        public int nextInt() throws IOException
        {
            int ret = 0;
            byte c = read();
            while (c <= ' ')
                c = read();
            boolean neg = (c == '-');
            if (neg)
                c = read();
            do
            {
                ret = ret * 10 + c - '0';
            }  while ((c = read()) >= '0' && c <= '9');
 
            if (neg)
                return -ret;
            return ret;
        }
    }
}
 
 
 
 
