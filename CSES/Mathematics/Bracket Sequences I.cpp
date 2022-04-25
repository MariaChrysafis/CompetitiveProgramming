#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
int64_t MOD = 1e9 + 7;
int64_t binPow (int64_t x, int64_t y) {
    int64_t res = x;
    int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res; ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}
vector<int64_t> fact = {1};
int64_t combo (int a, int b) {
    return (fact[a] * inv((fact[a - b] * fact[b]) % MOD)) % MOD;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    if (n % 2 == 1) {
        cout << 0;
        return 0;
    }
    n /= 2;
    for (int i = 0; i <= 2 * n; i++) {
        fact.push_back((fact.back() * fact.size()) % MOD);
    }
    cout << (combo(2 * n, n) - combo(2 * n, n + 1) + MOD) % MOD;
}
