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
ll solve () {
    ll a, b;
    cin >> a >> b;
    if (a > b) {
        swap (a, b);
    }
    //a < b
    if (3 * a >= b) {
        return (a + b)/4;
    }
    return a;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        ll x = solve();
        cout << x << '\n';
    }
}
