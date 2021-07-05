class Solution {
public:
    const int MOD = 1e9 + 7;
    long long binpow(long long x, long long y){
        long long cur = x;
        long long ans = 1;
        while(y != 0){
            if(y & 1){
                ans *= cur;
                ans %= MOD;
            }
            y /= 2;
            cur *= cur;
            cur %= MOD;
        }
        return ans;
    }
    int countGoodNumbers(long long n) {
        return (binpow(4, n/2) * binpow(5, (n + 1)/2)) % MOD;
    }
};
