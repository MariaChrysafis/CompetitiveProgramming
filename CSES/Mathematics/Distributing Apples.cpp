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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int64_t> fact = {1};
    for (int i = 0; i <= (int)2e6; i++) {
        fact.push_back((fact.back() * fact.size()) % MOD);
    }
    int a, b;
    cin >> a >> b;
    cout << (fact[a + b - 1] * inv((fact[a - 1] * fact[b]) % MOD)) % MOD;
}
