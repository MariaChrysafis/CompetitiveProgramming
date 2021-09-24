class Solution {
    public static int MOD = (int)1e9 + 7;
    public static long mult(long a, long b) {
        a %= MOD;
        b %= MOD;
        return (a * b) % MOD;
    }
    public static long binPow(long x, long a) {
        a %= (MOD - 1);
        x %= MOD;
        long ans = 1;
        long res = x;
        //cout << res << " " << ans << endl;
        //System.out.println(res + " " + ans);
        while (a > 0) {
            if (a % 2 == 1) {
                ans = mult(ans,res);
            }
            res = mult(res, res);
            a /= 2;
        }
        //System.out.println(ans);
        return ans;
    }
    public static long inv(long x) {
        return binPow(x, MOD - 2);
    }
    public int minNonZeroProduct(int p) {
        long x = 1;
        for(int i = 0; i < p; i++) {
            x *= 2;
        }
        long a = binPow(x - 2, x/2 - 1);
        return (int)mult(a, x - 1);
    }
}
