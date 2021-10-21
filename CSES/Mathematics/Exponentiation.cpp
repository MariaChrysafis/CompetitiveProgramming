#include <iostream>
#define MOD 1000000007
using namespace std;
long long binpow(long long a, long long b) {
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
        long long a,b;
        cin >> a >> b;
        long long x = binpow(a, b);
        cout << x << endl;
    }
}
