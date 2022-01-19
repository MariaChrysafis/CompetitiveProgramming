#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

typedef int64_t ll;
const int MAX = 1e6 + 1;
vector<ll> phi_1_to_n(int n) {
    vector<ll> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        phi[i] = i;
    }

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    return phi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> phi = phi_1_to_n(MAX);
    vector<ll> res; res.assign(MAX, 0);
    for (int i = 1; i < MAX; i++) {
        for (int j = i; j < MAX; j += i) {
            res[j] += i * phi[i];
        }
    }
    int t;
    cin >> t;
    while (t--) {
        ll x;
        cin >> x;
        ll ans = res[x];
        ans++;
        cout << (ans * x)/2 << '\n';
    }
}
