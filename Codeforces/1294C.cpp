#include <iostream>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <set>
#define ll long long
using namespace std;
pair<ll, ll> factors (ll n, ll exclude) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0 && i != exclude && n/i != exclude && i * i != n) {
            return {i, n/i};
        }
    }
    return {-1, -1};
}
void solve() {
    ll n;
    cin >> n;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            pair<ll, ll> fact = factors(n / i, i);
            if (fact.first == -1 || fact.second == -1) {
                cout << "NO\n";
                return;
            }
            cout << "YES\n";
            cout << fact.first << " " << fact.second << " " << i << '\n';
            return;
        }
    }
    cout << "NO\n";
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
