#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
using namespace std;

bool isPrime (ll x) {
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        ll x;
        cin >> x;
        ll l = 0;
        ll r = 1e8;
        while (l != r) {
            ll m = (l + r + 1)/2;
            if (m * m <= x) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if (l * l == x && x != 1) {
            if (isPrime(l)) {
                cout << "YES\n";
                continue;
            }
        }
        cout << "NO\n";
    }

}
