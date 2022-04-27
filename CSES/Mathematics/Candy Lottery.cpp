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
            //System.out.println(dum);
            bd = bd.add(dum);
        }
        bd = bd.multiply(new BigDecimal(1000000));
        bd = bd.divide(power(k, n), RoundingMode.HALF_UP);
        return bd;
    }
    public static void main(String[] args) throws Exception {
        Reader br = new Reader();
        BigDecimal ans = f(br.nextInt(), br.nextInt());
        String s = ans.toString();
        for (int i = 0; i < s.length(); i++) {
            System.out.print(s.charAt(i));
            if (s.length() - i - 1 == 6) {
                System.out.print('.');
            }
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
 
 
