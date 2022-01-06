#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

using namespace std;
typedef long long ll;

const int MAX = 1e6 + 1;

vector<vector<int>> primes;

int F (int x, int y) {
    //how many numbers from 1...x are relatively prime with y
    int ans = 0;
    int prod[(1 << primes[y].size())];
    prod[0] = 1;
    for (int i = 1; i < (1 << primes[y].size()); i++) {
        int lg2 = log2(i);
        prod[i] = prod[i - (1 << lg2)] * primes[y][lg2];
    }
    for (int i = 1; i < (1 << (int)primes[y].size()); i++) {
        int bits = __builtin_popcount(i) + 1;
        if (bits % 2 == 0) {
            ans += floor(x/prod[i]);
        } else {
            ans -= floor(x/prod[i]);
        }
    }
    return x - ans;
}

int L (int x, int p, int k) {
    int l = 0;
    int r = 19260817;
    int base = F(x, p);
    while (l != r) {
        ll m = (l + r)/2;
        if (F(m, p) - base >= k) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    primes.resize((int)MAX + 1);
    for (int i = 2; i < primes.size(); i++) {
        if (primes[i].empty()) {
            for (int j = i; j < primes.size(); j += i) {
                primes[j].push_back(i);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        ll x, p, k;
        cin >> x >> p >> k;
        cout << L(x, p, k) << '\n';
    }
}
