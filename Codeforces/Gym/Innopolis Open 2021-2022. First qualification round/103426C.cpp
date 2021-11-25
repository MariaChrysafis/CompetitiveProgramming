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
const int MOD = 1e9 + 7;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll l, r;
    cin >> l >> r;
    l++, r++;
    if (l >= 0 && r <= 0) {
        cout << "-1\n";
        return 0;
    }
    ll ans = 0;
    for (ll i = 1; i <= (ll)sqrt(max(abs(r), abs(l))) + 3; i++) {
        for (ll strt = (min(abs(l), abs(r)) + i - 1)/i * i; strt <= max(abs(r), abs(l)); strt += i) {
            if (i * i <= strt) ans += 2;
        }
    }
    if (l < 0) {
        for (ll i = l; i <= r; i++) {
            ll x = sqrt(-i);
            if (i < 0 && x * x == -i) {
                ans--;
            }
        }
    }
    cout << ans << '\n';

}
