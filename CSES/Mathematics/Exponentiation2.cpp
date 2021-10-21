#include <iostream>
const long long mod = 1000000007;
using namespace std;
long long binpow(long long a, long long b, const long long MOD) {
    long long res = 1;
    while (b > 0) {
        if (b & 1){
            res = res * a;
            res %= MOD;
        }
        a = a * a;
        a %= MOD;
        b >>= 1;
    }
    return res;
}
int main(){
    int t;
    cin >> t;
    while(t--){
        long long a,b,c;
        cin >> a >> b >> c;
        long long x = binpow(b, c, mod - 1);
        long long y = binpow(a,x,mod);
        cout << y << endl;
    }
}
