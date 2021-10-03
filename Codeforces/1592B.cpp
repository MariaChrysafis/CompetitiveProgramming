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

#define ll long long
using namespace std;
ll ceil(ll a, ll b) {
    return (a + b - 1)/b;
}
bool canSwap(int x, int y, int C, int n) {
    if(x == y) {
        return true;
    }
    if (x > y) {
        swap(x, y);
    }
    if(abs(x - y) >= C) return true;
    if(abs(n - 1 - x) >= C) return true;
    if(abs(y) >= C) return true;
    return false;
}
bool solve () {
    ll n;
    ll x;
    cin >> n >> x;
    vector<ll> arr(n);
    vector<ll> copy(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        copy[i] = arr[i];
    }
    sort(copy.begin(), copy.end());
    for (int i = n - x; i <= x - 1; i++) {
        if (copy[i] != arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}
