#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>

using namespace std;

typedef int64_t ll;
struct Tuple {
    ll x;
    char c;
    ll y;
};
vector<Tuple> final;

ll add (ll x, ll y) {
    final.push_back({x, '+', y});
    return (x + y);
}

ll bitxor (ll x, ll y) {
    final.push_back({x, '^', y});
    return x ^ y;
}

ll mult (ll x, ll y) {
    for (int i = 2; i <= y; i++) {
        add(x, x * (i - 1));
    }
    return (x * y);
}

ll multPower (ll x, ll y) {
    for (int i = 1; i <= y; i++) {
        x = add(x, x);
    }
    return x;
}

void print (int x) {
    for (int i = log2(x); i >= 0; i--) {
        if (x & (1 << i)) cout << 1;
        else cout << 0;
    }
    cout << '\n';
}

void reduce (ll x) {
    //cout << x << '\n';
    if (x == 1) {
        return;
    }
    if (x % 4 == 3) {
        reduce(bitxor(x, add(x, x)));
        return;
    }
    int lg2 = log2(x);
    ll val = multPower(x, lg2);
    ll val1 = bitxor(add(val, x), bitxor(val, x));
    ll modif = x;
    while (__builtin_popcount(modif) != 1) {
        while (modif < val1) {
            modif = add(modif, modif);
        }
        modif = bitxor(val1, modif);
    }
    while (modif * 2 != val1) {
        modif = add(modif, modif);
    }
    modif = bitxor(modif, x);
    reduce(modif);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    reduce(n);
    cout << final.size() << '\n';
    for (auto& p: final) {
        cout << p.x << " " << p.c << " " << p.y << '\n';
    }
}
