#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
 
using namespace std;
 
const int MOD = 998244353;
 
long long mult (long long x, long long y){
    return (x * y) % MOD;
}
 
long long binPow (long long x, long long y){
    long long ans = 1;
    long long res = x;
    while (y > 0){
        if (y & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
 
long long inv (long long x){
    return binPow (x, MOD - 2);
}
 
long long solve() {
    long long n, m, l, r;
    cin >> n >> m >> l >> r;
    if (n % 2 == 1 && m % 2 == 1){
        return binPow(r - l + 1, n * m);
    }
    if (l % 2 != r % 2){
        return mult(binPow(r - l + 1, n * m), inv(2));
    }
    //even sized board
    return mult(binPow(r - l + 1, n * m) + 1, inv(2));
}
 
int main() {
    cout << solve();
}
