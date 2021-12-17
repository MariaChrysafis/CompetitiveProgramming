#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

#define ll long long
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
using namespace std;

int gcd(int a, int b) {
    if (!a || !b) return max(a, b);
    return gcd(max(a, b) % min(a, b), min(a, b));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        for (int k = 2; k <= 1000; k++) {
            int a = n - (k + 1);
            int b = k;
            int c = 1;
            if (a < 0 || b < 0 || c < 0) continue;
            if (a == b || b == c || a == c) continue;
            if (gcd(a, b) != c) continue;
            cout << a << " " << b << " " << c << '\n';
            break;
        }
    }
}
