#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")
using namespace std;
map<string,vector<string>> myMap;
const int MOD = 1e9 + 7;
long long binPow(long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y /= 2;
    }
    return ans;
}
int main() {
    myMap["White"] = {"Red", "Green", "Blue", "Orange"};
    myMap["Yellow"] = {"Red", "Blue", "Green", "Orange"};
    myMap["Green"] = {"Red", "White", "Yellow", "Orange"};
    myMap["White"] = {"Red", "Green", "Blue", "Orange"};
    myMap["Orange"] = {"Blue", "White", "Yellow", "Green"};
    myMap["Blue"] = {"Red", "Orange", "White", "Yellow"};
    myMap["Red"] = {"White", "Blue", "Green", "Yellow"};
    int n;
    cin >> n;
    //cout << binPow(3, 5) << endl;
    //cout << binPow(6, MOD - 2) << endl;
    long long dp[n + 1];
    dp[1] = 6;
    for (int i = 2; i <= n; i++) {
        dp[i] = ((dp[i - 1] * dp[i - 1]) % MOD * 16) % MOD * binPow(6, MOD - 2);
        dp[i] %= MOD;
    }
    cout << dp[n];
}
