#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <map>
using namespace std;
const long long MOD = 998244353;
long long mult (long long x, long long y) {
    x %= MOD, y %= MOD;
    return (x * y) % MOD;
}
long long add (long long x, long long y) {
    x %= MOD, y %= MOD;
    return (x + y) % MOD;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int n = s.length();
    vector<long long> v = {1};
    long long powr = 1;
    for (int i = 1; i <= n + 2; i++) {
        v.push_back(add(mult(10, v[i - 1]), powr));
        powr = mult(powr, 2);
    }
    long long ans = 0;
    powr = 1;
    for (int i = 0; i < s.length(); i++) {
        ans = add(ans, mult(mult(powr, v[s.length() - i - 1]), s[i] - '0'));
        powr = mult(powr, 2);
    }
    cout << ans;
}
