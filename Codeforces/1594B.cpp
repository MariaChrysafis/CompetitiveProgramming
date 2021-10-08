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
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        long long ans = 0;
        for (int i = 0; i < 30; i++) {
            if (k & (1 << i)) {
                ans += binPow(n, i);
                ans %= MOD;
            }
        }
        cout << ans << endl;
    }
}
