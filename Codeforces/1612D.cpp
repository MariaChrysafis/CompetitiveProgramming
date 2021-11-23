#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
bool valid (ll a, ll b, ll x) {
    if (a == x || b == x) {
        return true;
    }
    if (x > max(a,b)) {
        return false;
    }
    if (a > b) {
        swap(a, b);
    }
    if (a == 0) {
        return false;
    }
    if (b % a == x % a) {
        return true;
    }
    return valid(b % a, a, x);
}
bool solve() {
    ll a, b, x;
    cin >> a >> b >> x;
    return valid(a, b , x);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        bool b = solve();
        if (b) cout << "YES\n";
        else cout << "NO\n";
    }
}
