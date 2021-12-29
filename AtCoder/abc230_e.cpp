#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;

typedef int64_t ll;

void solve() {
    ll N;
    cin >> N;
    set<ll> pos;
    for (ll i = 1; i <= sqrt(N); i++) {
        pos.insert(i);
        pos.insert(N/i);
    }
    ll ans = 0;
    for (ll i: pos) {
        //cout << i << ": " << N/(i + 1) + 1 << " " << N/i << '\n';
        ll l = N/(i + 1) + 1;
        ll r = N/i;
        if (r >= l) {
            ans += (r - l + 1) * i;
        }
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();

}
