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
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll a, b;
    cin >> a >> b;
    if (b - a >= 5) {
        cout << 0;
        return 0;
    }
    ll ans = 1;
    for (ll x = a + 1; x <= b; x++) {
        ans *= x;
        ans %= 10;
    }
    cout << ans % 10;
}
