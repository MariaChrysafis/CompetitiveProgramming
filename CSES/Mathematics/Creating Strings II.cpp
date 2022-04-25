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
    int oc[26];
    string s;
    cin >> s;
    vector<int64_t> fact = {1};
    for (int i = 0; i <= s.length(); i++) {
        fact.push_back((fact.back() * fact.size()) % MOD);
    }
    for (int i = 0; i < 26; i++) {
        oc[i] = 0;
    }
    for (int i = 0; i < s.length(); i++) {
        oc[s[i] - 'a']++;
    }
    int64_t x = fact[s.length()];
    for (int i = 0; i < 26; i++) {
        if (oc[i])
            x *= inv(fact[oc[i]]), x %= MOD;
    }
    cout << x;
}
