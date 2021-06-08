#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int MOD = 1e9 + 7;
long long mult(long long a, long long b){
    return (a * b) % MOD;
}
long long powr(long long a, long long b){
    if(b == 0){
        return 1;
    }
    if(a == 0){
        return 0;
    }
    long long res = 1;
    while(b){
        if(b & 1){
            res = mult(res, a);
        }
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
long long inv(long long a){
    return powr(a, MOD - 2);
}
void solve(int n, int k){
    cout << powr(n, k) << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        solve(n, k);
    }
}
