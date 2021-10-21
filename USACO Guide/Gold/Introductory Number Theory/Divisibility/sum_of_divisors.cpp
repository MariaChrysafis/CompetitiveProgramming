#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
const int MOD = 2 * (1e9 + 7);
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long n;
    cin >> n;
    long long ans = 0;
    set<long long> s;
    for (long long i = 1; i * i <= n; i++) {
        s.insert(n / i);
    }
    for (long long i = 1; i * i <= n; i++) {
        s.insert(i);
    }
    for (long long k: s) {
        long long l = (n + 1 + k)/(k + 1);
        long long r = n/k;
        r %= MOD;
        l %= MOD;
        ans += (((r - l + 1) * (l + r)/2) % MOD * k) % MOD;
        ans %= MOD;
    }
    cout << ans % (MOD/2) << endl;
}
