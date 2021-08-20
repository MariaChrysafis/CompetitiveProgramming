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
 
    static long gcd(long a, long b) {
        if (a == 0 || b == 0) return Math.max(a, b);
        return gcd(Math.max(a, b) % Math.min(a, b), Math.min(a, b));
    }
 
    public static long MOD = 998244353;
    static List<Long> primes = new ArrayList<>();
    static long fact[] = new long[50];
    static long inv_fact[] = new long[50];
 
    static long binpow(long a, long b) {
        long ans = 1;
        long res = a;
        while (b > 0) {
            if (b % 2 == 1) {
                ans *= res;
                ans %= MOD;
            }
            b /= 2;
            res = (res * res) % MOD;
        }
        return ans;
    }
 
    static long inv(long a) {
        return binpow(a, MOD - 2);
    }
 
    static long binom(List<Integer> val) {
        long sum = 0;
        for (int i = 0; i < val.size(); i++) {
            sum += val.get(i);
        }
        long ans = fact[(int) sum];
        for (int i = 0; i < val.size(); i++) {
            if (val.get(i) == 0 || val.get(i) == 1) continue;
            ans *= inv_fact[val.get(i)];
            ans %= MOD;
        }
        return ans;
    }
 
    static long paths(long u) {
        long new_u = u;
        List<Integer> val = new ArrayList<>();
        for (int i = 0; i < primes.size(); i++) {
            int cntr = 0;
            while (new_u % primes.get(i) == 0) {
                new_u /= primes.get(i);
                cntr++;
            }
            if (cntr != 0) {
                val.add(cntr);
            }
        }
        return binom(val);
    }
 
    static long paths(long u, long v) {
        if (u < v) {
            return paths(v, u);
        }
        if (u % v == 0) {
            return paths(u / v);
        }
        return (paths(gcd(u, v), u) * paths(gcd(u, v), v)) % MOD;
    }
 
    public static void main(String[] args) {
        OutputStream outputStream = System.out;
        PrintWriter out = new PrintWriter(outputStream);
        FastReader in = new FastReader();
        fact[0] = 1;
        for (int i = 1; i < fact.length; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
            inv_fact[i] = inv(fact[i]);
        }
        long D = in.nextLong();
        long new_D = D;
        for (int i = 2; i <= Math.sqrt(D); i++) {
            if (new_D % i == 0) {
                primes.add((long) i);
                while (new_D % i == 0) {
                    new_D /= i;
                }
            }
        }
        if (new_D != 1) {
            primes.add(new_D);
        }
        int Q = in.nextInt();
        for (int dum = 0; dum < Q; dum++) {
            out.println(paths(in.nextLong(), in.nextLong()));
        }
        out.close();
    }
}
