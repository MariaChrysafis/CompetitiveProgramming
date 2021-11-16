#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
#include <set>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cassert>
using namespace std;
long long mult (long long x, long long y, int MOD) {
    x += MOD;
    y += MOD;
    x %= MOD;
    y %= MOD;
    return (x * y) % MOD;
}
long long binPow (long long x, long long y, int MOD) {
    if (x < 0) {
        x += MOD;
    }
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res, MOD);
        }
        res = mult(res, res, MOD);
        y /= 2;
    }
    return ans;
}
long long inv (long long x, int MOD) {
    if (x < 0) {
        x += MOD;
    }
    return binPow(x, MOD - 2, MOD);
}
int main() {
    int n;
    cin >> n;
    long long a[n];
    long long b[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int cnt = 0;
    map<pair<int,int>,int> myMap;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0 && b[i] == 0) {
            cnt++;
        } else if (a[i] == 0) {
            continue;
        } else {
            int MOD1 = (int)1e9 + 9;
            int MOD2 = (int)1e9 + 7;
            int x = mult(b[i], inv(a[i], MOD1), MOD1);
            int y = mult(b[i], inv(a[i], MOD2), MOD2);
            //cout << x << " " << y << endl;
            myMap[{x, y}]++;
        }
    }
    int add = 0;
    for (auto& p: myMap) {
        //cout << p.first << " " << p.second << endl;
        add = max(add, p.second);
    }
    cout << add + cnt << endl;
}
