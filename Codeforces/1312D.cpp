#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
long long MOD = 998244353;
long long mult(long long x, long long y){
    return (x * y) % MOD;
}
long long subtract(long long x, long long y){
    return (x - y + 2 * MOD) % MOD;
}
long long binpow(long long x, long long y){
    long long res = x;
    long long ans = 1;
    while(y > 0){
        if(y & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
long long inv(long long x){
    return binpow(x, MOD - 2);
}
long long fact(long long n){
    if(n == 0) return 1;
    return mult(fact(n - 1), n);
}
long long combo(int a, int b){
    //a chose b
    return mult(fact(a), inv(mult(fact(b), fact(a - b))));
}
int main(){
    int n, m;
    cin >> n >> m;
    long long x = mult(combo(m - 1,n - 2), m);
    x = subtract(x, combo(m, n - 1));
    x = mult(x, binpow(2, n - 3));
    cout << x << endl;
}
